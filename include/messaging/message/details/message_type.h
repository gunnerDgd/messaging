#pragma once
#include <messaging/defines/handle/opaque.h>
#include <memory/mman/mman_traits.h>

typedef struct
	__synapse_messaging_message
{
	uint16_t
		msg_opcode;
	void*
		msg_field_ptr;
	size_t
		msg_field_size;
	synapse_memory_mman_block
		msg_mman_block;
} __synapse_messaging_message;