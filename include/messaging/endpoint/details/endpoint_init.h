#pragma once
#include <messaging/endpoint/details/endpoint_type.h>

__synapse_messaging_endpoint*
	__synapse_messaging_endpoint_initialize
		(synapse_memory_manager*);

void
	__synapse_messaging_endpoint_cleanup
		(__synapse_messaging_endpoint*);