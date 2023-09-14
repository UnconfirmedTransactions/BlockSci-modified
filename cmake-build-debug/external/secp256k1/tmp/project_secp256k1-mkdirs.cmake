# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/daslab/BlockSci-daslab/cmake-build-debug/external/secp256k1/src/project_secp256k1"
  "/home/daslab/BlockSci-daslab/cmake-build-debug/external/secp256k1/src/project_secp256k1-build"
  "/home/daslab/BlockSci-daslab/cmake-build-debug/external/secp256k1"
  "/home/daslab/BlockSci-daslab/cmake-build-debug/external/secp256k1/tmp"
  "/home/daslab/BlockSci-daslab/cmake-build-debug/external/secp256k1/src/project_secp256k1-stamp"
  "/home/daslab/BlockSci-daslab/cmake-build-debug/external/secp256k1/src"
  "/home/daslab/BlockSci-daslab/cmake-build-debug/external/secp256k1/src/project_secp256k1-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/daslab/BlockSci-daslab/cmake-build-debug/external/secp256k1/src/project_secp256k1-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/daslab/BlockSci-daslab/cmake-build-debug/external/secp256k1/src/project_secp256k1-stamp${cfgdir}") # cfgdir has leading slash
endif()
