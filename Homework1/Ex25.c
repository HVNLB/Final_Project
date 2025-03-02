#include <stdio.h>
int main() {
    int N, K, M;
    scanf("%d %d %d", &N, &K, &M);
    int arr[N + 1];
    for (int i = 0; i < N; i++) scanf("%d", &arr[i]);
    for (int i = N; i > M; i--) arr[i] = arr[i - 1];
    arr[M] = K;
    for (int i = 0; i <= N; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
