//
//  witness_unkown_script.hpp
//  blocksci
//
//  Created by Harry Kalodner on 10/22/18.
//
//

#ifndef witness_unkown_script_hpp
#define witness_unkown_script_hpp

#include "script.hpp"

#include <blocksci/blocksci_export.h>
#include <blocksci/core/hash_combine.hpp>

#include <range/v3/utility/optional.hpp>

#include <string>

namespace blocksci {
    template <>
    class BLOCKSCI_EXPORT ScriptAddress<AddressType::WITNESS_UNKNOWN> : public ScriptBase {
        const WitnessUnknownSpendScriptData *rawInputData;
        
        const WitnessUnknownScriptData *getData() const {
            return reinterpret_cast<const WitnessUnknownScriptData *>(ScriptBase::getData());
        }
        
    public:
        constexpr static AddressType::Enum addressType = AddressType::WITNESS_UNKNOWN;
        
        ScriptAddress() = default;
        ScriptAddress(uint32_t scriptNum_, std::tuple<const WitnessUnknownScriptData *, const WitnessUnknownSpendScriptData *> &&rawData_, DataAccess &access_) : ScriptBase(scriptNum_, addressType, access_, std::get<0>(rawData_)), rawInputData(std::get<1>(rawData_)) {}
        ScriptAddress(uint32_t addressNum_, DataAccess &access_);
        
        CScriptView getWitnessScript() const;
        ranges::optional<ranges::any_view<ranges::any_view<unsigned char>>> getWitnessStack() const;
        
        std::string getWitnessScriptString() const;
        uint8_t witnessVersion() const;
        
        std::string toString() const;
        std::string toPrettyString() const;
    };
} // namespace blocksci

namespace std {
    template<> struct BLOCKSCI_EXPORT hash<blocksci::ScriptAddress<blocksci::AddressType::WITNESS_UNKNOWN>> {
        size_t operator()(const blocksci::ScriptAddress<blocksci::AddressType::WITNESS_UNKNOWN> &address) const {
            std::size_t seed = 32847956;
            blocksci::hash_combine(seed, static_cast<const blocksci::ScriptBase &>(address));
            return seed;
        }
    };
} // namespace std

#endif /* witness_unkown_script_hpp */
