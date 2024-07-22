/*
 * Script for testing various functionalities of the PCB
 */

#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <RTClib.h>
#include <Adafruit_LSM6DSOX.h> 
#include "pitches.h"

#define BUZZER 7
#define NEOPIXEL_CTRL 17
#define PB1 18
#define PB2 8
#define PCB_I2C_SDA 38
#define PCB_I2C_SCL 39
#define IMU_INT1 40
#define IMU_INT2 41
#define RTC_INT  2
#define SWREG_CTRL 9
#define BUZZER_PIN 7
#define BUZZER_CHANNEL 0

#define LED_COUNT 30

Adafruit_LSM6DSOX imu;
RTC_PCF8523 rtc;
Adafruit_NeoPixel strip(LED_COUNT, NEOPIXEL_CTRL, NEO_GRB + NEO_KHZ800);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

//Function Def
void test_i2c_devices();
void test_neopixel();
void test_oled();
void imu_test_print();
void beep( int note, int duree );
void HappyBirthday();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);

  Serial.println("Hello PCB");
  delay(1000);

  //LEDs
  Serial.println("LED Test");
  pinMode(15,OUTPUT);
  pinMode(16,OUTPUT);
  
  digitalWrite(15,HIGH);
  digitalWrite(16,HIGH);

  Wire.begin(PCB_I2C_SDA,PCB_I2C_SCL);
  delay(1000);

  i2c_addr_scan();

  test_i2c_devices();

  //3V7 powers OLED and pixels
  pinMode(SWREG_CTRL,OUTPUT);
  digitalWrite(SWREG_CTRL,HIGH);
  
  Serial.println("Try with 3V7 on");
  i2c_addr_scan();
  test_oled();

  strip.begin();
  strip.clear();
  strip.setBrightness(20);
}

void loop() {
  imu_test_print();
  HappyBirthday();
  test_neopixel();

}

void test_neopixel()
{
  Serial.println("Start test");

  for(int i=0; i<LED_COUNT; i++) {

    strip.setPixelColor(i, strip.Color(0, 150, 0));
    strip.show();
    delay(500);
  }

  for(int i=0; i<LED_COUNT; i++) {

    strip.setPixelColor(i, strip.Color(150, 0, 0));
    strip.show();
    delay(500);
  }

  for(int i=0; i<LED_COUNT; i++) {

    strip.setPixelColor(i, strip.Color(0, 0, 150));
    strip.show();
    delay(500);
  }  

  Serial.println("Neopixel test done");
}

void test_i2c_devices()
{ 
  Serial.println("I2C Device Test");
  
  if(!imu.begin_I2C()){
    Serial.println("Unable to find LSM6DSOX");
  }
  else{
    Serial.println("IMU Found");
  }

  if(!rtc.begin()){
    Serial.println("Unable to find PCF8523");
  }
  else{
    Serial.println("RTC Found");
  }
  
  Serial.println("I2C testing done");
  
}

void test_oled()
{ 
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  delay(100);
  Serial.println("OLED display test");
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  } 
  else{
    Serial.println("OLED OK");
  }

  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();

  display.fillRect(0,0,display.width(),display.height(),SSD1306_WHITE);
  display.display();
}


void i2c_addr_scan()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 
  delay(5000);           // wait 5 seconds for next scan
}

void imu_test_print()
{
  // put your main code here, to run repeatedly:
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  imu.getEvent(&accel, &gyro, &temp);  

    /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("\t\tAccel X: ");
  Serial.print(accel.acceleration.x);
  Serial.print(" \tY: ");
  Serial.print(accel.acceleration.y);
  Serial.print(" \tZ: ");
  Serial.print(accel.acceleration.z);
  Serial.println(" m/s^2 ");

  /* Display the results (rotation is measured in rad/s) */
  Serial.print("\t\tGyro X: ");
  Serial.print(gyro.gyro.x);
  Serial.print(" \tY: ");
  Serial.print(gyro.gyro.y);
  Serial.print(" \tZ: ");
  Serial.print(gyro.gyro.z);
  Serial.println(" radians/s ");
  Serial.println();  
}

void beep( int note, int noteDuration ) {
  int pauseBetweenNotes = noteDuration * 1.30;
  tone(BUZZER,note,noteDuration);
  delay(pauseBetweenNotes);     
  noTone(BUZZER);
  delay(noteDuration*0.25);
}

void HappyBirthday() {
  Serial.println("Starting Buzzer Test: Happy Birthday");
  
  beep(NOTE_G3, 200);
  beep(NOTE_G3, 200);
  beep(NOTE_A3, 500);
  beep(NOTE_G3, 500);
  beep(NOTE_C4, 500);
  beep(NOTE_B3, 1000);
  beep(NOTE_G3, 200);
  beep(NOTE_G3, 200);
  beep(NOTE_A3, 500);
  beep(NOTE_G3, 500);
  beep(NOTE_D4, 500);
  beep(NOTE_C4, 1000);
  beep(NOTE_G3, 200);
  beep(NOTE_G3, 200);
  beep(NOTE_G4, 500);
  beep(NOTE_E4, 500);
  beep(NOTE_C4, 500);
  beep(NOTE_B3, 500);
  beep(NOTE_A3, 750);
  beep(NOTE_F4, 200);
  beep(NOTE_F4, 200);
  beep(NOTE_E4, 500);
  beep(NOTE_C4, 500);
  beep(NOTE_D4, 500);
  beep(NOTE_C4, 1000); 
}
