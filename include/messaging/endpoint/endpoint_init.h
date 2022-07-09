#pragma once
#include <messaging/interface/messaging.h>

synapse_messaging_endpoint
	synapse_messaging_endpoint_initialize
		(synapse_messaging_route, const char*);

void
	synapse_messaging_endpoint_cleanup
		(synapse_messaging_route, synapse_messaging_endpoint);

synapse_messaging_endpoint
	synapse_messaging_endpoint_retrieve
		(synapse_messaging_route, const char*);