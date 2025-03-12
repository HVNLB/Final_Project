#include <stdio.h>
#include <string.h>


void reverseString(char *str) {
    if (!str || *str == '\0') return;  // For null or empty strings
    
    char *left = str;
    char *right = str + strlen(str) - 1;
    
    while (left < right) {
        // Swapping characters
        char temp = *left;
        *left = *right;
        *right = temp;
        
        // Moving pointers
        left++;
        right--;
    }
}

int main() {
    char str[] = "Hello, World!";  // array of chars
    printf("Original: %s\n", str);
    
    reverseString(str);
    printf("Reversed: %s\n", str);
    
    return 0;
}

