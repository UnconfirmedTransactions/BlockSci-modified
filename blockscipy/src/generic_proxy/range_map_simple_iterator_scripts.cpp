//
//  range_map_simple_iterator.cpp
//  blocksci
//
//  Created by Harry Kalodner on 9/22/18.
//
//

#include "range_map.hpp"
#include "range_map_simple_impl.hpp"

#include <blocksci/address/equiv_address.hpp>
#include <blocksci/cluster/cluster.hpp>

void applyProxyMapFuncsScripts(pybind11::class_<IteratorProxy, GenericProxy> &cl) {
	addProxyMapFuncsMethodsScripts<ranges::category::input>(cl);
}