#include <messaging/endpoint/details/endpoint_init.h>

__synapse_messaging_endpoint*
	__synapse_messaging_endpoint_initialize
		(synapse_memory_mman_traits* pMman)
{
	synapse_memory_mman_block
		hnd_block
			= pMman->allocate
				(pMman->hnd_mman, NULL, sizeof(__synapse_messaging_endpoint));

	__synapse_messaging_endpoint*
		ptr_endpoint
		= pMman->block_pointer
				(hnd_block);

	ptr_endpoint->ep_hnd_mblock
		= hnd_block;
	ptr_endpoint->ep_hnd_message_mman
		= pMman;
	ptr_endpoint->ep_hnd_message
		= synapse_structure_double_linked_initialize
				(pMman);

	ptr_endpoint->ep_hnd_notifier
		= CreateEvent
			(NULL, FALSE, FALSE, NULL);
	ptr_endpoint->ep_hnd_lock
		= CreateMutex
			(NULL, TRUE, NULL);

	return
		ptr_endpoint;
}

void
	__synapse_messaging_endpoint_cleanup
		(__synapse_messaging_endpoint* pEndpoint)
{
	CloseHandle
		(pEndpoint->ep_hnd_lock);
	CloseHandle
		(pEndpoint->ep_hnd_notifier);

	pEndpoint->ep_hnd_message_mman
		->deallocate_all
			(pEndpoint->ep_hnd_message_mman->hnd_mman);
}