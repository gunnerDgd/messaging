#pragma once
#include <messaging/messaging_endpoint.hpp>

namespace synapse::messaging {
	
	struct message_format_type {};
	class  message
	{
		message(synapse_messaging_message);
	public:
		using operation_code_type
					= std::uint16_t;
		using native_handle_type
					= synapse_messaging_message;

		using raw_type
					= void*;
		using size_type
					= std::size_t;
	public:
		message () = delete;
		~message();
		
		raw_type			raw_field     ();
		size_type			entire_size   ();
		operation_code_type operation_code();

	public:
		static message
				receive_from
					(endpoint&);
		template <typename AnyMessage>
		static std::enable_if_t
					<std::is_base_of_v
						<message_format_type,
							std::remove_all_extents_t<AnyMessage>>>
				send_to
					(endpoint& pEndpoint, operation_code_type pOpCode, AnyMessage& pMessage)
		{
			synapse_send_message
				(pEndpoint.__M_ep_handle,
					pOpCode, pMessage.raw_field(), pMessage.entire_size());
		}

	private:
		native_handle_type
			__M_message_handle;
	};
}