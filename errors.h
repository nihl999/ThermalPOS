#pragma once


namespace ThermalPOS::Errors {
	enum error_types
	{
		no_error = 0,
		winsock_initialization_failed,
		sockfd_creation_failed,
		sockfd_connection_failed,
		sockfd_connection_invalid_address,
		send_failed
	};

	extern inline error_types last_error = no_error;

	inline error_types get_last_error()
	{
		return last_error;
	}

}


