#ifndef LED_H
#define LED_H
#include <stdio.h> // fopen, fprintf, fclose, perror
#include <stdlib.h>  // exit, EXIT_FAILURE, EXIT_SUCCESS
#include <stdbool.h>
#include <time.h>


#define GREEN_LED_TRIGGER_FILE "/sys/class/leds/ACT/trigger"
#define GREEN_LED_BRIGHTNESS_FILE "/sys/class/leds/ACT/brightness"
#define RED_LED_TRIGGER_FILE "/sys/class/leds/FPGA_RED/trigger"
#define RED_LED_BRIGHTNESS_FILE "/sys/class/leds/FPGA_RED/brightness"

static bool writeToFile(const char* filename, const char* value);

bool GreenLed_turnOn();
bool GreenLed_turnOff();

bool RedLed_turnOn();
bool RedLed_turnOff();

bool GreenLed_flash(long long delayInMs, int numRepeat);
bool RedLed_flash(long long delayInMs, int numRepeat);

void RedLed_cleanup();
void GreenLed_cleanup();



#endif