#include <stdio.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000

// Function to count characters, words, and lines
void countCharsWordsLines(FILE *file) {
    int char_count = 0;
    int word_count = 0;
    int line_count = 0;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file) != NULL) {
        line_count++;

        // Count characters
        char_count += strlen(line);

        // Count words
        int in_word = 0; // Flag to track if we're in a word
        for (int i = 0; line[i] != '\0'; i++) {
            if (isspace(line[i])) {
                if (in_word) {
                    word_count++;
                    in_word = 0;
                }
            } else {
                in_word = 1;
            }
        }
        // Check for last word in the line
        if (in_word) {
            word_count++;
        }
    }

    printf("Number of characters: %d\n", char_count);
    printf("Number of words: %d\n", word_count);
    printf("Number of lines: %d\n", line_count);
}

int main() {
    FILE *file;
    char filename[100];

    printf("Enter the filename: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    countCharsWordsLines(file);

    fclose(file);

    return 0;
}
