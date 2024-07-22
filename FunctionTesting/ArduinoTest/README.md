# ArduinoTest

Used to test various functionalities of the PCB. 

## To Be Done
- Buzzer

## Arduino IDE Upload
[Source: USB and CDC Flashing](https://docs.espressif.com/projects/arduino-esp32/en/latest/tutorials/cdc_dfu_flash.html)

USB CDC is used to upload and view debugging messages
1. To enter into the download mode, you need to press and hold BOOT button and press and release the RESET button. You should see a new USB device with the name ESP32S3 Dev Kit listed in available ports. Select the device.
2. Configuration
- USB CDC On Boot -> Enabled
- Upload Mode -> UART0 / Hardware CDC
- USB Mode -> Hardware CDC & JTAG

Full configuration from "Tools" is here
![](./Config.png)
