#include <stdio.h>
#include <ctype.h>
int main() {
    char str[100];
    scanf("%s", str);
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = islower(str[i]) ? toupper(str[i]) : tolower(str[i]);
    }
    printf("%s\n", str);
    return 0;
}
