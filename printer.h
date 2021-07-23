#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "errors.h"

namespace ThermalPOS {

	enum printer_type
	{
		Internet,
		Serial
	};

	struct configuration
	{
		std::string sockfd;
		int complemention;
		ThermalPOS::printer_type connection_type;
	};


	class printer
	{
		configuration printer_configuration;
		SOCKET network_connector;

	public:
		printer(configuration printer_config); // Printer constructor
		~printer();
		int raw(std::string& message);
		int raw(const char* message);
	};

}
