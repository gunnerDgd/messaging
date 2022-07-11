#pragma once
#include <synapse/memory/interface/memory_manager.h>
#include <synapse/messaging/defines/handle/opaque.h>

#include <structure/list/double_linked.h>

#include <Windows.h>

typedef struct
	__synapse_messaging_endpoint
{
	HANDLE
		ep_hnd_notifier,
		ep_hnd_lock;

	synapse_structure_double_linked
		ep_hnd_message;
	synapse_memory_block
		ep_hnd_mblock;
} __synapse_messaging_endpoint;