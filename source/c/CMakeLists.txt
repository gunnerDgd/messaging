cmake_minimum_required(VERSION 3.0.0)

file(
    GLOB_RECURSE src_synapse_messaging_lib CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(
    synapse_messaging_lib
    STATIC
    ${src_synapse_messaging_lib}
)

target_include_directories(
    synapse_messaging_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

target_include_directories(
    synapse_messaging_lib
    PUBLIC
    ${CMAKE_SOURCE_DIR}/submodules/synapse-memory/include
)
