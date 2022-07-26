# Arduino Gmod Interface
 (No longer in development.) Experimental Garry's Mod module that allows the game to communicate with Arduino microcontrollers, and vice versa using [SerialPort.](https://github.com/manashmandal/SerialPort) This only contains the API for interfacing between the game and Arduino along with a few Arduino and Lua samples. For a functional addon that uses this API, see [ArduinoWiremod.](https://github.com/LambdaGaming/ArduinoWiremod)

# Installing
 1. Download the latest ArduinoGmod binary module from [here.](https://github.com/LambdaGaming/ArduinoGmodInterface/releases) Make sure you download the 32-bit version unless you're running the x86-64 branch.
 2. Move the downloaded binary module to `steamapps/common/garrysmod/garrysmod/lua/bin`. You may have to create the bin folder as it doesn't exist by default.
 3. Enjoy! If you need help getting started read the comments above each function in [main.cpp](https://github.com/LambdaGaming/ArduinoGmodInterface/blob/main/ArduinoGmod/main.cpp) and take a look at the [examples.](https://github.com/LambdaGaming/ArduinoGmodInterface/tree/main/ArduinoTestCodes)

# Contrubiting/Compiling
- This project has been archived and is no longer accepting pull requests, but feel free to create your own fork.

# FAQs
## Does this work on servers?
 Yes, you can rename the first part of the binary module from gmcl to gmsv and place it in the `lua/bin` folder of the server. Everything *should* work the same as the client version, just make sure the Arduino is plugged into the device that is running the server.

## Does this work on beta branches of the game?
 It works on the x86-64 branch in both 32-bit and 64-bit mode. Other branches haven't been tested but should work without issue.

## Will this work with my Arduino?
 It works with the Uno. Other types of boards haven't been tested, but most if not all should work as long as they have the ability to communicate through a serial port.
