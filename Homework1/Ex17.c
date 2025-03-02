#include <stdio.h>
void print_binary(int num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}
int main() {
    int num;
    scanf("%d", &num);
    if (num >= 0) print_binary(num);
    else print_binary((~(-num) + 1) & 255);
    return 0;
}
