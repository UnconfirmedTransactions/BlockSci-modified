//
//  witness_pubkeyhash_proxy_py.cpp
//  blocksci
//
//  Created by Harry Kalodner on 9/22/18.
//
//

#include "witness_pubkeyhash_proxy_py.hpp"
#include "scripts/pubkey/pubkey_proxy_impl.hpp"
#include "scripts/address_py.hpp"
#include "proxy_apply_py.hpp"
#include "proxy/basic.hpp"
#include "proxy/equality.hpp"
#include "proxy/optional.hpp"
#include "proxy/range.hpp"

#include <blocksci/chain/block.hpp>
#include <blocksci/cluster/cluster.hpp>
#include <blocksci/scripts/pubkey_script.hpp>

void addWitnessPubkeyHashProxyMethods(AllProxyClasses<blocksci::script::WitnessPubkeyHash, ProxyAddress> &cls) {
	cls.applyToAll(AddProxyMethods{});
    setupRangesProxy(cls);
    addProxyOptionalMethods(cls.optional);
 
	applyMethodsToProxy(cls.base, AddPubkeyBaseMethods<blocksci::script::WitnessPubkeyHash>{});
    addProxyEqualityMethods(cls.base);
}
