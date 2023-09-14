FIND_PACKAGE(JSONCPP REQUIRED)
FIND_PACKAGE(JSONRPCCPP REQUIRED)
FIND_PACKAGE(CURL REQUIRED)

add_library(curl INTERFACE)
target_link_libraries(curl INTERFACE ${CURL_LIBRARIES})
target_include_directories(curl INTERFACE ${CURL_INCLUDE_DIRS})

add_library(jsoncpp INTERFACE)
target_link_libraries(jsoncpp INTERFACE ${JSONCPP_LIBRARIES})
target_include_directories(jsoncpp INTERFACE ${JSONCPP_INCLUDE_DIRS})

add_library(jsonrpccpp INTERFACE)
target_link_libraries(jsonrpccpp INTERFACE ${JSONRPCCPP_LIBRARIES})
target_include_directories(jsonrpccpp INTERFACE ${JSONRPCCPP_INCLUDE_DIRS})

# Find header and source files
FILE(GLOB bitcoinapi_header ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
FILE(GLOB bitcoinapi_source ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Set target libraries
ADD_LIBRARY(bitcoinapi SHARED ${bitcoinapi_source})
ADD_LIBRARY(bitcoinapi_static STATIC ${bitcoinapi_source})

# Set output name of static library
SET_TARGET_PROPERTIES(bitcoinapi_static PROPERTIES OUTPUT_NAME bitcoinapi)



# Link the library with json-rpc-cpp libs
TARGET_LINK_LIBRARIES(bitcoinapi
                        curl
                        jsoncpp
                        jsonrpccpp)

TARGET_LINK_LIBRARIES(bitcoinapi_static
                        curl
                        jsoncpp
                        jsonrpccpp)

target_include_directories(bitcoinapi INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(bitcoinapi_static INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)

# Set version settings
SET(VERSION_STRING ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})
SET_TARGET_PROPERTIES(bitcoinapi bitcoinapi_static PROPERTIES
    VERSION "${VERSION_STRING}"
    SOVERSION "${SO_VERSION}")

# Install to appropriate destinations
INSTALL(FILES ${bitcoinapi_header} DESTINATION include/bitcoinapi)

INSTALL(TARGETS bitcoinapi bitcoinapi_static
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib)
