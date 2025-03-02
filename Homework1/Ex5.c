#include <stdio.h>
int main() {
    int N, reversed = 0;
    scanf("%d", &N);
    while (N > 0) {
        reversed = reversed * 10 + N % 10;
        N /= 10;
    }
    printf("%d\n", reversed);
    return 0;
}

