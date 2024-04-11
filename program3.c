#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

int is_text_file(FILE *file);

void convert_to_unix(FILE *file);

int main(int argc, char *argv[]) {
    char filename[BUFFER_SIZE];
    FILE *input_file;

    // Flag to indicate if the "-u" flag has been encountered
    int unix_conversion_flag = 0;

    // Loop through each filename from stdin
    while (fgets(filename, BUFFER_SIZE, stdin) != NULL) {
        // Remove newline character from the end of filename
        filename[strcspn(filename, "\n")] = '\0';

        if (argc == 2) {
            unix_conversion_flag = 1;
        }

        // Open the file
        input_file = fopen(filename, "r+");
        if (input_file == NULL) {
            // Error message if file could not be opened
            fprintf(stderr, "Error: Could not open file %s\n", filename);
            continue;
        }

        // Check if the file is a text file
        if (!is_text_file(input_file)) {
            // Display message on stderr if file is not text
            fprintf(stderr, "%s is not a text file\n", filename);

            // If "-u" flag is provided and file is Windows formatted text
            if (unix_conversion_flag == 1) {
                convert_to_unix(input_file);
                unix_conversion_flag = 0; // Reset the flag after conversion
            }
            
            fclose(input_file);
            continue;
        }

        // Display the filename on stdout
        printf("%s is a txt file\n", filename);

        

        fclose(input_file);
    }

    return 0;
}

// Function to check if a file is text or binary
int is_text_file(FILE *file) {
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (!(ch == '\n' || (ch >= 32 && ch <= 126))) {
            rewind(file);
            return 0; // Not a text file
        }
    }
    rewind(file);
    return 1; // Text file
}

// Function to convert Windows formatted text file to Unix format
void convert_to_unix(FILE *file) {
    FILE *temp_file = tmpfile(); // Creates a temporary file
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch != '\r') {
            fputc(ch, temp_file); // Write characters to the temporary file without '\r'
        }
    }
    rewind(temp_file); // Rewind the temporary file to the beginning
    rewind(file); // Rewind the original file to the beginning

    // Open the original file in read/write mode
    freopen(NULL, "r+", file);
    
    while ((ch = fgetc(temp_file)) != EOF) {
        fputc(ch, file); // Write characters from the temporary file back to the original file
    }
    fclose(temp_file); // Close the temporary file

    printf("Conversion completed.\n"); // Debug output
}

