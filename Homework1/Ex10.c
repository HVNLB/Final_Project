#include <stdio.h>
int main() {
    int N, M;
    char ch;
    scanf("%d %d %c", &N, &M, &ch);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%c", ch);
        }
        printf("\n");
    }
    return 0;
}
