# CMakeList.txt for HAL (Hardware Abstraction Layer)
#   Build a library (`hal`) which exposes the LED control functionality
#   Use header as: #include "led.h"

# Find all source files in the src directory
include_directories(hal/include)
file(GLOB HAL_SOURCES "src/*.c")

# Create the HAL static library
add_library(hal STATIC ${HAL_SOURCES})

# Make the include directory available to users of this library
target_include_directories(hal PUBLIC include)

# Link required libraries for LED control and timing
target_link_libraries(hal PUBLIC rt)  # For nanosleep and real-time functions

# Set library properties
set_target_properties(hal PROPERTIES
    OUTPUT_NAME "hal_led"
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)