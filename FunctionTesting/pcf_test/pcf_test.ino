#include <Wire.h>
#include <RTClib.h>

#define PCB_I2C_SDA 38
#define PCB_I2C_SCL 39
#define RTC_INT  2

RTC_PCF8523 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


void setup() {
  Serial.begin(115200);
  while(!Serial);

  Serial.println("RTC Function Test");

  Wire.begin(PCB_I2C_SDA,PCB_I2C_SCL);
  if(!rtc.begin()){
    Serial.println("Couldnt find RTC");
    while(1);
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  rtc.start();
}

void loop () {
    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    Serial.println();
    
    delay(3000);
}
