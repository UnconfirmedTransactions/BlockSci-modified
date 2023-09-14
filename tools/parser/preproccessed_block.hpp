//
//  preproccessed_block.hpp
//  BlockParser2
//
//  Created by Harry Kalodner on 1/10/17.
//  Copyright © 2017 Harry Kalodner. All rights reserved.
//

#ifndef preproccessed_block_hpp
#define preproccessed_block_hpp

#include "config.hpp"
#include "script_output.hpp"
#include "script_input.hpp"
#include "utxo.hpp"

#include <blocksci/core/bitcoin_uint256.hpp>

#include <boost/container/small_vector.hpp>

struct getrawtransaction_t;
struct vout_t;
struct vin_t;
struct InputView;

namespace blocksci {
    struct RawTransaction;
}

std::vector<unsigned char> hexStringToVec(const std::string &scripthex);

class SafeMemReader;

struct WitnessStackItem {
    uint32_t length = 0;
    const char *itemBegin = nullptr;
    
    WitnessStackItem(const char *itemBegin_, uint32_t length_) : length(length_), itemBegin(itemBegin_) {}
    
    #ifdef BLOCKSCI_FILE_PARSER
    WitnessStackItem(SafeMemReader &reader);
    #endif
};

struct RawInput {
private:
    const unsigned char *scriptBegin = nullptr;
    uint32_t scriptLength = 0;
    
    std::vector<unsigned char> scriptBytes;
    
    std::vector<WitnessStackItem> witnessStack;
    
    std::vector<std::vector<char>> rpcWitnessStack;
    
public:
    
    RawOutputPointer rawOutputPointer;
    uint32_t sequenceNum;
    
    
    
    UTXO utxo;
    
    blocksci::InoutPointer getOutputPointer() const;
    
    blocksci::CScriptView getScriptView() const {
        if (scriptLength == 0) {
            return blocksci::CScriptView(scriptBytes.data(), scriptBytes.data() + scriptBytes.size());
        } else {
            return blocksci::CScriptView(scriptBegin, scriptBegin + scriptLength);
        }
    }
    
    std::vector<WitnessStackItem> getWitnessStack() const {
        if (witnessStack.size() == 0) {
            std::vector<WitnessStackItem> realStack;
            for (const auto &witnessItem : rpcWitnessStack) {
                realStack.emplace_back(witnessItem.data(), static_cast<uint32_t>(witnessItem.size()));
            }
            return realStack;
        } else {
            return witnessStack;
        }
    }
    
    RawInput() : utxo{} {}
    
    #ifdef BLOCKSCI_FILE_PARSER
    RawInput(SafeMemReader &reader);
    void readWitnessStack(SafeMemReader &reader);
    #endif
    
    #ifdef BLOCKSCI_RPC_PARSER
    RawInput(const vin_t &vin);
    #endif
};

struct RawOutput {
private:
    const unsigned char *scriptBegin = nullptr;
    uint32_t scriptLength = 0;
    
    std::vector<unsigned char> scriptBytes;
public:
    int64_t value;

    #ifdef BLOCKSCI_FILE_PARSER
    RawOutput(SafeMemReader &reader);
    #endif
    
    #ifdef BLOCKSCI_RPC_PARSER
    RawOutput(const vout_t &vout);
    RawOutput(std::vector<unsigned char> scriptBytes_, int64_t value_);
    #endif
    
    blocksci::CScriptView getScriptView() const {
        if (scriptLength == 0) {
            return blocksci::CScriptView(scriptBytes.data(), scriptBytes.data() + scriptBytes.size());
        } else {
            return blocksci::CScriptView(scriptBegin, scriptBegin + scriptLength);
        }
    }
};

struct TransactionHeader {
    int32_t version = 0;
    uint32_t inputCount = 0;
    uint32_t outputCount = 0;
    uint32_t baseSize = 0;
    uint32_t realSize = 0;
    uint32_t locktime = 0;
    TransactionHeader(SafeMemReader &reader);
};

struct RawTransaction {
    uint32_t txNum;
    blocksci::uint256 hash;
    uint32_t baseSize = 0;
    uint32_t realSize = 0;
    uint32_t locktime = 0;
    int32_t version = 0;
    blocksci::BlockHeight blockHeight;
    bool isSegwit;
    bool isTaproot;
    const char *txHashStart;
    uint32_t txHashLength;
    
    boost::container::small_vector<RawInput, 4> inputs;
    boost::container::small_vector<RawOutput, 4> outputs;
    boost::container::small_vector<AnyScriptInput, 4> scriptInputs;
    boost::container::small_vector<AnyScriptOutput, 4> scriptOutputs;
    
    
    RawTransaction() :
      txNum(0),
      hash(),
      baseSize(0),
      realSize(0),
      locktime(0),
      version(0),
      blockHeight(0) {}
    
    #ifdef BLOCKSCI_FILE_PARSER
    void load(SafeMemReader &reader, uint32_t txNum, blocksci::BlockHeight blockHeight, bool witnessActivated, bool taprootActivated);
    #endif
    
    #ifdef BLOCKSCI_RPC_PARSER
    void load(const getrawtransaction_t &txinfo, uint32_t txNum, blocksci::BlockHeight blockHeight, bool witnessActivated, bool taprootActivated);
    #endif
    
    void calculateHash();
    
    blocksci::uint256 getHash(const InputView &info, const blocksci::CScriptView &scriptView, int hashType) const;
    blocksci::RawTransaction getRawTransaction() const;
    
    std::vector<char> getSer(const InputView &info, const blocksci::CScriptView &scriptView, int hashType) const;
};


#endif /* preproccessed_block_hpp */
