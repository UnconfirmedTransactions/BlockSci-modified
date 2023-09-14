//
//  address_proxy_py.hpp
//  blocksci
//
//  Created by Harry Kalodner on 3/28/18.
//

#ifndef address_proxy_py_h
#define address_proxy_py_h

#include "python_fwd.hpp"

#include <blocksci/scripts/scripts_fwd.hpp>

#include <pybind11/pybind11.h>

void init_proxy_address(pybind11::class_<ProxyAddress, SimpleProxy> &addressCl);

void addAddressProxyMethods(AllProxyClasses<blocksci::AnyScript, ProxyAddress> &cls);

#endif /* address_proxy_py_h */
