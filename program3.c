#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Function to check if a file is text or binary
int is_text_file(FILE *file);

int main(int argc, char *argv[]) {
    char filename[BUFFER_SIZE];
    FILE *input_file;
    int i;

    // Loop through each filename from stdin
    for (i = 1; i < argc; i++) {
        // if the argument is a string - ignore (for now) and move on
        if (strcmp(argv[i], "-u") == 0){
            continue;
        }
        // Open the file
        input_file = fopen(argv[i], "rb");
        if (input_file == NULL) {
            // Error message if file could not be opened
            fprintf(stderr, "Error: Could not open file %s\n", argv[i]);
            continue;
        }

        // Check if the file is a text file
        if (!is_text_file(input_file)) {
            // Display message on stderr if file is not text
            fprintf(stderr, "%s is not a text file\n", argv[i]);
            fclose(input_file);
            continue;
        }

        // Display the filename on stdout
        printf("%s\n", argv[i]);

        // If "-u" flag is provided and file is Windows formatted text
        if (argc > 2 && strcmp(argv[1], "-u") == 0) {
            // convert(input_file) to be implemented
            printf(" to be converted to unix");
        }

        fclose(input_file);
    }

    return 0;
}

// Function to check if a file is text or binary
int is_text_file(FILE *file) {
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (!(ch == '\n' || ch == '\r' || (ch >= 32 && ch <= 126))) {
            rewind(file);
            printf("This is not a txt file : ");
            return 0; // Not a text file
        }
    }
    rewind(file);
    printf("This is a txt file : ");
    return 1; // Text file
}