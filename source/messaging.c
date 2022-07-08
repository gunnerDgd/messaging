#include <messaging/messaging.h>

#include <memory/mman/mman_traits.h>
#include <memory/mman/standard_heap/stdheap.h>

#include <messaging/endpoint/endpoint_init.h>
#include <messaging/endpoint/endpoint_manip.h>

#include <messaging/route/details/route_init.h>

static synapse_memory_mman_traits
			*__synapse_messaging_mman_endpoint,
			*__synapse_messaging_mman_message ;

static synapse_messaging_route
			 __synapse_messaging_route_object;

synapse_messaging_dll
	void
		synapse_messaging_initialize_system
			()
{
	__synapse_messaging_mman_endpoint
		= synapse_memory_mman_stdheap_initialize_traits();
	__synapse_messaging_mman_message
		= synapse_memory_mman_stdheap_initialize_traits();

	__synapse_messaging_route_object.opaque
		= __synapse_messaging_route_initialize
			(__synapse_messaging_mman_endpoint, __synapse_messaging_mman_message);
}

synapse_messaging_dll
	void
		synapse_messaging_cleanup_system
			()
{
	__synapse_messaging_route_cleanup
			(__synapse_messaging_route_object.opaque);

	synapse_memory_mman_stdheap_cleanup_traits
		(__synapse_messaging_mman_endpoint);
	synapse_memory_mman_stdheap_cleanup_traits
		(__synapse_messaging_mman_message);
}

synapse_messaging_dll
	synapse_messaging_endpoint
		synapse_create_messaging_endpoint
			(const char* pName, void(*pRoutine)(void*), void* pRoutineParameter)
{
	return
		synapse_messaging_endpoint_initialize
			(__synapse_messaging_route_object, pName, pRoutine, pRoutineParameter);
}

synapse_messaging_dll
	void
		synapse_delete_messaging_endpoint
			(synapse_messaging_endpoint pEndpoint)
{
	synapse_messaging_endpoint_cleanup
		(__synapse_messaging_route_object, pEndpoint);
}

synapse_messaging_dll
	synapse_messaging_endpoint
		synapse_retrieve_messaging_endpoint
			(const char* pName)
{
	return
		synapse_messaging_endpoint_retrieve
			(__synapse_messaging_route_object, pName);
}

synapse_messaging_dll
	void
		synapse_send_message
			(synapse_messaging_endpoint pEndpoint, uint16_t pOpcode, void* pDataField, size_t pDataSize)
{
	synapse_messaging_endpoint_send_to
		(__synapse_messaging_route_object, pEndpoint, pOpcode, pDataField, pDataSize);
}

synapse_messaging_dll
	synapse_messaging_message
		synapse_receive_message
			(synapse_messaging_endpoint pEndpoint)
{
	return
		synapse_messaging_endpoint_receive_from
			(__synapse_messaging_route_object, pEndpoint);
}

synapse_messaging_dll
	void*
		synapse_message_data
			(synapse_messaging_message pMessage)
{
	return
		((__synapse_messaging_message*)pMessage.opaque)
			->msg_field_ptr;
}

synapse_messaging_dll
	size_t
		synapse_message_size
			(synapse_messaging_message pMessage)
{
	return
		((__synapse_messaging_message*)pMessage.opaque)
			->msg_field_size;
}