#pragma once
#include <messaging/interface/messaging.h>

void
	synapse_messaging_endpoint_send_to
		(synapse_messaging_route, synapse_messaging_endpoint, uint16_t, void*, size_t);

synapse_messaging_message
	synapse_messaging_endpoint_receive_from
		(synapse_messaging_route, synapse_messaging_endpoint);

void
	synapse_messaging_endpoint_expire_message
		(synapse_messaging_route, synapse_messaging_message);