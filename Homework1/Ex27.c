#include <stdio.h>
#include <string.h>
#include <stdbool.h>
void sort(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (str[j] > str[j + 1]) {
                char temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }
}
int main() {
    char str1[100], str2[100];
    scanf("%s %s", str1, str2);
    if (strlen(str1) != strlen(str2)) {
        printf("No\n");
        return 0;
    }
    sort(str1);
    sort(str2);
    printf(strcmp(str1, str2) == 0 ? "Yes\n" : "No\n");
    return 0;
}
