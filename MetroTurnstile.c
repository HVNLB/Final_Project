#include <stdio.h>
#include <unistd.h>
#include <assert.h>

// Define the possible states of the turnstile
enum turnstile_state {
    LOCKED,     // Turnstile is locked, requires a coin to unlock
    UNLOCKED    // Turnstile is unlocked, allows a person to pass
};

// Array to store state names for easy display
const char* state_as_string[] = {"LOCKED", "UNLOCKED"};

/**
 * Handles turnstile state transitions based on user input.
 *
 * param state Pointer to the current state of the turnstile.
 * param event The event character ('c' for coin, 'p' for pass).
 */
void handle_turnstile_event(enum turnstile_state* state, char event) {
    switch (*state) {
        case LOCKED:  
            if (event == 'c') {  // If user inserts a coin ('c')
                printf("Coin inserted. Turnstile is now UNLOCKED.\n");
                *state = UNLOCKED; // Change state to UNLOCKED
            } else {  
                // If user tries to pass without inserting a coin
                printf("Turnstile is LOCKED. Insert a coin to pass.\n");
            }
            break;
        case UNLOCKED:  
            if (event == 'p') {  // If user passes through ('p')
                printf("Person passed. Turnstile is now LOCKED again.\n");
                *state = LOCKED; // Change state back to LOCKED
            } else {  
                // If a coin is inserted when already unlocked
                printf("Turnstile is already UNLOCKED. You can pass.\n");
            }
            break;
        default:
            printf("Invalid state.\n");
            break;
    }
}

/**
 * Main function to simulate a subway turnstile.
 * 
 * It continuously asks for user input to simulate inserting a coin or passing through.
 */
int main() {
    // Initialize the turnstile to the LOCKED state
    enum turnstile_state current_state = LOCKED; 
    char event; // Variable to store user input

    // Display initial instructions
    printf("Turnstile simulation started...\n");
    printf("Commands:\n - 'c' to insert a coin\n - 'p' to pass through\n - 'q' to quit\n");

    // Infinite loop to handle user input until they quit
    while (1) {
        // Display current state
        printf("Current State: %s\n", state_as_string[current_state]);
        printf("Enter event (c/p/q): ");
        
        // Read user input (using " %c" to skip any whitespace)
        scanf(" %c", &event);  

        // If user enters 'q', exit the loop
        if (event == 'q') {
            printf("Exiting simulation.\n");
            break;
        }

        // handle turnstile state changes
        handle_turnstile_event(&current_state, event);
        
        //  small delay for better readability
        sleep(1); 
    }

    return 0; // Exit successfully
}
