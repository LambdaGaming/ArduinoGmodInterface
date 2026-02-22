local function ArduinoGmod_Init()
	if pcall( require, "arduinogmod" ) then
		MsgC( Color( 0, 255, 255 ), "\nArduino for Wiremod successfully loaded.\n" )
	end
end
hook.Add( "InitPostEntity", "ArduinoGmodInit", ArduinoGmod_Init )
