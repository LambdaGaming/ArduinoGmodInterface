--Required to initialize the module. Using pcall here since it's an easy way of knowing whether or not the module successfully loaded.
local function ArduinoGmod_Init()
	if pcall( require, "arduinogmod" ) then
		MsgC( Color( 0, 255, 255 ), "\nArduinoGmod module successfully loaded.\n" )
	end
end
hook.Add( "InitPostEntity", "ArduinoGmodInit", ArduinoGmod_Init )

--[[
	Arduino test:
	Simple function that reads and prints out the output of the specified Arduino.
]]
function Arduino_Test( port )
	local e = arduino.Begin( port )
	local str = arduino.ReadString( e )
	print( str )
	arduino.Close( e )
end

--[[
	DarkRP lockdown test:
	Used alongside ButtonInput.ino to detect when the button is pressed.
	Once pressed, the player will call a lockdown in the game (assuming they're mayor)
	Also demonstrates that you can use loops to constantly read outputs without
	initializing a new connection with every loop and causing insane lag/crashes.
]]
function Arduino_Lockdown( port )
	local e = arduino.Begin( port )
	timer.Create( "ArduinoLockdown", 0.1, 0, function()
		local str = arduino.ReadString( e )
		if isstring( str ) and string.find( str, "1" ) then
			LocalPlayer():ConCommand( "say /lockdown" )
			timer.Remove( "ArduinoLockdown" )
			arduino.Close( e )
		end
	end )
end
