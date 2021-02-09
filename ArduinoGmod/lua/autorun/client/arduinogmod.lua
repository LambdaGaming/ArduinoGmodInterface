local function ArduinoGmod_Init()
	if pcall( require, "arduinogmod" ) then
		MsgC( Color( 0, 255, 255 ), "\nArduinoGmod module successfully loaded.\n" )
	end
end
hook.Add( "InitPostEntity", "ArduinoGmodInit", ArduinoGmod_Init )

function Arduino_Test( port )
	local e = arduino.Begin( port )
	local str = arduino.ReadString( e )
	print( str )
	arduino.Close( e )
end
