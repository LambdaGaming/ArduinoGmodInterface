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

function Arduino_TimerTest( port )
	local e = arduino.Begin( port )
	timer.Create( "ArduinoTimer", 1, 3, function()
		local str = arduino.ReadString( e )
		print( str )
		if timer.RepsLeft( "ArduinoTimer" ) == 0 then
			arduino.Close( e )
		end
	end )
end

if DarkRP then
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
end
