#include <stdio.h>
int main() {
    int arr[10], N, found = 0;
    for (int i = 0; i < 10; i++) scanf("%d", &arr[i]);
    scanf("%d", &N);
    for (int i = 0; i < 10; i++) {
        if (arr[i] == N && !found) {
            found = 1;
            continue;
        }
        printf("%d ", arr[i]);
    }
    if (!found) printf("Number not found");
    printf("\n");
    return 0;
}
