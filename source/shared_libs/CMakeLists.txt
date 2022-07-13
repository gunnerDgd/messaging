cmake_minimum_required(VERSION 3.0)

project(
    synapse-messaging-dll
    VERSION 0.1.0
    LANGUAGES C
)

add_library(
    synapse_messaging_dll
    STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
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
