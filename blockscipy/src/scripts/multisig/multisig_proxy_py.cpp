//
//  multisig_proxy_py.cpp
//  blocksci
//
//  Created by Harry Kalodner on 9/22/18.
//
//

#include "multisig_proxy_py.hpp"
#include "multisig_py.hpp"
#include "scripts/address_py.hpp"
#include "proxy_apply_py.hpp"
#include "proxy/basic.hpp"
#include "proxy/equality.hpp"
#include "proxy/optional.hpp"
#include "proxy/range.hpp"

#include <blocksci/chain/block.hpp>
#include <blocksci/cluster/cluster.hpp>
#include <blocksci/scripts/multisig_script.hpp>

struct AddMultisigMethods {
    template <typename FuncApplication>
    void operator()(FuncApplication func) {
        func(property_tag, "required", &blocksci::script::Multisig::getRequired, "The number of signatures required for this address");
		func(property_tag, "total", &blocksci::script::Multisig::getTotal, "The total number of keys that can sign for this address");
		func(property_tag, "addresses", +[](blocksci::script::Multisig &address) -> RawRange<blocksci::script::MultisigPubkey> {
            return address.pubkeyScripts();
        }, "The list of the keys that can sign for this address");
    }
};

void addMultisigProxyMethods(AllProxyClasses<blocksci::script::Multisig, ProxyAddress> &cls) {
	cls.applyToAll(AddProxyMethods{});
    setupRangesProxy(cls);
    addProxyOptionalMethods(cls.optional);

	applyMethodsToProxy(cls.base, AddMultisigMethods{});
    addProxyEqualityMethods(cls.base);
}
