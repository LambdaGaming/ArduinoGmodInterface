--Safely initialize the module
local function ArduinoGmod_Init()
	if !util.IsBinaryModuleInstalled( "arduinogmod" ) then
		MsgC( Color( 255, 0, 0 ), "\nERROR: ArduinoGmod module not found.\n" )
		return
	end
	require( "arduinogmod" )
	MsgC( Color( 0, 255, 255 ), "\nArduinoGmod module successfully loaded.\n" )
end
hook.Add( "InitPostEntity", "ArduinoGmodInit", ArduinoGmod_Init )
