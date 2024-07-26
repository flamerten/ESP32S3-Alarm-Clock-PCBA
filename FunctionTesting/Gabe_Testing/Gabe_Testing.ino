/**
 * Arduino Code for testing the ESP32S3 PCB for Gabriel
 * 
 * The pupose of this code is to enable Gabriel to test functions related to the casing of the board,
 * Specifically
 * - Whether the buzzer tones can be heard with the case
 * - Whether the digits of the 7 segment are displayed.
 * 
 * The OLED, IMU and the PCF display are not initialised as they are not crictical for the board
 * casing.
 * 
 *  ----------------------------------------USAGE ----------------------------------------
 * Left push button to turn on the buzzer music
 * Right push button to cycle the digit brightness
 * 
 */

// Defines ----------------------------------------
#define DEBOUNCE_TIME_MS 100

// Numbers stolen from some website, not sure who

#define BUZZER_CHANNEL     0
#define BUZZER_FREQ        2000             // Frequency
#define BUZZER_RES         8                // Resolution


// Arduino Libraries ----------------------------------------
#include "pitches.h"                                // For the buzzer
#include <Adafruit_NeoPixel.h>                      // For the 7 Segment Display

// Local Libraries ----------------------------------------
#include "PCB_Pin_Definitions.h"                    // Inlcudes Defines for the PCB                     

// Structs ----------------------------------------

// Pushbutton struct to detect presses
typedef struct Pushbutton_Config{
  uint8_t        gpio_number;
  unsigned long  time_low;   
}Pushbutton_Config;


// Function Prototypes ----------------------------------------

void init_gpios();
bool button_pressed(Pushbutton_Config *pb_config);

// Objects ---------------------------------

Pushbutton_Config PB_Left;
Pushbutton_Config PB_Right;

uint8_t Clock_Led_Brightness = 20;
Adafruit_NeoPixel Clock_Leds(PCB_NEOPIXEL_COUNT, PCB_NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

const uint32_t COLOUR_GREEN = Clock_Leds.Color(0,100,0);
const uint32_t COLOUR_RED   = Clock_Leds.Color(100,0,0);
const uint32_t COLOUR_BLUE  = Clock_Leds.Color(0,0,100);
const uint32_t COLOUR_WHITE = Clock_Leds.Color(100,100,100);

const note_t HappyBirthday_Notes[25] = {NOTE_G, NOTE_G, NOTE_A, NOTE_G, NOTE_C, NOTE_B,
                                        NOTE_G, NOTE_G, NOTE_A, NOTE_G, NOTE_D, NOTE_C,
                                        NOTE_G, NOTE_G, NOTE_G, NOTE_E, NOTE_C, NOTE_B,
                                        NOTE_A, NOTE_F, NOTE_F, NOTE_E, NOTE_C, NOTE_D, NOTE_C};

const int HappyBirthday_Octaves[25] = {3, 3, 3, 3, 4, 3, 3, 3, 3, 3,
                                       4, 4, 3, 3, 4, 4, 4, 3, 3, 4,
                                       4, 4, 4, 4, 4};

const int HappyBirthday_NoteTime[25] = {200,  200, 500, 500, 500, 1000, 200, 200, 500, 500, 500, 
                                1000, 200, 200, 500, 500, 500, 500, 750, 200, 200, 500,
                                500,  500, 1000};

bool tune_playing = true;
uint8_t tune_index = 0;

void setup() {
  Serial.begin(115200); delay(100);
  Serial.println("Hello World");

  init_gpios();

  Clock_Leds.begin();
  Clock_Leds.clear();
  Clock_Leds.setBrightness(Clock_Led_Brightness);   // 1- 255, 0 is the max brightness

  // Set digits to indiv colours. WHITE - BLUE - WHITE(Seperator) - GREEN - RED

  for(int i = 0; i < 7; i++){
    Clock_Leds.setPixelColor(i,COLOUR_RED);
  }

  for(int i = 7; i < 14; i++){
    Clock_Leds.setPixelColor(i,COLOUR_GREEN);
  } 

  Clock_Leds.setPixelColor(14,COLOUR_WHITE);

  for(int i = 15; i < 22; i++){
    Clock_Leds.setPixelColor(i,COLOUR_BLUE);
  } 

  for(int i = 22; i < PCB_NEOPIXEL_COUNT; i++){
    Clock_Leds.setPixelColor(i,COLOUR_WHITE);
  }

  Clock_Leds.show();

}

void loop() {
  if(button_pressed(&PB_Left)){
    Serial.println("LEFT PB");
    Clock_Led_Brightness += 5;          //20, 25 ... 250, 255, (cycle) 5, 10 ...
    Clock_Leds.setBrightness(Clock_Led_Brightness);
    Clock_Leds.show();
    digitalWrite(PCB_LED0,HIGH);
  }
  else{
    digitalWrite(PCB_LED0,LOW);
  }

  if(button_pressed(&PB_Right)){ //button pressed
    play_happy_birthday(tune_index);
    tune_index = (tune_index + 1) % 25; //Range of tune_index should be between 0 - 24;
    digitalWrite(PCB_LED1,HIGH);
  }
  else{
    digitalWrite(PCB_LED1,LOW);
  }

}

//For initialising the LED GPIOs, Buzzer GPIO, PB GPIOs and the 3V7 regulator
void init_gpios()
{
  //LEDs
  pinMode(PCB_LED0, OUTPUT);
  pinMode(PCB_LED1, OUTPUT);

  digitalWrite(PCB_LED0,LOW);
  digitalWrite(PCB_LED1,LOW);

  //Push Buttons
  pinMode(PCB_PB_LEFT, INPUT_PULLUP);
  PB_Left.gpio_number = PCB_PB_LEFT;
  PB_Left.time_low = 0;

  pinMode(PCB_PB_RIGHT, INPUT_PULLUP);
  PB_Right.gpio_number = PCB_PB_RIGHT;
  PB_Right.time_low = 0;

  //Turn on 3V7 Reg
  pinMode(PCB_BUCK_CTRL, OUTPUT);
  digitalWrite(PCB_BUCK_CTRL,HIGH);

  //Buzzer
  //pinMode(PCB_BUZZER_PIN, OUTPUT);
  //analogWrite(PCB_BUZZER_PIN,0);     //Turn off buzzer
  
  
}

//For checking if a pushbutton was pressed with a debounce time of 100ms
bool button_pressed(Pushbutton_Config *pb_config)
{
  uint8_t gpio_num = pb_config->gpio_number;
  unsigned long last_time_low = pb_config->time_low;
  unsigned long time_now = millis();

  if(time_now - last_time_low < DEBOUNCE_TIME_MS){
    return false;
  }

  if(digitalRead(gpio_num) == LOW){
    pb_config->time_low = time_now;
    return true;
  }

  return false;

}

void play_happy_birthday(uint32_t index)
{
  note_t note = HappyBirthday_Notes[index];
  int note_duration = HappyBirthday_NoteTime[index];
  int octave = HappyBirthday_Octaves[index];
  
  int pauseBetweenNotes = note_duration * 1.0; // To customize the delay between tunes;
  
  ledcAttachChannel(PCB_BUZZER_PIN, BUZZER_FREQ, BUZZER_RES, BUZZER_CHANNEL);
  ledcWriteNote(PCB_BUZZER_PIN,note,octave);
  delay(pauseBetweenNotes);
  ledcDetach(PCB_BUZZER_PIN); //For pauses between notes, prob not the most efficient way...
  delay(note_duration*0.25);

  char mybuffer[100];
  snprintf(mybuffer, sizeof(mybuffer),"%i, Note: %i, Duration: %i",index, note, note_duration);
  Serial.println(mybuffer);
}
