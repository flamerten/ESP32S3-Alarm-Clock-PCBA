/**
 * @file PCB_Pin_Definitions.h
 * @author Samuel Yow
 * @brief 
 */

#define PCB_LED0            GPIO_NUM_15           // Active High LED
#define PCB_LED1            GPIO_NUM_16           // Active High LED
  
#define PCB_PB_RIGHT        GPIO_NUM_18           // Active Low PB, (Low when pressed). Note: Silkscreen on PCB is wrong
#define PCB_PB_LEFT         GPIO_NUM_8            // Active Low PB, (Low when pressed). Note: Silkscreen on PCB is wrong
  
#define PCB_BUCK_CTRL       GPIO_NUM_9            // Active High Switch to turn on buck converter (3V7)
  
#define PCB_BUZZER_PIN      GPIO_NUM_7            // Pin connected to MOSFET that controls power to buzzer      
 
#define PCB_NEOPIXEL_PIN    GPIO_NUM_17           // Pin connected to first NEOPIXEL LED
#define PCB_NEOPIXEL_COUNT  29                    // Number of NEOPIXELS, 7 + 7 + 1 + 7 + 7
 
#define PCB_I2C_SDA         GPIO_NUM_38           // Connected to IMU, RTC
#define PCB_I2C_SCL         GPIO_NUM_39           // Connected to IMU, RTC
#define PCB_I2C_PORT        I2C_NUM_0             // Connected to IMU, RTC 
 
#define PCB_LSM_INT1        GPIO_NUM_40           // LSM6DSOX INT1 pin, direct connection
#define PCB_LSM_INT2        GPIO_NUM_41           // LSM6DSOX INT2 pin, direct connection
 
#define PCB_PCF_INT1        GPIO_NUM_2            // PCF8523 INT1 pin, direct connection
 
#define PCB_BATT_ADC        GPIO_NUM_6            // Multiply ADC reading by 2 to get BATT Voltage. (BATT -  100K | 100k - GND)


