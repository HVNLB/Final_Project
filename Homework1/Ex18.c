#include <stdio.h>
#include <string.h>
int main() {
    char binary[33];
    int decimal = 0;
    scanf("%s", binary);
    for (int i = 0; i < strlen(binary); i++) {
        decimal = decimal * 2 + (binary[i] - '0');
    }
    printf("%d\n", decimal);
    return 0;
}

