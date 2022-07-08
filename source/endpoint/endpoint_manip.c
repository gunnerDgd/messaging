#include <messaging/endpoint/endpoint_manip.h>
#include <messaging/route/details/route_endpoint.h>

void
	synapse_messaging_endpoint_send_to
		(synapse_messaging_route    pRoute, 
		 synapse_messaging_endpoint pEndpoint, 
		 uint16_t					pMessageOpcode, 
		 void*					    pMessageField, 
		 size_t						pMessageFieldSize)
{
	__synapse_messaging_route_send_to
		(synapse_messaging_opaque_handle_reference
			(pRoute),
		 synapse_messaging_opaque_handle_reference
			(pEndpoint),
				pMessageOpcode, pMessageField, pMessageFieldSize);
}

synapse_messaging_message
	synapse_messaging_endpoint_receive_from
		(synapse_messaging_route pRoute, synapse_messaging_endpoint pEndpoint)
{
	synapse_messaging_opaque_handle_init
		(synapse_messaging_message, hnd_message,
			__synapse_messaging_route_receive_from
				(synapse_memory_opaque_reference
					(pRoute),
				 synapse_memory_opaque_reference
					(pEndpoint)));

	return
		hnd_message;
}

void
	synapse_messaging_endpoint_expire_message
		(synapse_messaging_route pRoute, synapse_messaging_message pMessage)
{
	__synapse_messaging_route_expire
		(synapse_memory_opaque_reference
			(pRoute),
		 synapse_memory_opaque_reference
			(pMessage));
}