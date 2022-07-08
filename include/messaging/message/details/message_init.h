#pragma once
#include <messaging/message/details/message_type.h>

__synapse_messaging_message*
	__synapse_messaging_message_initialize
		(synapse_memory_mman_traits*, uint16_t, void*, size_t);

void
	__synapse_messaging_message_cleanup
		(synapse_memory_mman_traits*, __synapse_messaging_message*);