#include <stdio.h>

int main() {
    int a, b, digits = 1;
    scanf("%d %d", &a, &b);

    int temp = b;
    while (temp > 0) {
        digits *= 10;
        temp /= 10;
    }

    printf("%d\n", a * digits + b);
    return 0;
}

