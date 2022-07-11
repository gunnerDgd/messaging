#pragma once
#include <messaging/route/details/route_type.h>

__synapse_messaging_route*
	__synapse_messaging_route_initialize
		(synapse_memory_manager*);

void
	__synapse_messaging_route_cleanup
		(__synapse_messaging_route*);