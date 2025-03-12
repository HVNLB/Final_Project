#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void compressString(char *str) {
    if (!str || *str == '\0') return; // For null or empty strings
    
    int length = strlen(str);
    int writeIndex = 0, readIndex = 0;
    
    while (readIndex < length) {
        char currentChar = str[readIndex];
        int count = 0;
        
        while (readIndex < length && str[readIndex] == currentChar) {
            count++;
            readIndex++;
        }// Reads characters and counts repetitions, writes the compressed version in place.The loop counts consecutive characters.
        
        str[writeIndex++] = currentChar;
        
        // Convert count to string and append it to str
        int numLen = snprintf(str + writeIndex, length - writeIndex + 1, "%d", count);
        writeIndex += numLen;
    }
    
    str[writeIndex] = '\0'; // Null-terminate the string
}

int main() {
    char str[100]; // Ensuring space for in-place modification
    
    printf("Enter a string: ");
    scanf("%99s", str); // Read user input safely
    
    printf("Original: %s\n", str);
    
    compressString(str);
    printf("Compressed: %s\n", str);
    
    return 0;
}
