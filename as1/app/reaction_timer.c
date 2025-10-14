#include <stdio.h>
#include <stdlib.h>  // exit, EXIT_FAILURE, EXIT_SUCCESS
#include <stdbool.h>
#include "hal/led.h"
#include "hal/timing.h"
#include "hal/SPI.h"
#include <time.h>

typedef struct reaction_returns
{
    long long reaction_time_ms;
    bool status;
} reaction_returns;

void startup() {  
    /*1. Print a “get ready” message, and do the following four (4) times to flash the BYAI’s LEDs:
    a) Turn on the green LED for 250ms, then turn off.
    b) Turn on the red LED for 250ms, then turn off.*/
    printf("When the LEDs light up, press the joystick in that direction! (green -> up, red -> down)\n");
    printf("(Press left or right to exit)\n");
    printf("Get Ready...\n");
    for (int i = 0; i < 4; i++){
        GreenLed_flash(250, 1); // Flash green LED for 250ms, 1 time
        sleepForMs(250);    // Wait for 250ms
        RedLed_flash(250, 1);   // Flash red LED for 250ms, 1 time
        sleepForMs(250);    // Wait for 250ms
    }
}
void promptUser(int direction) {
    if (direction == 0) {
        printf("Press UP now!\n");
        GreenLed_turnOn();
    } else {
        printf("Press DOWN now!\n");
        RedLed_turnOn();
    }
}
reaction_returns getReactionTime(int direction){
    joystick_values jv;
    long long reaction_time_ms;
    long long startTime = getTimeInMs();
    reaction_returns result = {5000, true};
    // wait for user to move joystick or timeout after 5 seconds
    while(getTimeInMs() - startTime < 5000){ // 5 seconds to respond
        
        jv = Read_ADC_Values();
        if (jv.x > 50 || jv.x < -50) {
            printf("User selected to quit.\n");
            result.reaction_time_ms = 5000;
            result.status = false;
            return result;
        }
        else if ((direction == 0 && jv.y > 50)||(direction == 1 && jv.y < -50)) { // correct direction
            reaction_time_ms = getTimeInMs() - startTime;
            printf("Correct!\n");
            GreenLed_flash(200, 5); // flash the green LED on and off five times in one second
            result.reaction_time_ms = reaction_time_ms;
            result.status = true;
            return result;
            break;
        } 
        else if ((direction == 0 && jv.y < -50)||(direction == 1 && jv.y > 50) ){ // wrong direction
            printf("Incorrect direction!.\n");
            result.reaction_time_ms = 5000;
            result.status = true;
            return result;
            break;
        } 
    }
    printf("No input within 5 seconds; quitting!\n");
    result.reaction_time_ms = 5000;
    result.status = false;
    return result;
}
reaction_returns game (long long highestRecord){
    joystick_values jv;
    long long reaction_time_ms;
    int wait_min_ms = 500;
    int wait_max_ms = 3000;
    reaction_returns result = {5000, true};
    reaction_returns highScore = {5000, true};
    
    /* seed RNG so rand() produces different sequences across runs */
    srand(getTimeInMs() % 1000); // seed with current time in ms mod 1000
    /* get a random wait time between 0.5s and 3s */
    int randomWait = wait_min_ms + (rand() % (wait_max_ms - wait_min_ms + 1));
    int randomDir = rand() % 2; // 0 for up and 1 for down

    printf("Random wait time: %d ms\n", randomWait);
  
    startup();

    // ensure joystick is centered before starting
    jv = Read_ADC_Values();
    if (jv.x > 5 && jv.y > 5 && jv.x < -5 && jv.y < -5) {
        printf("Please let go of joystick\n");
    } 

    // Wait for random time between 0.5s to 3s
    sleepForMs(randomWait); 
    
    // prompt user to move joystick
    promptUser(randomDir);

    // initialize game and get reaction time
    result = getReactionTime(randomDir);

    // check if reaction time is a new record
    if (result.reaction_time_ms < highestRecord) {
                highScore.reaction_time_ms = result.reaction_time_ms;
                printf("New record! Fastest reaction time: %lld ms\n", highestRecord);
            }
            else {
                printf("Your reaction time was %lld ms. Fastest reaction time remains: %lld ms\n", reaction_time_ms, highestRecord);
            }
    // update game status
    highScore.status = result.status;
    // cleanup 
    if (randomDir == 0) { 
            GreenLed_turnOff(); 

        } else if (randomDir == 1) {
            RedLed_turnOff();
        }
        return highScore;
}

int main(){
    long long HighestRecord = 5000;
    reaction_returns current = {5000, true};


    while (current.status == true) {
        current = game(HighestRecord);
    }

    return 0;
    
    

}
