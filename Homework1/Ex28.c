#include <stdio.h>
#include <string.h>
int main() {
    char str1[100], str2[100];
    scanf("%s %s", str1, str2);
    printf(strstr(str1, str2) ? "Yes\n" : "No\n");
    return 0;
}
