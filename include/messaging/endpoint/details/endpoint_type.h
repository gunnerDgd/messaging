#pragma once
#include <messaging/defines/handle/opaque.h>
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
	synapse_memory_mman_traits*
		ep_hnd_message_mman;
	synapse_memory_mman_block
		ep_hnd_mblock;
} __synapse_messaging_endpoint;