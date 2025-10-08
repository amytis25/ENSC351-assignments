#include <stdio.h> // fopen, fprintf, fclose, perror
#include <stdlib.h>  // exit, EXIT_FAILURE, EXIT_SUCCESS

#define GREEN_LED_TRIGGER_FILE "/sys/class/leds/ACT/trigger"

int main (){

    
    // 1) Open the trigger file for writing.
    //    WHY: sysfs exposes device controls as files; writing the trigger name selects behavior.
    FILE *pGreenLedTriggerFile = fopen(GREEN_LED_TRIGGER_FILE, "w");
    if (pGreenLedTriggerFile == NULL) {
        // If this fails, it’s usually a permissions issue (need sudo) or wrong path.
        perror("Error opening green LED trigger file");
        exit(EXIT_FAILURE);
    }

    // 2) Write the new trigger value (e.g., "none") to the file.
    //    WHY: This tells the kernel LED subsystem to switch the LED’s control source.
    //    - "none"  -> manual control via brightness
    //    - "heartbeat" -> kernel blinks to show liveness
    //    - "timer" -> enables delay_on/delay_off files for kernel-timed blinking
    int charsWritten = fprintf(pGreenLedTriggerFile, "none");
    if (charsWritten <= 0) {
        perror("Error writing trigger value to LED file");
        fclose(pGreenLedTriggerFile);  // try to close before exiting
        exit(EXIT_FAILURE);
    }

    // 3) Close the file to flush the write.
    //    WHY: sysfs applies changes on write/close; closing ensures the kernel sees your update.
    if (fclose(pGreenLedTriggerFile) != 0) {
        perror("Error closing green LED trigger file");
        exit(EXIT_FAILURE);
    }


    return EXIT_SUCCESS;

}
