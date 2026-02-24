AddCSLuaFile()

DEFINE_BASECLASS( "base_wire_entity" )
ENT.PrintName = "Arduino Microcontroller"

if SERVER then
	function ENT:Initialize()
		self:SetMoveType( MOVETYPE_VPHYSICS )
		self:SetSolid( SOLID_VPHYSICS )
		self:PhysicsInit( SOLID_VPHYSICS )
		self:SetUseType( SIMPLE_USE )

		self.Inputs = Wire_CreateInputs( self, { "Enabled", "Data Input 1", "Data Input 2 [STRING]" } )
		self.Outputs = Wire_CreateOutputs( self, { "Data Output" } )
	end

	function ENT:Setup( enabled, port, model, numfix, inputdelay, outputdelay )
		self.Instance = arduino.Begin( port )
		if !self.Instance:IsConnected() then
			MsgC( Color( 255, 0, 0 ), "[Arduino] ERROR: Failed to initialize connection!" )
			self:EmitSound( "buttons/button10.wav" )
			self:Remove()
			return
		end
		self.Enabled = tobool( enabled )
		self.Port = port
		self.NumFix = tobool( numfix )
		self.Instance:SetInputDelay( inputdelay )
		self.Instance:SetOutputDelay( outputdelay )
		self.InputDelay = inputdelay
		self.OutputDelay = outputdelay
		self:UpdateOverlay()
		self:ProcessOutput()
	end

	function ENT:UpdateOverlay()
		local enabled = self.Enabled and "Enabled" or "Disabled"
		self:SetOverlayText( "Status: "..enabled.."\nSerial Port: "..self.Port.."\nInput Delay: "..self.InputDelay.."\nOutput Delay: "..self.OutputDelay )
	end
	
	function ENT:TriggerInput( iname, value )
		if iname == "Enabled" then
			self.Enabled = tobool( value )
			self:UpdateOverlay()
		else
			if self.Enabled then
				local success = self.Instance:WriteString( tostring( value ) )
				if !success then
					MsgC( Color( 255, 0, 0 ), "[Arduino] ERROR: Failed to write string. Device not found.\n" )
				end
			end
		end
	end

	function ENT:ProcessOutput()
		timer.Create( "ArduinoTimer"..self:EntIndex(), 0.01, 0, function()
			if self.Enabled then
				local str = self.Instance:ReadString()
				if self.NumFix then str = tonumber( str ) end --Optional number conversion since the module only supports strings
				Wire_TriggerOutput( self, "Data Output", tonumber( str ) )
			end
		end )
	end

	function ENT:OnRemove()
		timer.Remove( "ArduinoTimer"..self:EntIndex() )
		self.Instance:Close()
	end
end

duplicator.RegisterEntityClass( "gmod_wire_arduino", WireLib.MakeWireEnt, "Data", "StartEnabled", "Port", "model", "NumFix", "InputDelay", "OutputDelay" )
