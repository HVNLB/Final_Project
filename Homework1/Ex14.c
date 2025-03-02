#include <stdio.h>
int main() {
    int low = 1, high = 100, mid;
    char response;
    while (low <= high) {
        mid = (low + high) / 2;
        printf("Is it %d? (h/l/c): ", mid);
        scanf(" %c", &response);
        if (response == 'c') break;
        else if (response == 'h') high = mid - 1;
        else if (response == 'l') low = mid + 1;
    }
    printf("Guessed correctly!\n");
    return 0;
}

