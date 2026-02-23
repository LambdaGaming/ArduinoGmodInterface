--Reads and prints out the output of the specified Arduino.
function Arduino_Test( port )
	local ino = arduino.Begin( port )
	local str = ino:ReadString()
	print( str )
	ino:Close()
end

--[[
	DarkRP lockdown test:
	Used alongside ButtonInput.ino to detect when the button is pressed.
	Once pressed, the player will call a lockdown in the game (assuming they're mayor)
	Also demonstrates that you can use loops to constantly read outputs without
	initializing a new connection with every loop and causing insane lag/crashes.
]]
function Arduino_Lockdown( port )
	local ino = arduino.Begin( port )
	timer.Create( "ArduinoLockdown", 0.1, 0, function()
		local str = ino:ReadString()
		if isstring( str ) and string.find( str, "1" ) then
			LocalPlayer():ConCommand( "say /lockdown" )
			timer.Remove( "ArduinoLockdown" )
			ino:Close()
		end
	end )
end
