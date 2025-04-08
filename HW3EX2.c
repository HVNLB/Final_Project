#include <stdio.h>

// Defining the different states the vending machine can be in
typedef enum {
    WAITING,
    TAKING_COINS,
    GIVING_PRODUCT
} MachineState;

// Defining the different actions a user or machine can take
typedef enum {
    INSERT_COIN,
    CHOOSE_PRODUCT,
    PRODUCT_GIVEN,
    DO_NOTHING
} UserAction;

// Converting states to strings to print
const char* getStateName(MachineState state) {
    switch (state) {
        case WAITING: return "WAITING";
        case TAKING_COINS: return "TAKING_COINS";
        case GIVING_PRODUCT: return "GIVING_PRODUCT";
        default: return "UNKNOWN_STATE";
    }
}

// Converting actions to string for printing
const char* getActionName(UserAction action) {
    switch (action) {
        case INSERT_COIN: return "INSERT_COIN";
        case CHOOSE_PRODUCT: return "CHOOSE_PRODUCT";
        case PRODUCT_GIVEN: return "PRODUCT_GIVEN";
        case DO_NOTHING: return "DO_NOTHING";
        default: return "UNKNOWN_ACTION";
    }
}

// Setting product price
#define PRODUCT_COST 5

// Function to update machine state based on action and balance
MachineState updateMachineState(MachineState currentState, UserAction action, int* coins) {
    switch (currentState) {
        case WAITING:
            if (action == INSERT_COIN) {
                *coins += 1;
                return TAKING_COINS;
            }
            break;

        case TAKING_COINS:
            if (action == INSERT_COIN) {
                *coins += 1;
            } else if (action == CHOOSE_PRODUCT) {
                if (*coins >= PRODUCT_COST) {
                    *coins -= PRODUCT_COST;
                    return GIVING_PRODUCT;
                } else {
                    printf(" Balance too low You need %d more.\n", PRODUCT_COST - *coins);
                }
            }
            break;

        case GIVING_PRODUCT:
            if (action == PRODUCT_GIVEN) {
                return WAITING;
            }
            break;
    }

    // If nothing changes, the state stays the same
    return currentState;
}

int main() {
    // Start in the WAITING state
    MachineState currentState = WAITING;

    // keeping track of users balance
    int coinCount = 0;

    // A list of actions to simulate and check the code
    UserAction actions[] = {
        INSERT_COIN,
        INSERT_COIN,
        CHOOSE_PRODUCT,   // Not enough coins
        INSERT_COIN,
        INSERT_COIN,
        CHOOSE_PRODUCT,   // Now it's enough
        PRODUCT_GIVEN,
        INSERT_COIN,
        INSERT_COIN,
        INSERT_COIN,
        INSERT_COIN,
        INSERT_COIN,
        CHOOSE_PRODUCT,
        PRODUCT_GIVEN
    };

    // Counting the ammount of actions
    int totalActions = sizeof(actions) / sizeof(UserAction);

    // Going through each action one by one
    for (int i = 0; i < totalActions; i++) {
        UserAction currentAction = actions[i];
        MachineState nextState = updateMachineState(currentState, currentAction, &coinCount);

        // Showing what happened
        printf("Action: %-18s | State: %-15s → %-15s | Coins: %d\n",
               getActionName(currentAction),
               getStateName(currentState),
               getStateName(nextState),
               coinCount);

        // Moving to the next state
        currentState = nextState;
    }


    return 0;
}

