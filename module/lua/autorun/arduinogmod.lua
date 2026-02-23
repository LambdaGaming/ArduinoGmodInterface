--Safely initialize the module
local version = "1.3"
hook.Add( "InitPostEntity", "ArduinoModuleInit", function()
	if !util.IsBinaryModuleInstalled( "arduino" ) then
		MsgC( Color( 255, 0, 0 ), "\nERROR: Arduino module not found.\n" )
		return
	end
	require( "arduino" )
	MsgC( Color( 0, 255, 255 ), "\nArduino module v"..version.." successfully loaded.\n" )
end )
