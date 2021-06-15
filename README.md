# Arduino Gmod Interface
 Garry's Mod module that allows the game to communicate with Arduino microcontrollers, and vice versa using [SerialPort.](https://github.com/manashmandal/SerialPort) This only contains the API for interfacing between the game and Arduino along with a few Arduino and Lua samples. This module does nothing on it's own.

# Installing
 1. Download the latest ArduinoGmod binary module from [here.](https://github.com/LambdaGaming/ArduinoGmodInterface/releases) Make sure you download the 32-bit version unless you're running the x86-64 branch.
 2. Move the downloaded binary module to `steamapps/common/garrysmod/garrysmod/lua/bin`. You may have to create the bin folder yourself.
 3. Enjoy! If you need help getting started read the comments above each function in [this file](https://github.com/LambdaGaming/ArduinoGmodInterface/blob/main/ArduinoGmod/main.cpp) and take a look at the [examples.](https://github.com/LambdaGaming/ArduinoGmodInterface/tree/main/ArduinoTestCodes)

# Contrubiting/Compiling
- If you want to contribute, please read the [contributing guidelines](https://lambdagaming.github.io/contributing.html) before making a pull request.
- The project files for VS2019 and required Garry's Mod module headers are included. To get it to compile you shouldn't have to do anything but change your include paths.

# FAQs
## Does this work on servers?
 Yes, you can rename the first part of the binary module from gmcl to gmsv and place it in the `lua/bin` folder of the server. Everything *should* work the same as the client version.

## Is support for Linux/Mac planned?
 Not currently.

## Does this work on beta branches of the game?
 It works on the x86-64 branch in both 32-bit and 64-bit mode. Other branches haven't been tested but should work without issue.

## Will this work with my Arduino?
 It works with the Uno. Other types of boards haven't been tested, but most if not all should work as long as they have the ability to communicate through a serial port. The only board incompatibilities you should encounter while using this module should be from the code you write.
