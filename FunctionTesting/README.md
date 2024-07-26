# Function Testing
This folder serves as a repository of Arduino IDE `.ino` files that can be used to test various features on the custom PCB. The actual firmware of the board is being developed using ESP-IDF and is found at [ESP32S3-Alarm-Clock-FW](https://github.com/flamerten/ESP32S3-Alarm-Clock-FW). The most recently updated script is the [GabeTesting.ino](./Gabe_Testing/Gabe_Testing.ino) script which is used for testing interactions.

Arduino IDE Version: `1.18.19`

Libraries used
1. Adafruit Neopixel `1.12.2` 

# Usage

Install ESP32 boards following this tutorial [RandomNerdTutorials: Installing ESP32 Board in Arduino IDE](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)

- Board: `ESP32S3 Dev Module`
- USB Mode: `Hardware CDC and JTAG`
- USB CDC on Boot: `Enabled`   *this allows serial monitor output*
- Upload Mode: `"UART0 / Hardware CDC"`

Remember to select board before uploading.