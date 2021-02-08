#define GMMODULE
#define DATA_LENGTH 255

#include "SerialPort.hpp"
#include "Interface.h"
#include <string>

using namespace GarrysMod::Lua;
using namespace std;

SerialPort *arduino;

/*
	Arduino_WriteString( String port, String str )
	Arguments:
		port - Name of the port, usually something like COM3. If the COM port is larger than 9 then you will need to format it like this: \\\\.\\COM10
		str - String to be sent to the Arduino
	Returns:
		Bool success - Whether or not the string was send successfully
	Example: Arduino_WriteString( "COM3", "Hello, World!" )
*/
LUA_FUNCTION( Arduino_WriteString )
{
	LUA->CheckType( 1, Type::String );
	LUA->CheckType( 2, Type::String );
	const char* port = LUA->GetString( 1 );
	const char* str = LUA->GetString( 2 );
	arduino = new SerialPort( port );
	if ( arduino->isConnected() )
	{
		bool haswritten = arduino->writeSerialPort( str, DATA_LENGTH );
		arduino->~SerialPort();
		if ( haswritten )
		{
			LUA->PushBool( true );
			return 1;
		}
	}
	arduino->~SerialPort();
	LUA->PushBool( false );
	return 1;
}

/*
	Arduino_ReadString( String port )
	Arguments:
		port - Name of the port, usually something like COM3. If the COM port is larger than 9 then you will need to format it like this: \\\\.\\COM10
	Returns:
		String str - String containing the read data, or an empty string if the read failed
	Example: Arduino_ReadString( "COM3" )
*/
LUA_FUNCTION( Arduino_ReadString )
{
	LUA->CheckType( 1, Type::String );
	const char* port = LUA->GetString( 1 );
	arduino = new SerialPort( port );
	char received[DATA_LENGTH];
	if ( arduino->isConnected() )
	{
		int hasread = arduino->readSerialPort( received, DATA_LENGTH );
		arduino->~SerialPort();
		if ( hasread )
		{
			LUA->PushString( received );
			return 1;
		}
	}
	arduino->~SerialPort();
	LUA->PushString( "" ); // Push empty string if read fails
	return 1;
}

GMOD_MODULE_OPEN()
{
	LUA->PushSpecial( SPECIAL_GLOB );
		LUA->PushCFunction( Arduino_WriteString );
		LUA->SetField( -2, "Arduino_WriteString" );
		LUA->PushCFunction( Arduino_ReadString );
		LUA->SetField( -2, "Arduino_ReadString" );
	LUA->Pop();
	return 0;
}

GMOD_MODULE_CLOSE()
{
	return 0;
}
