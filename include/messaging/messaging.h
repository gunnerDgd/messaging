#pragma once
#include <messaging/interface/messaging.h>
#include <messaging/defines/export/export.h>



synapse_messaging_dll
	synapse_messaging_endpoint
		synapse_create_messaging_endpoint
			(const char*);

synapse_messaging_dll
	void
		synapse_delete_messaging_endpoint
			(synapse_messaging_endpoint);

synapse_messaging_dll
	synapse_messaging_endpoint
		synapse_retrieve_messaging_endpoint
			(const char*);

synapse_messaging_dll
	void
		synapse_send_message
			(synapse_messaging_endpoint, uint16_t, void*, size_t);

synapse_messaging_dll
	synapse_messaging_message
		synapse_receive_message
			(synapse_messaging_endpoint);

synapse_messaging_dll
	void
		synapse_expire_message
			(synapse_messaging_message);

synapse_messaging_dll
	void*
		synapse_message_data
			(synapse_messaging_message);

synapse_messaging_dll
	size_t
		synapse_message_size
			(synapse_messaging_message);

synapse_messaging_dll
	uint16_t
		synapse_message_opcode
			(synapse_messaging_message);