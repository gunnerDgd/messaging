#include <messaging/route/details/route_init.h>

__synapse_messaging_route*
	__synapse_messaging_route_initialize
		(synapse_memory_mman_traits* pMmanRoute, synapse_memory_mman_traits* pMmanMessage)
{
	synapse_memory_mman_block
		hnd_block
			= pMmanRoute->allocate
					(pMmanRoute->hnd_mman, NULL, sizeof(__synapse_messaging_route));

	__synapse_messaging_route*
		ptr_route
			= pMmanRoute->block_pointer
					(hnd_block);

	ptr_route->rt_mman_endpoint
		= pMmanRoute;
	ptr_route->rt_mman_message
		= pMmanMessage;

	ptr_route->rt_mblock
		= hnd_block;
	ptr_route->rt_handle
		= synapse_structure_double_linked_initialize
				(pMmanRoute);

	return
		ptr_route;
}

void
	__synapse_messaging_route_cleanup
		(__synapse_messaging_route* pRoute)
{
	synapse_structure_double_linked_node
		ptr_terminate
			= synapse_structure_double_linked_node_begin
					(pRoute->rt_handle);

	for ( ; ptr_terminate.opaque
		  ; ptr_terminate = synapse_structure_double_linked_node_next(ptr_terminate))
	{
		__synapse_messaging_route_endpoint*
			ptr_endpoint
				= *(__synapse_messaging_route_endpoint**)
						synapse_structure_double_linked_node_data
							(ptr_terminate);

		WaitForSingleObject
			(ptr_endpoint->rt_endpoint_thread, INFINITE);
		CloseHandle
			(ptr_endpoint->rt_endpoint_thread);
	}

	pRoute->rt_mman_message->deallocate_all
			(pRoute->rt_mman_message->hnd_mman);
	pRoute->rt_mman_endpoint->deallocate_all
			(pRoute->rt_mman_endpoint->hnd_mman);
}