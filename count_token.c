#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_FILENAME_LENGTH 100
#define MAX_TOKEN_LENGTH 1000

void save_token_count(char *filename, int *token_count) {
    FILE *output_file = fopen(filename, "w");
    if (output_file == NULL) {
        printf("Error: could not open file '%s' for writing.\n", filename);
        exit(1);
    }

    for (int i = 0; i < 256; i++) {
        if (token_count[i] > 0) {
            if (isprint(i)) {
                fprintf(output_file, "%c: %d\n", i, token_count[i]);
            } else {
                fprintf(output_file, "\\x%02x: %d\n", i, token_count[i]);
            }
        }
    }

    fclose(output_file);
}

int main() {
    char input_filename[MAX_FILENAME_LENGTH];
    char word_count_filename[MAX_FILENAME_LENGTH];
    char char_count_filename[MAX_FILENAME_LENGTH];
    FILE *input_file;
    int word_token_count[256] = {0};
    int char_token_count[256] = {0};

    // Prompt the user for the input filename
    printf("Enter the input filename: ");
    scanf("%s", input_filename);

    // Open the input file for reading
    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        printf("Error: could not open input file.\n");
        exit(1);
    }

    // Read each token (word or character) from the input file and count its occurrence
    char token[MAX_TOKEN_LENGTH];
    int is_word = 0;
    while (fscanf(input_file, "%s", token) == 1) {
        if (isalpha(token[0])) {
            is_word = 1;
        } else {
            is_word = 0;
        }

        for (int i = 0; token[i] != '\0'; i++) {
            char c = token[i];
            if (is_word) {
                word_token_count[c]++;
            } else {
                char_token_count[c]++;
            }
        }
    }

    // Generate the output filenames and save the token counts to separate files
    sprintf(word_count_filename, "%s_word_count.txt", input_filename);
    sprintf(char_count_filename, "%s_char_count.txt", input_filename);
    save_token_count(word_count_filename, word_token_count);
    save_token_count(char_count_filename, char_token_count);

    // Close the input file
    fclose(input_file);

    printf("Token counts saved to files:\n");
    printf("  %s\n", word_count_filename);
    printf("  %s\n", char_count_filename);

    return 0;
}
