#include "printer.h"

int send_all(SOCKET& s, const void* buffer, size_t len, int flags);

ThermalPOS::printer::printer(configuration printer_config) : printer_configuration(printer_config)
{
	if (printer_configuration.connection_type == ThermalPOS::printer_type::Internet)
	{
		WSADATA wsa;
		struct sockaddr_in server;

		//Initializing WS2
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
			Errors::last_error = Errors::error_types::winsock_initialization_failed;

		//Creating Socket
		if ((network_connector = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
			Errors::last_error = Errors::error_types::sockfd_creation_failed;
		//Translating ip to network bytes
		if (inet_pton(AF_INET, printer_configuration.sockfd.c_str(), &server.sin_addr.s_addr) == 0)
			Errors::last_error = Errors::error_types::sockfd_connection_invalid_address;
		//Inserting socket target data inside sockaddr struct
		server.sin_family = AF_INET;
		server.sin_port = htons(printer_configuration.complemention);
		//Connection to target
		if (connect(network_connector, reinterpret_cast<const sockaddr*>(&server), sizeof(server)) == SOCKET_ERROR)
		{
			Errors::last_error = Errors::error_types::sockfd_connection_failed;
		}
	}
}

ThermalPOS::printer::~printer()
{
	if (printer_configuration.connection_type == ThermalPOS::printer_type::Internet)
	{
		WSACleanup();
	}
}

int ThermalPOS::printer::raw(std::string& message)
{
	int r = send_all(network_connector, message.c_str(), strlen(message.c_str()), 0);
	if (r != 0)
	{
		Errors::last_error = Errors::error_types::send_failed;
	}
	return r;
}
int ThermalPOS::printer::raw(const char* message)
{
	int r = send_all(network_connector, message, strlen(message), 0);
	if (r != 0)
	{
		Errors::last_error = Errors::error_types::send_failed;
	}
	return r;
}

int send_all(SOCKET& s, const void* buffer, size_t len, int flags)
{
	const char* data = static_cast<const char*>(buffer);
	while (len > 0)
	{
		int bytes_sent = send(s, data, len, flags);
		if (bytes_sent < 1) return 1;
		data += bytes_sent;
		len -= bytes_sent;
	}
	return 0;
}
