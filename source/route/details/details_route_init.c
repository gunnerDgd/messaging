#include <messaging/route/details/route_init.h>

__synapse_messaging_route*
	__synapse_messaging_route_initialize
		(synapse_memory_manager* pMmanRoute)
{
	synapse_memory_block
		hnd_block
			= pMmanRoute->allocate
					(pMmanRoute->hnd_mman, NULL, sizeof(__synapse_messaging_route));

	__synapse_messaging_route*
		ptr_route
			= pMmanRoute->block_pointer
					(hnd_block);

	ptr_route->rt_mblock
		= hnd_block;
	ptr_route->rt_mman_route
		= pMmanRoute;

	ptr_route->rt_handle
		= synapse_structure_double_linked_initialize
				(pMmanRoute);
	ptr_route->rt_thread_lock
		= CreateMutex(NULL, TRUE, NULL);
	ptr_route->rt_thread_id
		= GetCurrentThreadId();

	return
		ptr_route;
}

void
	__synapse_messaging_route_cleanup
		(__synapse_messaging_route* pRoute)
{
	synapse_structure_double_linked_node
		ptr_terminate;

	if(GetCurrentThreadId()
			!= pRoute->rt_thread_id)
					return;

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

		if (GetCurrentThreadId()
					!= ptr_endpoint->rt_endpoint_thread_id)
		{
			WaitForSingleObject
				(ptr_endpoint->rt_endpoint_thread, INFINITE);
			CloseHandle
				(ptr_endpoint->rt_endpoint_thread);
		}
	}

	synapse_structure_double_linked_cleanup
		(pRoute->rt_handle);
	pRoute->rt_mman_route->deallocate
		(pRoute->rt_mman_route->hnd_mman, pRoute->rt_mblock);
}