#include <messaging/route/details/route_endpoint.h>

#include <messaging/endpoint/details/endpoint_init.h>
#include <messaging/message/details/message_init.h>

#include <memory/defines/alloc.h>
#include <memory/mman/standard_heap/stdheap.h>

#include <stdio.h>
#include <process.h>

__synapse_messaging_route_endpoint*
	__synapse_messaging_route_create_endpoint
		(__synapse_messaging_route * pRoute, const char* pEndpointName)
{
	synapse_memory_mman_block
		hnd_endpoint_route_mblock
			= pRoute->rt_mman_endpoint->allocate
					(pRoute->rt_mman_endpoint->hnd_mman, 
							NULL, sizeof(__synapse_messaging_route_endpoint));

	__synapse_messaging_route_endpoint*
		ptr_endpoint
			= pRoute->rt_mman_endpoint->block_pointer
					(hnd_endpoint_route_mblock);

	ptr_endpoint->rt_endpoint
		= __synapse_messaging_endpoint_initialize
				(synapse_memory_mman_stdheap_initialize_traits());
	ptr_endpoint->rt_endpoint_handle
		= synapse_structure_double_linked_insert_back
				(pRoute->rt_handle, &ptr_endpoint, sizeof(__synapse_messaging_route_endpoint*));

	ptr_endpoint->rt_endpoint_identifier
		= synapse_memory_default_alloc
				(NULL, strlen(pEndpointName) + 1);
	ptr_endpoint->rt_endpoint_identifier_length
		= strlen(pEndpointName);
	memset
		(ptr_endpoint->rt_endpoint_identifier,
			0x00, ptr_endpoint->rt_endpoint_identifier_length + 1);
	memcpy
		(ptr_endpoint->rt_endpoint_identifier,
				pEndpointName, 
					ptr_endpoint->rt_endpoint_identifier_length);

	ptr_endpoint->rt_endpoint_mblock
		= hnd_endpoint_route_mblock;
	DuplicateHandle
		(GetCurrentProcess(), GetCurrentThread (),
			GetCurrentProcess(), &ptr_endpoint->rt_endpoint_thread,
				0, TRUE, DUPLICATE_SAME_ACCESS);

	return
		ptr_endpoint;
}

void
	__synapse_messaging_route_delete_endpoint
		(__synapse_messaging_route* pRoute, __synapse_messaging_route_endpoint* pEndpoint)
{
	synapse_memory_mman_traits*
		ptr_mman_endpoint
			= pEndpoint->rt_endpoint->ep_hnd_message_mman;

	WaitForSingleObject
		(pEndpoint->rt_endpoint_thread, INFINITE);
	CloseHandle
		(pEndpoint->rt_endpoint_thread);

	synapse_memory_default_dealloc
		(pEndpoint->rt_endpoint_identifier, 
			pEndpoint->rt_endpoint_identifier_length);

	__synapse_messaging_endpoint_cleanup
		(pEndpoint->rt_endpoint);
	synapse_memory_mman_stdheap_cleanup_traits
		(ptr_mman_endpoint);

	synapse_structure_double_linked_erase_at
		(pRoute->rt_handle, pEndpoint->rt_endpoint_handle);
	pRoute->rt_mman_endpoint->deallocate
		(pRoute->rt_mman_endpoint->hnd_mman, pEndpoint->rt_endpoint_mblock);
}

__synapse_messaging_route_endpoint*
	__synapse_messging_route_retrieve_endpoint
		(__synapse_messaging_route* pRoute, const char* pName)
{
	synapse_structure_double_linked_node
		ptr_seek
			= synapse_structure_double_linked_node_begin
					(pRoute->rt_handle);

	for( ; ptr_seek.opaque
		 ; ptr_seek = synapse_structure_double_linked_node_next(ptr_seek))
	{
		__synapse_messaging_route_endpoint*
			ptr_endpoint
				= *(__synapse_messaging_route_endpoint**)
						synapse_structure_double_linked_node_data
							(ptr_seek);

		if (!ptr_endpoint->rt_endpoint_identifier)
			continue;
		if(strcmp
				(ptr_endpoint->rt_endpoint_identifier, pName) == 0)
			return
				ptr_endpoint;
	}

	return NULL;
}

void
	__synapse_messaging_route_send_to
		(__synapse_messaging_route			*pRoute, 
		 __synapse_messaging_route_endpoint *pEndpoint, 
		 uint16_t							 pMessageOpcode, 
		 void								*pMessageField, 
		 size_t								 pMessageFieldSize)
{
	__synapse_messaging_message*
		ptr_message
			= __synapse_messaging_message_initialize
					(pRoute->rt_mman_message, pMessageOpcode, pMessageField, pMessageFieldSize);

	WaitForSingleObject
		(pEndpoint->rt_endpoint->ep_hnd_lock, INFINITE);
	synapse_structure_double_linked_insert_back
		(pEndpoint->rt_endpoint->ep_hnd_message, &ptr_message, sizeof(__synapse_messaging_message));

	ReleaseMutex
		(pEndpoint->rt_endpoint->ep_hnd_lock);
	SetEvent
		(pEndpoint->rt_endpoint->ep_hnd_notifier);
}

__synapse_messaging_message*
	__synapse_messaging_route_receive_from
		(__synapse_messaging_route* pRoute, __synapse_messaging_route_endpoint* pEndpoint)
{
	__synapse_messaging_message*
		ptr_message;

	WaitForSingleObject
		(pEndpoint->rt_endpoint->ep_hnd_notifier, INFINITE);
	WaitForSingleObject
		(pEndpoint->rt_endpoint->ep_hnd_lock, INFINITE);

	ptr_message
		= *(__synapse_messaging_message**)
				synapse_structure_double_linked_node_data
					(synapse_structure_double_linked_node_begin
						(pEndpoint->rt_endpoint->ep_hnd_message));

	synapse_structure_double_linked_erase_front
		(pEndpoint->rt_endpoint->ep_hnd_message);

	ReleaseMutex(pEndpoint->rt_endpoint->ep_hnd_lock);

	return
		ptr_message;
}

void
	__synapse_messaging_route_expire
		(__synapse_messaging_route* pRoute, __synapse_messaging_message* pMessage)
{
	pRoute->rt_mman_message->deallocate
		(pRoute->rt_mman_message->hnd_mman,
			pMessage->msg_mman_block);
}