#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Structure to represent an expression
typedef struct {
    char result[10];   // Variable name for the result of the expression
    char op;           // Operator (+, -, *, /, ^)
    char arg1[10];     // First argument
    char arg2[10];     // Second argument
} Expression;

// Function to perform common subexpression elimination
void eliminateCommonSubexpressions(Expression expressions[], int num_expressions) {
    bool eliminated[num_expressions]; // Array to track eliminated expressions
    memset(eliminated, false, sizeof(eliminated)); // Initialize all as not eliminated

    for (int i = 0; i < num_expressions; i++) {
        if (!eliminated[i]) {
            for (int j = i + 1; j < num_expressions; j++) {
                if (!eliminated[j] &&
                    strcmp(expressions[i].arg1, expressions[j].arg1) == 0 &&
                    strcmp(expressions[i].arg2, expressions[j].arg2) == 0 &&
                    expressions[i].op == expressions[j].op) {
                    // Found common subexpression
                    printf("Common subexpression found between %s and %s\n",
                           expressions[i].result, expressions[j].result);
                    strcpy(expressions[j].result, expressions[i].result); // Replace with common result
                    eliminated[j] = true; // Mark as eliminated
                }
            }
        }
    }

    // Print optimized expressions
    printf("\nOptimized Expressions:\n");
    for (int i = 0; i < num_expressions; i++) {
        if (!eliminated[i]) {
            printf("%s = %s %c %s\n", expressions[i].result, expressions[i].arg1,
                   expressions[i].op, expressions[i].arg2);
        }
    }
}

int main() {
    // Example expressions to optimize
    Expression expressions[] = {
        {"t1", '+', "a", "b"},
        {"t2", '-', "c", "d"},
        {"t3", '*', "t1", "t2"},
        {"t4", '+', "t3", "t1"},
        {"t5", '-', "t4", "t2"},
        {"t6", '*', "t3", "t4"},
    };

    int num_expressions = sizeof(expressions) / sizeof(expressions[0]);

    printf("Original Expressions:\n");
    for (int i = 0; i < num_expressions; i++) {
        printf("%s = %s %c %s\n", expressions[i].result, expressions[i].arg1,
               expressions[i].op, expressions[i].arg2);
    }

    eliminateCommonSubexpressions(expressions, num_expressions);

    return 0;
}
