WireToolSetup.setCategory( "Chips, Gates", "Advanced" )
WireToolSetup.open( "arduino", "Arduino", "gmod_wire_arduino", nil, "Arduino" )

if CLIENT then
	language.Add( "tool.wire_arduino.name", "Arduino Microcontroller" )
	language.Add( "tool.wire_arduino.desc", "Transmits to and receives data from a real Arduino." )
	language.Add( "tool.wire_arduino.0", "Left Click: Spawn Arduino." )
	WireToolSetup.setToolMenuIcon( "icon16/wrench.png" )
end

WireToolSetup.SetupMax( 5 )

if SERVER then
	function TOOL:GetConVars()
		return self:GetClientNumber( "StartEnabled" ), self:GetClientInfo( "Port" ), self:GetClientInfo( "model" ), self:GetClientNumber( "NumFix" ), self:GetClientNumber( "InputDelay" ), self:GetClientNumber( "OutputDelay" )
	end

	function TOOL:LeftClick_PostMake( ent, ply, trace )
		if ent == true then return true end
		if ent == nil or ent == false or !IsValid( ent ) then return false end

		ent:GetPhysicsObject():EnableMotion( false )
		undo.Create( self.WireClass )
		undo.AddEntity( ent )
		undo.SetPlayer( ply )
		undo.Finish()
		ply:AddCleanup( self.WireClass, ent )
		return true
	end
end

function TOOL:SetPos( ent, trace )
	ent:SetPos( trace.HitPos )
end

TOOL.ClientConVar = {
	StartEnabled = 1,
	Port = "COM3",
	model = "models/bull/gates/microcontroller2.mdl",
	NumFix = 0,
	InputDelay = 0,
	OutputDelay = 0
}

function TOOL.BuildCPanel( panel )
	WireToolHelpers.MakePresetControl( panel, "wire_arduino" )
	panel:CheckBox( "Start Enabled", "wire_arduino_StartEnabled" )
	panel:CheckBox( "Convert Inputs To Numbers", "wire_arduino_NumFix" )
	panel:TextEntry( "Serial Port Name", "wire_arduino_Port" )
	panel:NumSlider( "Input Delay", "wire_arduino_InputDelay", 0, 600 )
	panel:NumSlider( "Output Delay", "wire_arduino_OutputDelay", 0, 600 )
	WireDermaExts.ModelSelect( panel, "wire_arduino_model", list.Get( "Wire_gate_Models" ), 2 )
end
