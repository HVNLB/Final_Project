#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    srand(time(0));
    int target = rand() % 100 + 1, guess;
    do {
        scanf("%d", &guess);
        if (guess < target) printf("Too low\n");
        else if (guess > target) printf("Too high\n");
    } while (guess != target);
    printf("Correct!\n");
    return 0;
}
