#pragma once
#include <synapse/memory/interface/memory_manager.h>
#include <structure/list/double_linked.h>

#include <messaging/endpoint/details/endpoint_type.h>
#include <messaging/message/details/message_type.h>

typedef struct
	__synapse_messaging_route_endpoint
{
	__synapse_messaging_endpoint*
		rt_endpoint;
	HANDLE
		rt_endpoint_thread;
	DWORD
		rt_endpoint_thread_id;

	const char*
		rt_endpoint_identifier;
	size_t
		rt_endpoint_identifier_length;

	synapse_memory_block
		rt_endpoint_mblock;
	synapse_structure_double_linked_node
		rt_endpoint_handle;
} __synapse_messaging_route_endpoint;

typedef struct
	__synapse_messaging_route
{
	synapse_structure_double_linked
		 rt_handle;
	
	synapse_memory_manager
		*rt_mman_route;
	synapse_memory_block
		 rt_mblock;
} __synapse_messaging_route;