#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function to generate three-address code for an arithmetic expression
void generateThreeAddressCode(const char *expression) {
    int temp_counter = 1; // Counter for temporary variables
    int i = 0;

    while (expression[i] != '\0') {
        if (isdigit(expression[i])) {
            // Read the number
            int num_start = i;
            while (isdigit(expression[i]))
                i++;
            int num_end = i;
            
            char temp_var[5]; // Temporary variable for the number
            snprintf(temp_var, sizeof(temp_var), "t%d", temp_counter++);
            printf("%s = %.*s\n", temp_var, num_end - num_start, &expression[num_start]);
        } else if (expression[i] == '+' || expression[i] == '-' ||
                   expression[i] == '*' || expression[i] == '/' ||
                   expression[i] == '^') {
            // Read the operator
            char op = expression[i++];
            
            // Read the operand
            int num_start = i;
            while (isdigit(expression[i]))
                i++;
            int num_end = i;
            
            char temp_var1[5]; // Temporary variable for the first operand
            snprintf(temp_var1, sizeof(temp_var1), "t%d", temp_counter++);
            
            char temp_var2[5]; // Temporary variable for the second operand
            snprintf(temp_var2, sizeof(temp_var2), "t%d", temp_counter++);
            
            printf("%s = %.*s %c %.*s\n", temp_var1, num_end - num_start, &expression[num_start], op, num_end - num_start, &expression[num_start]);
            printf("%s = %s %c %s\n", temp_var2, temp_var1, op, temp_var1);
        } else if (expression[i] == '(') {
            // Find matching closing parenthesis
            int count = 1;
            int j = i + 1;
            while (count != 0 && expression[j] != '\0') {
                if (expression[j] == '(')
                    count++;
                else if (expression[j] == ')')
                    count--;
                j++;
            }
            
            // Evaluate the sub-expression
            char sub_expression[100]; // Buffer for sub-expression
            strncpy(sub_expression, &expression[i + 1], j - i - 2);
            sub_expression[j - i - 2] = '\0';
            
            generateThreeAddressCode(sub_expression);
            
            i = j; // Move index after closing parenthesis
        } else {
            // Skip whitespaces
            if (expression[i] == ' ')
                i++;
        }
    }
}

int main() {
    char expression[100];

    printf("Enter an arithmetic expression: ");
    fgets(expression, sizeof(expression), stdin);

    // Remove newline character from fgets input
    expression[strcspn(expression, "\n")] = '\0';

    printf("Three Address Code:\n");
    generateThreeAddressCode(expression);

    return 0;
}
