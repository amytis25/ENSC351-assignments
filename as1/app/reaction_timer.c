#include <stdio.h>
#include <stdlib.h>  // exit, EXIT_FAILURE, EXIT_SUCCESS
#include <stdbool.h>
#include "led.h"
#include <time.h>

int main(){

    /*1. Print a “get ready” message, and do the following four (4) times to flash the BYAI’s LEDs:
        a) Turn on the green LED for 250ms, then turn off.
        b) Turn on the red LED for 250ms, then turn off.*/
    fprintf(stdout, "Get Ready!\n");
    for (int i = 0; i < 4; i++){
        GreenLed_flash(0, 250000000, 1); // Flash green LED every 0.25 seconds
        RedLed_flash(0, 250000000, 1);   // Flash red LED every 0.25 seconds
    }
    
}
