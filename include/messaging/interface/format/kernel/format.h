#pragma once
#include <messaging/interface/format/kernel/format_modules.h>

#define synapse_messaging_kernel_initialize 0
#define synapse_messaging_kernel_cleanup    1
#define synapse_messaging_kernel_debug		2

typedef struct
	synapse_messaging_kernel_message
{
	uint16_t
		krnl_opcode;
	union
	{
		synapse_messaging_kernel_message_modules
			krnl_message_modules;
	};
} synapse_messaging_kernel_message;