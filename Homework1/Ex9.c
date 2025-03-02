#include <stdio.h>
int main() {
    int N;
    scanf("%d", &N);
    printf((N > 0 && (N & (N - 1)) == 0) ? "Power of 2\n" : "Not Power of 2\n");
    return 0;
}
