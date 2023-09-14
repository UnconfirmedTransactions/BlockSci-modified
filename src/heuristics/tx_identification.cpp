//
//  tx_identification.cpp
//  blocksci
//
//  Created by Harry Kalodner on 12/1/17.
//

#include <blocksci/heuristics/tx_identification.hpp>
#include <blocksci/chain/transaction.hpp>
#include <blocksci/chain/input.hpp>
#include <blocksci/chain/output.hpp>
#include <blocksci/scripts/script_variant.hpp>

#include <range/v3/range_for.hpp>

#include <algorithm>
#include <unordered_set>
#include <unordered_map>

namespace blocksci {
namespace heuristics {


    // Peeling chains have one input and two outputs
    bool looksLikePeelingChain(const Transaction &tx) {
        return (tx.outputCount() == 2 && tx.inputCount() == 1);
    }

    // A transaction is considered a peeling chain if it has one input and two outputs,
    // and either the previous or one of the next transactions looks like a peeling chain.
    bool isPeelingChain(const Transaction &tx) {
        if (!looksLikePeelingChain(tx)) {
            return false;
        }
        // Check if past transaction is peeling chain
        if (looksLikePeelingChain(tx.inputs()[0].getSpentTx())) {
            return true;
        }
        // Check if any spending transaction is peeling chain
        RANGES_FOR(auto output, tx.outputs()) {
            if (output.isSpent() && looksLikePeelingChain(*output.getSpendingTx())) {
                return true;
            }
        }
        return false;
    }
    
    bool isCoinjoin(const Transaction &tx) {
        if (tx.inputCount() < 2 || tx.outputCount() < 3) {
            return false;
        }
        
        // Each participant contributes a spend and a change output
        uint16_t participantCount = (tx.outputCount() + 1) / 2;
        if (participantCount > tx.inputCount()) {
            return false;
        }
        
        std::unordered_set<Address> inputAddresses;
        RANGES_FOR (auto input, tx.inputs()) {
            inputAddresses.insert(input.getAddress());
        }
        
        if (participantCount > inputAddresses.size()) {
            return false;
        }
        
        std::unordered_map<int64_t, uint16_t> outputValues;
        RANGES_FOR (auto output, tx.outputs()) {
            outputValues[output.getValue()]++;
        }
        
        using pair_type = decltype(outputValues)::value_type;
        auto pr = std::max_element(std::begin(outputValues), std::end(outputValues),
                                   [] (const pair_type & p1, const pair_type & p2) {
                                       return p1.second < p2.second;
                                   }
                                   );
        // The most common output value should appear exactly `participantCount` times
        if (pr->second != participantCount) {
            return false;
        }
        
        // Exclude transactions sending dust outputs (unlikely to be CoinJoin)
        if (pr->first == 546 || pr->first == 2730) {
            return false;
        }
        
        return true;
    }
    
    struct OutputBucket {
        int64_t currentValue;
        int64_t goalValue;
        
        explicit OutputBucket(int64_t goal) : currentValue(0), goalValue(goal) {}
        
        bool isFull() const {
            return currentValue >= goalValue;
        }
        
        void addInput(int64_t val) {
            currentValue += val;
        }
        
        void removeInput(int64_t val) {
            currentValue -= val;
        }
        
        int64_t remaining() const {
            if (goalValue > currentValue) {
                return goalValue - currentValue;
            } else {
                return 0;
            }
        }
        
        bool operator<(const OutputBucket &other) const {
            return remaining() < other.remaining();
        }
    };
    
    CoinJoinResult _getSumCount(std::vector<int64_t> &values, std::vector<OutputBucket> buckets, int64_t totalRemaining, int64_t valueLeft, size_t maxDepth, size_t &depth);
    CoinJoinResult getSumCount(std::vector<int64_t> &values, std::vector<int64_t> bucketGoals, size_t maxDepth);
    
    
    CoinJoinResult _getSumCount(std::vector<int64_t> &values, std::vector<OutputBucket> buckets, int64_t totalRemaining, int64_t valueLeft, size_t maxDepth, size_t &depth) {
        if (totalRemaining > valueLeft) {
            return CoinJoinResult::False;
        }
        
        buckets.erase(std::remove_if(buckets.begin(), buckets.end(), [&](auto &bucket) { return bucket.isFull(); }), buckets.end());
        if (buckets.size() == 0) {
            return CoinJoinResult::True;
        }
        
        if (values.size() == 0) {
            return CoinJoinResult::False;
        }
        
        depth++;
        
        if (maxDepth != 0 && depth > maxDepth) {
            return CoinJoinResult::Timeout;
        }
        
        std::sort(buckets.rbegin(), buckets.rend());
        
        int64_t lastValue = values.back();
        values.pop_back();
        valueLeft -= lastValue;
        for (auto &bucket : buckets) {
            int64_t remaining = totalRemaining - bucket.remaining();
            bucket.addInput(lastValue);
            remaining += bucket.remaining();
            auto res = _getSumCount(values, buckets, remaining, valueLeft, maxDepth, depth);
            if (res != CoinJoinResult::False) {
                return res;
            }
            bucket.removeInput(lastValue);
        }
        values.push_back(lastValue);
        return CoinJoinResult::False;
    }
    
    
    CoinJoinResult getSumCount(std::vector<int64_t> &values, std::vector<int64_t> bucketGoals, size_t maxDepth) {
        std::sort(values.begin(), values.end());
        std::sort(bucketGoals.rbegin(), bucketGoals.rend());
        
        int64_t valueLeft = 0;
        for (auto value : values) {
            valueLeft += value;
        }
        
        int64_t totalRemaining = 0;
        for (auto goal : bucketGoals) {
            totalRemaining += goal;
        }
        
        std::vector<OutputBucket> buckets;
        buckets.reserve(bucketGoals.size());
        for (auto goal : bucketGoals) {
            buckets.emplace_back(goal);
        }
        size_t depth = 0;
        return _getSumCount(values, buckets, totalRemaining, valueLeft, maxDepth, depth);
    }
    
    
    CoinJoinResult isCoinjoinExtra(const Transaction &tx, int64_t minBaseFee, double percentageFee, size_t maxDepth) {
        if (tx.inputCount() < 2 || tx.outputCount() < 3) {
            return CoinJoinResult::False;
        }
        
        uint16_t participantCount = (tx.outputCount() + 1) / 2;
        if (participantCount > tx.inputCount()) {
            return CoinJoinResult::False;
        }
        
        std::unordered_map<Address, int64_t> inputValues;
        RANGES_FOR (auto input, tx.inputs()) {
            inputValues[input.getAddress()] += input.getValue();
        }
        
        if (participantCount > inputValues.size()) {
            return CoinJoinResult::False;
        }
        
        std::unordered_map<int64_t, std::unordered_set<Address>> outputValues;
        RANGES_FOR (auto output, tx.outputs()) {
            outputValues[output.getValue()].insert(output.getAddress());
        }
        
        using pair_type = decltype(outputValues)::value_type;
        auto pr = std::max_element(std::begin(outputValues), std::end(outputValues),
                                   [] (const pair_type & p1, const pair_type & p2) {
                                       return p1.second.size() < p2.second.size();
                                   }
                                   );
        
        
        if (pr->second.size() != participantCount) {
            return CoinJoinResult::False;
        }
        
        if (pr->first == 546 || pr->first == 2730) {
            return CoinJoinResult::False;
        }
        
        
        std::vector<int64_t> values;
        values.reserve(inputValues.size());
        for (auto &pair : inputValues) {
            values.push_back(pair.second);
        }
        
        int64_t goalValue = pr->first;
        
        int64_t maxPossibleFee = std::max(minBaseFee, static_cast<int64_t>(goalValue * percentageFee));
        
        std::vector<int64_t> bucketGoals;
        for (uint16_t i = 0; i < participantCount; i++) {
            bucketGoals.push_back(goalValue);
        }
        
        size_t j = 0;
        RANGES_FOR (auto output, tx.outputs()) {
            if (output.getValue() != goalValue) {
                bucketGoals[j] += output.getValue();
                j++;
            }
        }
        
        for (auto &goal : bucketGoals) {
            if (maxPossibleFee > goal) {
                goal = 0;
            } else {
                goal -= maxPossibleFee;
            }
        }
        
        return getSumCount(values, bucketGoals, maxDepth);
    }
    
    CoinJoinResult isPossibleCoinjoin(const Transaction &tx, int64_t minBaseFee, double percentageFee, size_t maxDepth) {
        
        if (tx.outputCount() == 1 || tx.inputCount() == 1) {
            return CoinJoinResult::False;
        }
        
        std::unordered_map<int64_t, uint16_t> outputValues;
        RANGES_FOR (auto output, tx.outputs()) {
            outputValues[output.getValue()]++;
        }
        
        using pair_type = decltype(outputValues)::value_type;
        auto pr = std::max_element(std::begin(outputValues), std::end(outputValues),
                                   [] (const pair_type & p1, const pair_type & p2) {
                                       return p1.second < p2.second;
                                   }
                                   );
        
        // There must be at least two outputs of equal value to create an anonymity set
        if (pr->second == 1) {
            return CoinJoinResult::False;
        }
        
        std::unordered_map<Address, int64_t> inputValues;
        RANGES_FOR (auto input, tx.inputs()) {
            inputValues[input.getAddress()] += input.getValue();
        }
        
        if (inputValues.size() == 1) {
            return CoinJoinResult::False;
        }
        
        std::vector<Output> unknownOutputs;
        RANGES_FOR (auto output, tx.outputs()) {
            if (inputValues.find(output.getAddress()) == inputValues.end()) {
                unknownOutputs.push_back(output);
            }
        }
        
        if (unknownOutputs.size() <= 1) {
            return CoinJoinResult::False;
        }
        
        outputValues.clear();
        for (auto &output : unknownOutputs) {
            outputValues[output.getValue()]++;
        }
        pr = std::max_element(std::begin(outputValues), std::end(outputValues),
                              [] (const pair_type & p1, const pair_type & p2) {
                                  return p1.second < p2.second;
                              }
                              );
        // There must be at least two outputs of equal value to create an anonymity set
        if (pr->second == 1) {
            return CoinJoinResult::False;
        }
        
        std::vector<int64_t> values;
        values.reserve(inputValues.size());
        for (auto &pair : inputValues) {
            values.push_back(pair.second);
        }
        
        int64_t maxPossibleFee = std::max(minBaseFee, static_cast<int64_t>(pr->first * percentageFee));
        int64_t goalValue = 0;
        if (pr->first > goalValue) {
            goalValue = pr->first - maxPossibleFee;
        }
        
        std::vector<int64_t> bucketGoals = {goalValue, goalValue};
        
        return getSumCount(values, bucketGoals, maxDepth);
    }
    
    bool isDeanonTx(const Transaction &tx) {
        if (tx.isCoinbase()) {
            return false;
        }
        
        if (tx.outputCount() == 1) {
            return false;
        }
        
        std::unordered_set<AddressType::Enum> inputCounts;
        RANGES_FOR (auto input, tx.inputs()) {
            inputCounts.insert(input.getAddress().type);
        }
        
        if (inputCounts.size() != 1) {
            return false;
        }
        
        AddressType::Enum inputType = *inputCounts.begin();
        
        bool seenType = false;
        RANGES_FOR (auto output, tx.outputs()) {
            if (output.getType() == inputType) {
                if (seenType) {
                    return false;
                }
                seenType = true;
            }
        }
        
        return seenType;
    }
    
    namespace {
        ranges::optional<Address> getInsidePointer(const ranges::optional<Address> &address, DataAccess &access);

        ranges::optional<Address> getInsidePointer(const Address &pointer, DataAccess &access) {
            if (pointer.type == AddressType::Enum::SCRIPTHASH) {
                script::ScriptHash scriptHashAddress(pointer.scriptNum, access);
                return getInsidePointer(scriptHashAddress.getWrappedAddress(), access);
            } else if(pointer.type == AddressType::Enum::WITNESS_SCRIPTHASH) {
                script::WitnessScriptHash witnessScriptHashAddress(pointer.scriptNum, access);
                return getInsidePointer(witnessScriptHashAddress.getWrappedAddress(), access);
            } else if(pointer.type == AddressType::Enum::WITNESS_TAPROOTHASH) {
                script::WitnessTaprootHash witnessTaprootHashAddress(pointer.scriptNum, access);
                return getInsidePointer(witnessTaprootHashAddress.getWrappedAddress(), access);
            } else {
                return pointer;
            }
        }
        
        ranges::optional<Address> getInsidePointer(const ranges::optional<Address> &address, DataAccess &access) {
            if (address) {
                return getInsidePointer(*address, access);
            } else {
                return ranges::nullopt;
            }
        }
    }
    
    
    struct DetailedType {
        AddressType::Enum mainType;
        bool hasSubtype;
        AddressType::Enum subType;
        int i;
        int j;
        
        DetailedType(const Address &pointer, DataAccess &access) : mainType(pointer.type), hasSubtype(false), subType(AddressType::Enum::NONSTANDARD), i(0), j(0) {
            auto insidePointer = getInsidePointer(pointer, access);
            if (insidePointer) {
                subType = insidePointer->type;
                hasSubtype = true;
                if (subType == AddressType::Enum::MULTISIG) {
                    script::Multisig multisigAddress(insidePointer->scriptNum, access);
                    i = multisigAddress.getRequired();
                    j = static_cast<int>(multisigAddress.getTotal());
                }
            }
        }
        
        bool operator==(const DetailedType &other) const {
            if (mainType != other.mainType || subType != other.subType) {
                return false;
            }
            if (mainType == AddressType::Enum::SCRIPTHASH && (!hasSubtype || !other.hasSubtype)) {
                return false;
            }
            if (mainType == AddressType::Enum::WITNESS_SCRIPTHASH && (!hasSubtype || !other.hasSubtype)) {
                return false;
            }
            if (mainType == AddressType::Enum::WITNESS_TAPROOTHASH && (!hasSubtype || !other.hasSubtype)) {
                return false;
            }
            if (subType == AddressType::Enum::MULTISIG && (i != other.i || j != other.j)) {
                return false;
            }
            
            return true;
        }
        
        bool operator!=(const DetailedType &other) const {
            return !operator==(other);
        }
    };
    
    struct DetailedTypeHasher {
        size_t operator()(const DetailedType& b) const {
            std::size_t seed = 123945432;
            hash_combine(seed, b.mainType);
            if (b.hasSubtype) {
                hash_combine(seed, b.subType);
            }
            if (b.subType == AddressType::Enum::MULTISIG) {
                hash_combine(seed, b.i);
                hash_combine(seed, b.j);
            }
            return seed;
        }
    };
    
    bool isChangeOverTx(const Transaction &tx) {
        if (tx.isCoinbase()) {
            return false;
        }
        
        std::unordered_set<DetailedType, DetailedTypeHasher> outputTypes;
        RANGES_FOR (auto output, tx.outputs()) {
            outputTypes.insert(DetailedType{output.getAddress(), tx.getAccess()});
        }
        
        if (outputTypes.size() != 1) {
            return false;
        }
        
        std::unordered_set<DetailedType, DetailedTypeHasher> inputTypes;
        RANGES_FOR (auto input, tx.inputs()) {
            inputTypes.insert(DetailedType{input.getAddress(), tx.getAccess()});
        }
        
        if (inputTypes.size() != 1) {
            return false;
        }
        
        return *outputTypes.begin() != *inputTypes.begin();
    }
    
    bool containsKeysetChange(const Transaction &tx) {
        if (tx.isCoinbase()) {
            return false;
        }
        
        std::unordered_set<Address> multisigOutputs;
        RANGES_FOR (auto output, tx.outputs()) {
            auto pointer = getInsidePointer(output.getAddress(), tx.getAccess());
            if (pointer && pointer->type == AddressType::Enum::MULTISIG) {
                multisigOutputs.insert(*pointer);
            }
        }
        
        if (multisigOutputs.size() == 0) {
            return false;
        }
        
        std::unordered_set<Address> multisigInputs;
        RANGES_FOR (auto input, tx.inputs()) {
            auto pointer = getInsidePointer(input.getAddress(), tx.getAccess());
            if (pointer && pointer->type == AddressType::Enum::MULTISIG) {
                if (multisigOutputs.find(*pointer) == multisigOutputs.end()) {
                    multisigInputs.insert(*pointer);
                }
            }
        }
        
        if (multisigInputs.size() == 0) {
            return false;
        }
        
        std::unordered_set<Address> containedOutputs;
        for (auto &pointer : multisigOutputs) {
            std::function<void(const blocksci::Address &)> visitFunc = [&](const blocksci::Address &add) {
                containedOutputs.insert(add);
            };
            pointer.getScript().visitPointers(visitFunc);
        }
        
        for (auto &pointer : multisigInputs) {
            bool foundMatch = false;
            std::function<void(const blocksci::Address &)> visitFunc = [&](const blocksci::Address &add) {
                if (containedOutputs.find(add) != containedOutputs.end()) {
                    foundMatch = true;
                    return;
                }
            };
            pointer.getScript().visitPointers(visitFunc);
            if (foundMatch) {
                return true;
            }
        }
        
        return false;
    }
}}
