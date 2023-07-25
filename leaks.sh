#!/bin/bash

# Infinite loop to run the 'leaks' command continuously
while true; do
    leaks cub3D  # Replace <your_program_name> with the name of your program
    sleep 5      # Adjust the sleep time (in seconds) to control the interval between each 'leaks' command run
done
