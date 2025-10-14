#include <stdio.h>
#include <stdlib.h>  // exit, EXIT_FAILURE, EXIT_SUCCESS
#include <stdbool.h>
#include "hal/led.h"
#include "hal/timing.h"
#include "hal/SPI.h"
#include <time.h>

int main(){
    joystick_values jv;
    long long reaction_time_ms;
    int wait_min_ms = 500;
    int wait_max_ms = 3000;
    int recordedTime = 5000;
    int randomWait = wait_min_ms + (rand() % (wait_max_ms - wait_min_ms + 1));
    
    printf("Random wait time: %d ms\n", randomWait);
    /*1. Print a “get ready” message, and do the following four (4) times to flash the BYAI’s LEDs:
        a) Turn on the green LED for 250ms, then turn off.
        b) Turn on the red LED for 250ms, then turn off.*/
    printf("Get Ready...\n");
    for (int i = 0; i < 4; i++){
        GreenLed_flash(250, 1); // Flash green LED for 250ms, 1 time
        sleepForMs(250);    // Wait for 250ms
        RedLed_flash(250, 1);   // Flash red LED for 250ms, 1 time
        sleepForMs(250);    // Wait for 250ms
    }

    jv = Read_ADC_Values();
    if (jv.x > 5 && jv.y > 5 && jv.x < -5 && jv.y < -5) {
        printf("Please let go of joystick\n");
    } 
    sleepForMs(randomWait); // Wait for random time between 0.5s to 3s
    int randomDir = rand() % 2; // 0 for up and 1 for down
    long long startTime = getTimeInMs();
    
    
    // prompt user to move joystick
    if (randomDir == 0) { // Move joystick up
            printf("move the joystick UP\n");
            GreenLed_turnOn(); 

        } else if (randomDir == 1) { // Move joystick down
            printf("move the joystick DOWN!\n");
            RedLed_turnOn(); 
        }
    // wait for user to move joystick or timeout after 5 seconds
    while(getTimeInMs() - startTime < 5000){ // 5 seconds to respond
        
        jv = Read_ADC_Values();
        if (jv.x > 50 || jv.x < -50) {
            printf("You moved the joystick on the x-axis!\n");
            break;
        }
        else if (randomDir == 0 && jv.y > 25) { // Moved up
            reaction_time_ms = getTimeInMs() - startTime;
            printf("You moved the joystick UP! Reaction time: %d ms\n", reaction_time_ms);
            GreenLed_flash(200, 5); // flash the green LED on and off five times in one second
            if (reaction_time_ms < recordedTime) {
                recordedTime = reaction_time_ms;
                printf("New record! Fastest reaction time: %d ms\n", recordedTime);
            }
            break;
        } 
        else if (randomDir == 1 && jv.y < -25) { // Moved down
            reaction_time_ms = getTimeInMs() - startTime;
            printf("You moved the joystick DOWN! Reaction time: %d ms\n", reaction_time_ms);
            GreenLed_flash(200, 5); // flash the green LED on and off five times in one second
            if (reaction_time_ms < recordedTime) {
                recordedTime = reaction_time_ms;
                printf("New record! Fastest reaction time: %d ms\n", recordedTime);
            }
            break;
        } else {
            printf("You moved the wrong way! \n");
            RedLed_flash(200, 5); // flash the red LED on and off five times in one second
        }
        break;
        
    }
    // turn leds off
    if (randomDir == 0) { 
            GreenLed_turnOff(); 

        } else if (randomDir == 1) {
            RedLed_turnOff();
        }
    printf("Timeout! You did not move the joystick in time.\n");

}
