#pragma once
#include <messaging/route/details/route_type.h>

__synapse_messaging_route_endpoint*
	__synapse_messaging_route_create_endpoint
		(__synapse_messaging_route*, const char*, void(*)(void*), void*);

void
	__synapse_messaging_route_delete_endpoint
		(__synapse_messaging_route*, __synapse_messaging_route_endpoint*);

__synapse_messaging_route_endpoint*
	__synapse_messging_route_retrieve_endpoint
		(__synapse_messaging_route*, const char*);

void
	__synapse_messaging_route_send_to
		(__synapse_messaging_route*, __synapse_messaging_route_endpoint*, uint16_t, void*, size_t);

__synapse_messaging_message*
	__synapse_messaging_route_receive_from
		(__synapse_messaging_route*, __synapse_messaging_route_endpoint*);

void
	__synapse_messaging_route_expire
		(__synapse_messaging_route*, __synapse_messaging_message*);