#include <messaging/messaging_endpoint.hpp>

synapse::messaging::endpoint::endpoint
	(__create_new pFlag, name_type pName)
		: __M_ep_handle
				(synapse_create_messaging_endpoint
					(pName.c_str())),
		  __M_ep_flag
				(__create_new::__flag)
{
	if(!synapse_messaging_opaque_handle_reference
			(__M_ep_handle))
				throw exception::invalid_endpoint_name {};
}

synapse::messaging::endpoint::endpoint
	(__retrieve_from pFlag, name_type pName)
		: __M_ep_handle
				(synapse_retrieve_messaging_endpoint
						(pName.c_str())),
		  __M_ep_flag
				(__retrieve_from::__flag)
{
	if(!synapse_messaging_opaque_handle_reference
			(__M_ep_handle))
				throw exception::endpoint_not_found {};
}

synapse::messaging::endpoint::~endpoint()
{
	if(__M_ep_flag == __create_new::__flag)
		synapse_delete_messaging_endpoint
			(__M_ep_handle);
}