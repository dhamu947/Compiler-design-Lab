#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an instruction
typedef struct {
    char op[10];    // Operation (e.g., add, sub, mul, ...)
    char arg1[10];  // First argument
    char arg2[10];  // Second argument
    char result[10];// Result variable
} Instruction;

// Function to generate assembly-like code from three-address code
void generateAssembly(Instruction instructions[], int num_instructions) {
    printf("Generated Assembly Code:\n");

    for (int i = 0; i < num_instructions; i++) {
        printf("%s %s, %s, %s\n", instructions[i].op,
               instructions[i].result, instructions[i].arg1, instructions[i].arg2);
    }
}

int main() {
    // Example three-address code instructions
    Instruction instructions[] = {
        {"ADD", "a", "b", "t1"},
        {"SUB", "c", "d", "t2"},
        {"MUL", "t1", "t2", "t3"},
        {"ADD", "t3", "t1", "t4"},
        {"SUB", "t4", "t2", "t5"},
        {"MUL", "t3", "t4", "t6"}
    };

    int num_instructions = sizeof(instructions) / sizeof(instructions[0]);

    generateAssembly(instructions, num_instructions);

    return 0;
}
