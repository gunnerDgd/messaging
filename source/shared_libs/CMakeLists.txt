cmake_minimum_required(VERSION 3.0)

project(
    synapse-messaging-dll
    VERSION 0.1.0
    LANGUAGES C
)

file(
    GLOB_RECURSE src_synapse_messaging_dll CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(
    synapse_messaging_dll
    SHARED
    ${src_synapse_messaging_dll}
)

target_include_directories(
    synapse_messaging_dll
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

target_include_directories(
    synapse_messaging_dll
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
    synapse_messaging_dll
    synapse_memory_dll
)

target_link_libraries(
    synapse_messaging_dll
    synapse_messaging_lib
)

target_link_libraries(
    synapse_messaging_dll
    synapse_structure_dlist_lib
)

target_compile_options(
    synapse_messaging_dll PRIVATE /Dsynapse_messaging_export_mode
)