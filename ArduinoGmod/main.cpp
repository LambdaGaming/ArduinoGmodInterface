#define GMMODULE
#define DATA_LENGTH 255

#include "SerialPort.hpp"
#include "Interface.h"

using namespace GarrysMod::Lua;

/*
	arduino.Begin( String port )
	Arguments:
		port - Name of the port, usually something like COM3. If the COM port is larger than 9 then you will need to format it like this: \\\\.\\COM10
	Returns:
		UserData arduino - Instance of the arduino serial connection
	Example: arduino.Begin( "COM3" )
*/
LUA_FUNCTION( Begin )
{
	LUA->CheckType( 1, Type::String );
	const char* port = LUA->GetString( 1 );
	SerialPort* arduino;
	arduino = new SerialPort( port );
	LUA->PushUserType( arduino, Type::UserData );
	return 1;
}

/*
	arduino.WriteString( UserData arduino, String str )
	Arguments:
		arduino - Instance of an arduino serial connection
		str - String to be sent to the Arduino
	Returns:
		Bool success - Whether or not the string was send successfully
	Example: arduino.WriteString( arduino, "Hello, World!" )
*/
LUA_FUNCTION( WriteString )
{
	LUA->CheckType( 1, Type::UserData );
	LUA->CheckType( 2, Type::String );
	SerialPort* arduino = LUA->GetUserType<SerialPort>( 1, Type::UserData );
	const char* str = LUA->GetString( 2 );
	if ( arduino->isConnected() )
	{
		bool haswritten = arduino->writeSerialPort( str, DATA_LENGTH );
		if ( haswritten )
		{
			LUA->PushBool( true );
			return 1;
		}
	}
	LUA->PushBool( false );
	return 1;
}

/*
	arduino.ReadString( UserData arduino )
	Arguments:
		arduino - Instance of an arduino serial connection
	Returns:
		String str - String containing the read data, or an empty string if the read failed
	Example: arduino.ReadString( arduino )
*/
LUA_FUNCTION( ReadString )
{
	LUA->CheckType( 1, Type::UserData );
	SerialPort* arduino = LUA->GetUserType<SerialPort>( 1, Type::UserData );
	char received[DATA_LENGTH];
	if ( arduino->isConnected() )
	{
		int hasread = arduino->readSerialPort( received, DATA_LENGTH );
		if ( hasread )
		{
			LUA->PushString( received );
			return 1;
		}
	}
	LUA->PushBool( false ); // Return false if read fails
	return 1;
}

LUA_FUNCTION( IsConnected )
{
	LUA->CheckType( 1, Type::UserData );
	SerialPort* arduino = LUA->GetUserType<SerialPort>( 1, Type::UserData );
	if ( arduino->isConnected() )
	{
		LUA->PushBool( true );
		return 1;
	}
	LUA->PushBool( false );
	return 1;
}

/*
	arduino.Close( UserData arduino )
	Arguments:
		arduino - Instance of an arduino serial connection
	Returns: None
	Example: arduino.Close( arduino )
*/
LUA_FUNCTION( Close )
{
	LUA->CheckType( 1, Type::UserData );
	SerialPort* arduino = LUA->GetUserType<SerialPort>( 1, Type::UserData );
	if ( arduino->isConnected() )
	{
		arduino->~SerialPort();
	}
	return 0;
}

GMOD_MODULE_OPEN()
{
	LUA->PushSpecial( SPECIAL_GLOB );
		LUA->CreateTable();
			LUA->PushCFunction( Begin );
			LUA->SetField( -2, "Begin" );
			LUA->PushCFunction( WriteString );
			LUA->SetField( -2, "WriteString" );
			LUA->PushCFunction( ReadString );
			LUA->SetField( -2, "ReadString" );
			LUA->PushCFunction( IsConnected );
			LUA->SetField( -2, "IsConnected" );
			LUA->PushCFunction( Close );
			LUA->SetField( -2, "Close" );
		LUA->SetField( -2,  "arduino" );
	LUA->Pop();
	return 0;
}

GMOD_MODULE_CLOSE()
{
	return 0;
}
