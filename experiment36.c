#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h> // Include for pow function

// Function to evaluate expressions respecting operator precedence
int evaluateExpression(const char *expression) {
    int result = 0;
    int i = 0;

    // Initial state
    int current_number = 0;
    char current_operator = '+';
    int last_number = 0;
    char last_operator = '+';

    while (expression[i] != '\0') {
        if (isdigit(expression[i])) {
            // Read the number
            current_number = 0;
            while (isdigit(expression[i])) {
                current_number = current_number * 10 + (expression[i] - '0');
                i++;
            }

            // Apply the last operator to the last number
            switch (last_operator) {
                case '+':
                    result += last_number;
                    last_number = current_number;
                    break;
                case '-':
                    result += last_number;
                    last_number = -current_number;
                    break;
                case '*':
                    last_number *= current_number;
                    break;
                case '/':
                    if (current_number != 0)
                        last_number /= current_number;
                    else {
                        printf("Error: Division by zero!\n");
                        return 0; // Exit with error
                    }
                    break;
                case '^':
                    last_number = (int) pow(last_number, current_number); // Cast result of pow to int
                    break;
            }

        } else if (expression[i] == '+' || expression[i] == '-' ||
                   expression[i] == '*' || expression[i] == '/' ||
                   expression[i] == '^') {
            // Update current operator
            last_operator = expression[i];
            i++;
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
            char *sub_expression = (char *) malloc((j - i) * sizeof(char)); // Explicit cast to char*
            strncpy(sub_expression, &expression[i + 1], j - i - 1);
            sub_expression[j - i - 1] = '\0';

            current_number = evaluateExpression(sub_expression);
            free(sub_expression);

            i = j; // Move index after closing parenthesis
        } else {
            // Skip whitespaces
            if (expression[i] == ' ')
                i++;
        }
    }

    // Apply the last operator and number
    switch (last_operator) {
        case '+':
            result += last_number;
            break;
        case '-':
            result += last_number;
            break;
        case '*':
            result += last_number;
            break;
        case '/':
            result += last_number;
            break;
    }

    return result;
}

int main() {
    char expression[100];

    printf("Enter an arithmetic expression: ");
    fgets(expression, sizeof(expression), stdin);

    // Remove newline character from fgets input
    expression[strcspn(expression, "\n")] = '\0';

    int result = evaluateExpression(expression);
    printf("Result of the expression \"%s\" is: %d\n", expression, result);

    return 0;
}
