cmake_minimum_required(VERSION 3.0)

project(
    synapse-messaging
    VERSION 0.1.0
    DESCRIPTION "Messaging Layer for Synapse Framework"
    LANGUAGES C
)

add_subdirectory(source/c)
add_subdirectory(source/cpp)