#include <messaging/endpoint/endpoint_init.h>
#include <messaging/route/details/route_endpoint.h>

#include <memory/mman/standard_heap/stdheap.h>
#include <stdio.h>
synapse_messaging_endpoint
	synapse_messaging_endpoint_initialize
		(synapse_messaging_route pRoute, 
		 const char*			 pEndpointName)
{
	synapse_messaging_opaque_handle_init
		(synapse_messaging_endpoint, hnd_endpoint,
			__synapse_messaging_route_create_endpoint
					(synapse_messaging_opaque_handle_reference
						(pRoute), pEndpointName));

	return
		hnd_endpoint;
}

void
	synapse_messaging_endpoint_cleanup
		(synapse_messaging_route pRoute, synapse_messaging_endpoint pEndpoint)
{
	__synapse_messaging_route_delete_endpoint
		(synapse_messaging_opaque_handle_reference
			(pRoute),
		 synapse_messaging_opaque_handle_reference
			(pEndpoint));
}

synapse_messaging_endpoint
	synapse_messaging_endpoint_retrieve
		(synapse_messaging_route pRoute, const char* pName)
{
	synapse_messaging_opaque_handle_init
		(synapse_messaging_endpoint, hnd_endpoint,
			__synapse_messging_route_retrieve_endpoint
				(synapse_messaging_opaque_handle_reference(pRoute),
					pName));

	return
		hnd_endpoint;
}