#include "SerialPort.hpp"
#include <iostream>

#define DATA_LENGTH 255

const char *portname = "COM01";
const char *sendstring = "Hello World\n";
SerialPort *arduino;

int main( void )
{
	arduino = new SerialPort( portname );
	if ( arduino->isConnected() )
	{
		bool haswritten = arduino->writeSerialPort( sendstring, DATA_LENGTH );
		if ( haswritten )
		{
			std::cout << "Success" << std::endl;
		}
		else
		{
			std::cerr << "Data was not written" << std::endl;
		}
	}
}
