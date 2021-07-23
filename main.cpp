#include <iostream>
#include "printer.h"

int main()
{
	ThermalPOS::configuration printer_cfg = { "192.168.2.102", 9100, ThermalPOS::printer_type::Internet };
	std::cout << ThermalPOS::Errors::get_last_error() << std::endl;
	ThermalPOS::printer	printer(printer_cfg);
	std::cout << ThermalPOS::Errors::get_last_error() << std::endl;


	printer.raw("Hello People, \n I'm here");
	std::cout << ThermalPOS::Errors::get_last_error() << std::endl;

	printer.raw("And i like \n all of you");
	std::cout << ThermalPOS::Errors::get_last_error() << std::endl;

	std::cin.get();
}


