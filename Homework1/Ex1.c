#include <stdio.h>

void calculate_arithmetic_operations() {
    double num1, num2, result;
    char op;
    
    printf("Enter arithmetic expression");
    scanf("%lf %c %lf", &num1, &op, &num2);
    
    switch (op) {
        case '+':
            result = num1 + num2;
            printf("%.2f %c %.2f = %.2f\n", num1, op, num2, result);
            break;
        case '-':
            result = num1 - num2;
            printf("%.2f %c %.2f = %.2f\n", num1, op, num2, result);
            break;
        case '*':
            result = num1 * num2;
            printf("%.2f %c %.2f = %.2f\n", num1, op, num2, result);
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                printf("%.2f %c %.2f = %.3f\n", num1, op, num2, result);
            } else {
                printf("Division by zero is not allowed.\n");
            }
            break;
        default:
            printf("Invalid operator!\n");
    }
}

int main() {
    calculate_arithmetic_operations();
    return 0;
}

