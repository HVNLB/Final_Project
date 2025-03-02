#include <stdio.h>
int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int arr[N];
    for (int i = 0; i < N; i++) scanf("%d", &arr[i]);
    for (int i = 0; i < N; i++) {
        if (i != M - 1) printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
