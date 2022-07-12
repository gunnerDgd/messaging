#pragma once
#include <messaging/interface/format/kernel/format_modules.h>

#define synapse_messaging_kernel_cleanup 1

typedef struct
	synapse_messaging_kernel_message
{
	uint16_t
		krnl_opcode;
} synapse_messaging_kernel_message;