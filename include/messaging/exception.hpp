#pragma once
#include <type_traits>

namespace synapse::messaging::exception {
	struct invalid_endpoint_name {};
	struct endpoint_not_found    {};

	struct invalid_message_handle {};
}