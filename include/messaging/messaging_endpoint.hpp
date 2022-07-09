#pragma once
extern "C"
{
#include <messaging/messaging.h>
}

#include <string>
#include <messaging/exception.hpp>

namespace synapse::messaging {
	class endpoint
	{
		friend class message;
		struct __create_new    { static constexpr int __flag = 0; };
		struct __retrieve_from { static constexpr int __flag = 1; };
	public:
		using name_type
				= std::string;
		using native_handle_type
				= synapse_messaging_endpoint;

		static constexpr
			__create_new    create   {};
		static constexpr
			__retrieve_from retrieve {};

	public:
		template <typename InitType>
		endpoint (InitType&&, name_type) {}
		endpoint (__create_new	 , name_type);
		endpoint (__retrieve_from, name_type);

		~endpoint();

	private:
		synapse_messaging_endpoint
			__M_ep_handle;
		int
			__M_ep_flag;
	};
}