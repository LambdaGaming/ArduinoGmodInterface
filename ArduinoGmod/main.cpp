#define GMMODULE
#define DATA_LENGTH 255

#include "SerialPort.hpp"
#include "Interface.h"

using namespace GarrysMod::Lua;

int ArduinoTable;

/*
	arduino.Begin( String port )
	Description:
		Initializes a new connection to the specified serial port.
	Arguments:
		port - Name of the port, usually something like COM3. If the COM port is larger than 9 then you will need to format it like this: \\\\.\\COM10
	Returns:
		UserData arduino - Instance of the arduino serial connection
	Example: arduino.Begin( "COM3" )
*/
LUA_FUNCTION( Begin )
{
	LUA->CheckType( 1, Type::String );
	auto port = LUA->GetString( 1 );
	SerialPort* arduino;
	arduino = new SerialPort( port );
	LUA->PushUserType( arduino, ArduinoTable );
	return 1;
}

/*
	Arduino:SetInputDelay( Int delay )
	Description:
		Sets the number of seconds before the next input can be sent to the virtual arduino.
	Arguments:
		delay - Delay amount in seconds
	Returns:
		None
*/
LUA_FUNCTION( SetInputDelay )
{
	LUA->CheckType( 2, Type::Number );
	auto arduino = LUA->GetUserType<SerialPort>( 1, ArduinoTable );

	if ( arduino->isConnected() )
	{
		arduino->InputDelay = LUA->GetNumber( 2 );
	}
	return 1;
}

/*
	Arduino:SetOutputDelay( Int delay )
	Description:
		Sets the number of seconds before the next input can be sent to the physical arduino.
	Arguments:
		delay - Delay amount in seconds
	Returns:
		None
*/
LUA_FUNCTION( SetOutputDelay )
{
	LUA->CheckType( 2, Type::Number );
	auto arduino = LUA->GetUserType<SerialPort>( 1, ArduinoTable );

	if ( arduino->isConnected() )
	{
		arduino->OutputDelay = LUA->GetNumber( 2 );
	}
	return 1;
}

/*
	Arduino:WriteString( String str )
	Description:
		Sends a string to the Arduino.
	Arguments:
		str - String to be sent to the Arduino
	Returns:
		Bool success - Whether or not the string was send successfully
	Example: local ino = arduino.Begin( "COM4" ) ino:WriteString( "Hello, World!" )
*/
LUA_FUNCTION( WriteString )
{
	LUA->CheckType( 2, Type::String );
	auto arduino = LUA->GetUserType<SerialPort>( 1, ArduinoTable );
	auto str = LUA->GetString( 2 );

	LUA->PushSpecial( SPECIAL_GLOB );
		LUA->GetField( -1, "CurTime" );
		LUA->Call( 0, 1 );
		auto curtime = LUA->GetNumber( -1 );
	LUA->Pop( 3 );

	if ( arduino->isConnected() )
	{
		if ( arduino->OutputDelay && arduino->OutputCooldown >= curtime )
		{
			LUA->PushBool( true );
			return 1;
		}

		auto haswritten = arduino->writeSerialPort( str, DATA_LENGTH );

		if ( arduino->OutputDelay )
		{
			arduino->OutputCooldown = curtime + arduino->OutputDelay;
		}

		if ( haswritten )
		{
			LUA->PushBool( true );
			return 1;
		}
	}
	LUA->PushBool( false );
	return 1;
}

/*	Arduino:ReadString()
*	Description:
*		Receives a string from the Arduino if it is currently transmitting one.
	Arguments: None
	Returns:
		String str - String containing the read data, or an empty string if the read failed
*/
LUA_FUNCTION( ReadString )
{
	auto arduino = LUA->GetUserType<SerialPort>( 1, ArduinoTable );
	char received[DATA_LENGTH];

	LUA->PushSpecial( SPECIAL_GLOB );
		LUA->GetField( -1, "CurTime" );
		LUA->Call( 0, 1 );
		auto curtime = LUA->GetNumber( -1 );
	LUA->Pop( 3 );

	if ( arduino->isConnected() )
	{
		if ( arduino->InputDelay && arduino->InputCooldown >= curtime )
		{
			LUA->PushBool( true );
			return 1;
		}

		auto hasread = arduino->readSerialPort( received, DATA_LENGTH );

		if ( arduino->InputDelay )
		{
			arduino->InputCooldown = curtime + arduino->InputDelay;
		}

		if ( hasread )
		{
			LUA->PushString( received );
			return 1;
		}
	}
	LUA->PushString( "" ); // Return empty string if read fails
	return 1;
}

/*
	Arduino:IsConnected()
	Description:
		Checks whether or not the Arduino currently has a valid connection.
	Arguments: None
	Returns:
		Bool connected - Whether or not the specified connection is available
*/
LUA_FUNCTION( IsConnected )
{
	auto arduino = LUA->GetUserType<SerialPort>( 1, ArduinoTable );
	if ( arduino->isConnected() )
	{
		LUA->PushBool( true );
		return 1;
	}
	LUA->PushBool( false );
	return 1;
}

/*
	Arduino:Close()
	Description:
		Closes the connection. Do not try to start a new connection on the same port without calling this on the old connection first, or else things will break!
	Arguments: None
	Returns: None
*/
LUA_FUNCTION( Close )
{
	auto arduino = LUA->GetUserType<SerialPort>( 1, ArduinoTable );
	if ( arduino->isConnected() )
	{
		arduino->~SerialPort();
	}
	return 0;
}

GMOD_MODULE_OPEN()
{
	ArduinoTable = LUA->CreateMetaTable( "Arduino" );
	LUA->Push( -1 );
		LUA->SetField( -2, "__index" );
		LUA->PushCFunction( SetInputDelay );
		LUA->SetField( -2, "SetInputDelay" );
		LUA->PushCFunction( SetOutputDelay );
		LUA->SetField( -2, "SetOutputDelay" );
		LUA->PushCFunction( WriteString );
		LUA->SetField( -2, "WriteString" );
		LUA->PushCFunction( ReadString );
		LUA->SetField( -2, "ReadString" );
		LUA->PushCFunction( IsConnected );
		LUA->SetField( -2, "IsConnected" );
		LUA->PushCFunction( Close );
		LUA->SetField( -2, "Close" );
	LUA->Pop();

	LUA->PushSpecial( SPECIAL_GLOB );
		LUA->CreateTable();
			LUA->PushCFunction( Begin );
			LUA->SetField( -2, "Begin" );
		LUA->SetField( -2,  "arduino" );
	LUA->Pop();
	return 0;
}

GMOD_MODULE_CLOSE()
{
	return 0;
}
