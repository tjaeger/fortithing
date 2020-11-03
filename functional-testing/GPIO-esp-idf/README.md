# GPIO tests with esp-idf SDK

The esp-idf SDK from Espressif allow you to go deeper with the ESP32. The code is low level and allow you to control everything in the chip. The drawback is it's slightly more complex than using the Arduino IDE.

## The environment
First, setup the SDK under your favourite OS: [Link to the Espressif web site](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html)
Tested successfully under Linux and Windows with the Fortithing. Even with VM in Virtualbox plus USB passthrough to flash the device.

## Your first own code
The idea is to start from the `hello_world` from [step 5](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html#step-5-start-a-project). 
Copy again the template and copy the GPIO.c + CMakeLists.txt files in the folder `main`.
To use the full flash, change the default size: run `idf.py menuconfig` go to `Serial flasher config` and set the `Flash size` to `4 MB`.
Compile and flash the board and that's it.

