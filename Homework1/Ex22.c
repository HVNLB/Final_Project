#include <stdio.h>
int main() {
    int N, sorted = 1, order = 0;
    scanf("%d", &N);
    int arr[N];
    for (int i = 0; i < N; i++) scanf("%d", &arr[i]);
    for (int i = 1; i < N; i++) {
        if (arr[i] < arr[i - 1]) order = -1;
        else if (arr[i] > arr[i - 1] && order == -1) sorted = 0;
    }
    printf(sorted ? "Yes\n" : "No\n");
    return 0;
}
