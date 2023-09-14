//
//  input_py.hpp
//  blocksci
//
//  Created by Harry Kalodner on 12/12/17.
//
//

#ifndef input_py_hpp
#define input_py_hpp

#include "python_fwd.hpp"

#include <blocksci/chain/chain_fwd.hpp>

#include <pybind11/pybind11.h>

void init_input(pybind11::class_<blocksci::Input> &cl);
void addInputRangeMethods(RangeClasses<blocksci::Input> &classes);

#endif /* input_py_hpp */
