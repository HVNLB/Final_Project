#include <stdio.h> // needed for printf
#include <stdlib.h> // needed for EXIT_FAILURE/SUCCESS

#define FILENAME "HW2EX1.c"  // so that the program reads itself

int main() { 
    FILE *file = fopen(FILENAME, "r"); // opens file in read mode 
    if (!file) { 
        perror("Error opening file");
        return EXIT_FAILURE; // checks if file exists, if not returns error
    }

    int ch, row = 1, col = 0;
    printf("Locations of '{' and '}':\n");
    printf("--------------------------------\n");

    while ((ch = fgetc(file)) != EOF) {
        col++;
        if (ch == '\n') {
            row++;
            col = 0;   
   	} // if /n is found we go to the next line and set col to 0
	else if (ch == '{' || ch == '}') {
            printf("%c found at row %d, column %d\n", ch, row, col);
        }// printing position of { or } 
    }// reding file character by character, incrementing columns

    fclose(file);
    return EXIT_SUCCESS; // closing file, returning succes 
}
