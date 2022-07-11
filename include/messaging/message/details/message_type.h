#pragma once
#include <synapse/messaging/defines/handle/opaque.h>
#include <synapse/memory/interface/memory_manager.h>

typedef struct
	__synapse_messaging_message
{
	uint16_t
		msg_opcode;
	void*
		msg_field_ptr;
	size_t
		msg_field_size;
	synapse_memory_block
		msg_mman_block;
} __synapse_messaging_message;