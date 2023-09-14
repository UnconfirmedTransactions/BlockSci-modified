//
//  cluster_proxy_py.hpp
//  blocksci
//
//  Created by Harry Kalodner on 3/28/18.
//

#ifndef cluster_proxy_py_h
#define cluster_proxy_py_h

#include "python_fwd.hpp"

#include <blocksci/cluster/cluster_fwd.hpp>

void addClusterProxyMethods(AllProxyClasses<blocksci::Cluster> &cls);

#endif /* block_proxy_py_h */
