# Build the reaction timer application, using the HAL

# Find all source files in current directory
file(GLOB APP_SOURCES "*.c")

# Create the reaction_timer executable
add_executable(reaction_timer ${APP_SOURCES})

# Link with the HAL library
target_link_libraries(reaction_timer PRIVATE hal)

# Link additional libraries needed for timing and math functions
target_link_libraries(reaction_timer PRIVATE rt m)

# Copy executable to final location for deployment
add_custom_command(TARGET reaction_timer POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:reaction_timer>"
     "~/ensc351/public/myApps/reaction_timer" 
  COMMENT "Copying ARM executable to public NFS directory")

# Also copy to project root for easy local testing
add_custom_command(TARGET reaction_timer POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:reaction_timer>"
     "${CMAKE_SOURCE_DIR}/reaction_timer" 
  COMMENT "Copying executable to project root for local testing")
