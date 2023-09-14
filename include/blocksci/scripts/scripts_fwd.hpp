//
//  scriptsfwd.hpp
//  blocksci
//
//  Created by Harry Kalodner on 9/4/17.
//
//

#ifndef scriptsfwd_h
#define scriptsfwd_h

#include <blocksci/core/address_types.hpp>
#include <blocksci/core/address_type_meta.hpp>

namespace mpark {
    template <typename... Types>
    class variant;
} // namespace mpark

namespace blocksci {
    class CBitcoinAddress;
    class CKeyID;
    class CPubKey;
    struct DataConfiguration;
    
    class ScriptBase;
    
    class AnyScript;
    class CScriptView;
    
    template <AddressType::Enum>
    class ScriptAddress;

    class ScriptAccess;
    
    using ScriptVariant = to_variadic_t<to_address_tuple_t<ScriptAddress>, mpark::variant>;
    
    namespace script {
        using Pubkey = ScriptAddress<AddressType::PUBKEY>;
        using PubkeyHash = ScriptAddress<AddressType::PUBKEYHASH>;
        using MultisigPubkey = ScriptAddress<AddressType::MULTISIG_PUBKEY>;
        using WitnessPubkeyHash = ScriptAddress<AddressType::WITNESS_PUBKEYHASH>;
        using ScriptHash = ScriptAddress<AddressType::SCRIPTHASH>;
        using WitnessScriptHash = ScriptAddress<AddressType::WITNESS_SCRIPTHASH>;
        using WitnessTaprootHash = ScriptAddress<AddressType::WITNESS_TAPROOTHASH>;
        using Multisig = ScriptAddress<AddressType::MULTISIG>;
        using OpReturn = ScriptAddress<AddressType::NULL_DATA>;
        using Nonstandard = ScriptAddress<AddressType::NONSTANDARD>;
        using WitnessUnknown = ScriptAddress<AddressType::WITNESS_UNKNOWN>;
    }
} // namespace blocksci

#endif /* scriptsfwd_h */
