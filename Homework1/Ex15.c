#include <stdio.h>
int main() {
    int arr[10], min, max;
    for (int i = 0; i < 10; i++) scanf("%d", &arr[i]);
    min = max = arr[0];
    for (int i = 1; i < 10; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    printf("Min: %d\nMax: %d\n", min, max);
    return 0;
}

