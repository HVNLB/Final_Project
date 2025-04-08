#include <stdio.h>

// Defining possible door states
typedef enum {
    CLOSED,
    OPENING,
    OPEN,
    CLOSING
} DoorStatus;

//Defining button commands from user 
typedef enum {
    PRESS_OPEN,
    PRESS_CLOSE,
    DOOR_IS_OPEN,
    DOOR_IS_CLOSED,
    NO_INPUT
} DoorAction;

// Converting enums to text to display to the user
const char* getDoorStatusName(DoorStatus status) {
    switch (status) {
        case CLOSED: return "CLOSED";
        case OPENING: return "OPENING";
        case OPEN: return "OPEN";
        case CLOSING: return "CLOSING";
        default: return "UNKNOWN";
    }
}

// Converting action enums to text to display to the user
const char* getDoorActionName(DoorAction action) {
    switch (action) {
        case PRESS_OPEN: return "PRESS_OPEN";
        case PRESS_CLOSE: return "PRESS_CLOSE";
        case DOOR_IS_OPEN: return "DOOR_IS_OPEN";
        case DOOR_IS_CLOSED: return "DOOR_IS_CLOSED";
        case NO_INPUT: return "NO_INPUT";
        default: return "UNKNOWN_ACTION";
    }
}

// Function that calculates the doors next move
DoorStatus updateDoorStatus(DoorStatus currentStatus, DoorAction action) {
    switch (currentStatus) {
        case CLOSED:
            if (action == PRESS_OPEN) {
                return OPENING;
            }
            break;

        case OPENING:
            if (action == DOOR_IS_OPEN) {
                return OPEN;
            }
            break;

        case OPEN:
            if (action == PRESS_CLOSE) {
                return CLOSING;
            }
            break;

        case CLOSING:
            if (action == DOOR_IS_CLOSED) {
                return CLOSED;
            } else if (action == PRESS_OPEN) {
                // Giving the user the chance to interrupt and reopen the door
                return OPENING;
            }
            break;
    }

    // If nothing happens, the door state will not change
    return currentStatus;
}

int main() {
    // Setting the door to closed status by default
      DoorStatus currentStatus = CLOSED;

    // Simulating a sequence of actions to check the code
    DoorAction actions[] = {
        PRESS_OPEN,
        DOOR_IS_OPEN,
        PRESS_CLOSE,
        DOOR_IS_CLOSED,
        PRESS_OPEN,
        DOOR_IS_OPEN,
        PRESS_CLOSE,
        NO_INPUT,
        DOOR_IS_CLOSED
    };

    // counting the ammount of actions
    int actionCount = sizeof(actions) / sizeof(DoorAction);

   
    // Go through each action and update the door status
    for (int i = 0; i < actionCount; i++) {
        DoorAction action = actions[i];
        DoorStatus nextStatus = updateDoorStatus(currentStatus, action);

        // Print what's happening
        printf("Action: %-15s | Status: %-10s → %-10s\n",
               getDoorActionName(action),
               getDoorStatusName(currentStatus),
               getDoorStatusName(nextStatus));

        // Move to next status
        currentStatus = nextStatus;
    }

    return 0;
}

