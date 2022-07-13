cmake_minimum_required(VERSION 3.11)

if(SYNAPSE_MESSAGING_STANDALONE_BUILD)
    project
    (
        synapse-messaging
        VERSION 0.1.0
        DESCRIPTION "Messaging Layer for Synapse Framework"
        LANGUAGES C
    )
endif()

add_subdirectory(source/c)