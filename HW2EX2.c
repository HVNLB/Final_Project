#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_COLUMNS 100

void search_csv(const char *filename, int column, const char *search_value) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    
    char line[MAX_LINE_LENGTH];
    char *headers[MAX_COLUMNS];
    char *fields[MAX_COLUMNS];
    
    // Read the first line (column headers)
    if (fgets(line, MAX_LINE_LENGTH, file)) {
        int col_count = 0;
        char *token = strtok(line, ",\n");
        while (token && col_count < MAX_COLUMNS) {
            headers[col_count++] = strdup(token);
            token = strtok(NULL, ",\n");
        }
        
        printf("Searching in column: %s\n", headers[column]);
        
        // Read and process each line of the CSV file
        while (fgets(line, MAX_LINE_LENGTH, file)) {
            int field_count = 0;
            token = strtok(line, ",\n");
            
            while (token && field_count < MAX_COLUMNS) {
                fields[field_count++] = strdup(token);
                token = strtok(NULL, ",\n");
            }
            
            // Check if the specified column contains the search value
            if (column < field_count && strcmp(fields[column], search_value) == 0) {
                // Print the entire row
                for (int i = 0; i < field_count; i++) {
                    printf("%s%s", fields[i], (i < field_count - 1) ? ", " : "\n");
                }
            }
            
            // Free allocated memory for fields
            for (int i = 0; i < field_count; i++) {
                free(fields[i]);
            }
        }
        
        // Free allocated memory for headers
        for (int i = 0; i < col_count; i++) {
            free(headers[i]);
        }
    }
    
    fclose(file);
}

int main() {
    char filename[256];
    int column;
    char search_value[256];
    
    // Prompt the user for input
    printf("Enter the CSV filename: ");
    scanf("%255s", filename);
    printf("Enter column number (starting from 0): ");
    scanf("%d", &column);
    printf("Enter search value: ");
    scanf("%255s", search_value);
    
    // Perform search
    search_csv(filename, column, search_value);
    
    return 0;
}

