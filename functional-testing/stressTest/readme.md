# StressTest app for the Fortithing board

The goal of the project is to test during hours and days the board to validate the hardware.

## How it works
The board boot, hook on the local 2.4GHZ WPA/WPA2 Wifi and get it's IP from the DHCP server.
The board send to the server, via a GET request, the asked sensor values by the server. From the server's reply, the board keep the next sensor to send, shift the 4 RGB LED and pause for 1 second.

## Deploy it

### The board
Before flashing the board, 3 steps are needed:
 - Install the lib: FastLED, Adafruit LIS3DH, Adafruit BMP280 Library (and their dependencies)
 - Modify the 4 #define at the beginning of stressTestFortithing.ino file to setup your Wifi and server settings
 - Patch the Adafruit BMP280 lib to read correctly the BMP280 sensor:
Open this file https://github.com/adafruit/Adafruit_BMP280_Library/blob/master/Adafruit_BMP280.cpp
comment those 2 lines:               
 99:   if (read8(BMP280_REGISTER_CHIPID) != chipid)             
100:    return false;                

### The server
PHP need to be installed, create a folder "file" at the root of the server, copy file.php and do the corresponding setting asked for stressTestFortithing.ino.
Do not forget to set the folder writeable for the PHP code.
2 files are generated server side, in CSV format, with the content of the accelerometer and temperature sensors. So you can check the data in a worksheet by graph them and see if everything is accurate.

