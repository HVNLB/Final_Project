#include <stdio.h>
int main() {
    int count[11] = {0}, num;
    while (1) {
        scanf("%d", &num);
        if (num == -1) break;
        if (num >= 1 && num <= 10) count[num]++;
    }
    for (int i = 1; i <= 10; i++) {
        if (count[i] > 0) printf("%d occurs %d times\n", i, count[i]);
    }
    return 0;
}
