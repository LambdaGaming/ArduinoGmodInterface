# Arduino Gmod Interface
 Experimental Garry's Mod module that allows the game to communicate with Arduino microcontrollers, and vice versa using [SerialPort.](https://github.com/manashmandal/SerialPort) This repo contains the base addon (including the binary module), as well as a Wiremod tool.

# Installing the Base
 1. Download the latest binary module from [here.](https://github.com/LambdaGaming/ArduinoGmodInterface/releases) Make sure you download the 32-bit version unless you're running the x86-64 branch.
 2. Move the downloaded binary module to `steamapps/common/garrysmod/garrysmod/lua/bin`. You may have to create the bin folder as it doesn't exist by default.
 3. Enjoy! If you need help getting started read the comments above each function in [main.cpp](module/src/main.cpp) and take a look at the [examples.](examples)

# Using the Wiremod Tool
 Ensure you have the base addon and binary module downloaded, [Wiremod](https://steamcommunity.com/sharedfiles/filedetails/?id=160250458) downloaded, and an Arduino device plugged into your PC. The Arduino needs to be programmed to send or receive serial data.

 The Wiremod tool can be found in the "Chips, Gates" category. Once you have it selected, you can change various settings that include:
 - Whether or not it should be enabled on spawn. If disabled, the virtual Arduino will not be able to transmit or receive any data until turned on through a virtual input.
 - Whether or not the virtual Arduino should convert all strings sent by the physical Arduino to numbers. This is useful for communicating with Wiremod entities that only accept numbers for certain inputs.
 - The name of the serial port the physical Arduino is connected to. This is required to make the virtual Arduino function properly.
 - The model of the virtual Arduino. Model options are the same as the Wiremod CPU.

 Once you spawn it in, you can get to work connecting things as inputs, outputs, or both depending entirely on what you want to do, and then writing code for your physical Arduino to react to those inputs/outputs.

# FAQs
## Does this work on servers?
 Yes, you can rename the first part of the binary module from gmcl to gmsv and place it in the `garrysmod/lua/bin` folder of the server. Everything *should* work the same as the client version, just make sure the Arduino is plugged into the server.

## Does this work on beta branches of the game?
 It works on the x86-64 branch in both 32-bit and 64-bit mode. Other branches haven't been tested but should work without issue.

## Will this work with my Arduino?
 It works with the Uno. Other types of boards haven't been tested, but most if not all should work as long as they have the ability to communicate through a serial port.
