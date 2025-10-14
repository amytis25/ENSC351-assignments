#include <stdio.h>
#include <stdlib.h>  // exit, EXIT_FAILURE, EXIT_SUCCESS
#include <stdbool.h>
#include "hal/led.h"
#include "hal/timing.h"
#include "hal/SPI.h"
#include <time.h>

void startup() {  
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
}
void promptUser(int direction) {
    if (direction == 0) {
        printf("Move the joystick UP!\n");
        GreenLed_turnOn();
    } else {
        printf("Move the joystick DOWN!\n");
        RedLed_turnOn();
    }
}
long long getReactionTime(int direction){
    joystick_values jv;
    long long reaction_time_ms;
    long long startTime = getTimeInMs();
    // wait for user to move joystick or timeout after 5 seconds
    while(getTimeInMs() - startTime < 5000){ // 5 seconds to respond
        
        jv = Read_ADC_Values();
        if (jv.x > 50 || jv.x < -50) {
            printf("You moved the joystick on the x-axis!\n");
            return 5000;
            break;
        }
        else if (direction == 0 && jv.y > 50) { // Moved up when prompted up
            reaction_time_ms = getTimeInMs() - startTime;
            printf("You moved the joystick UP! Reaction time: %lld ms\n", reaction_time_ms);
            GreenLed_flash(200, 5); // flash the green LED on and off five times in one second
            return reaction_time_ms;
            break;
        } 
        else if (direction == 1 && jv.y < -50) { // Moved down when prompted down 
            reaction_time_ms = getTimeInMs() - startTime;
            printf("You moved the joystick DOWN! Reaction time: %lld ms\n", reaction_time_ms);
            GreenLed_flash(200, 5); // flash the green LED on and off five times in one second
            return reaction_time_ms;
            break;
        } else if (direction == 0 && jv.y < -50){ // Moved down when prompted up
            printf("Wrong direction! You moved the joystick DOWN when prompted UP.\n");
            return 5000;
            break;
        } else if (direction == 1 && jv.y > 50){ // Moved up when prompted down
            printf("Wrong direction! You moved the joystick UP when prompted DOWN.\n");
            return 5000;
            break;

        }
    }
    printf("Timeout! You did not move the joystick in time.\n");
    return 5000; // Return a high value indicating timeout

} 
long long game (long long highestRecord){
    joystick_values jv;
    long long reaction_time_ms;
    int wait_min_ms = 500;
    int wait_max_ms = 3000;
    
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
    reaction_time_ms = getReactionTime(randomDir);

    // check if reaction time is a new record
    if (reaction_time_ms < highestRecord) {
                highestRecord = reaction_time_ms;
                printf("New record! Fastest reaction time: %lld ms\n", highestRecord);
            }
    // cleanup 
    if (randomDir == 0) { 
            GreenLed_turnOff(); 

        } else if (randomDir == 1) {
            RedLed_turnOff();
        }
        return highestRecord;
}

int main(){
    long long HighestRecord = 5000;
    char status = 'p';

    while (status == 'p') {
        HighestRecord = game(HighestRecord);
        printf("Press ENTER to play again or CTRL-C to exit.\n");
        status = getchar();
    }

    return 0;
    
    

}
