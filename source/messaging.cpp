#include <messaging/messaging.hpp>

void synapse::messaging::initialize()
{
	synapse_messaging_initialize_system();
}
void synapse::messaging::cleanup()
{
	synapse_messaging_cleanup_system();
}

synapse::messaging::message::message
	(synapse_messaging_message pHandle)
		: __M_message_handle
				(pHandle)
{
	if(!synapse_messaging_opaque_handle_reference
			(__M_message_handle))
				throw exception::invalid_message_handle {};
}

synapse::messaging::message::~message()
{
	if(synapse_messaging_opaque_handle_reference
		(__M_message_handle))
			synapse_expire_message
				(__M_message_handle);
}
		
typename synapse::messaging::message::raw_type  
	synapse::messaging::message::raw_field()
{
	return
		synapse_message_data
			(__M_message_handle);
}

typename synapse::messaging::message::size_type 
	synapse::messaging::message::entire_size()
{
	return
		synapse_message_size
			(__M_message_handle);
}

synapse::messaging::message 
	synapse::messaging::message::receive_from(endpoint& pEndpoint)
{
	return
		message
			(synapse_receive_message
				(pEndpoint.__M_ep_handle));
}

typename synapse::messaging::message::operation_code_type
	synapse::messaging::message::operation_code()
{
	return
		synapse_message_opcode
			(__M_message_handle);
}