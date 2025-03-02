#include <stdio.h>

void grades_to_letters() {
    int grade;
    
    while (1) {
        printf("Enter a grade or -1 to exit: ");
        scanf("%d", &grade);
        
        if (grade == -1) break;
        
        char letter;
        if (grade >= 90 && grade <= 100) letter = 'A';
        else if (grade >= 80) letter = 'B';
        else if (grade >= 70) letter = 'C';
        else if (grade >= 60) letter = 'D';
        else if (grade >= 0) letter = 'F';
        else {
            printf("Invalid grade.\n");
            continue;
        }
        
        printf("Your grade is %c\n", letter);
    }
}

int main() {
    grades_to_letters();
    return 0;
}

