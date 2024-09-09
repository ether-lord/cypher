#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* INVERTED_FILE_EXTENTION = ".inv";

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("%s\n", "Error: no filename provied");
        exit(EXIT_FAILURE);
    }

    char* inverted_filename = argv[1];
    FILE* inverted_file = fopen(inverted_filename, "rb");
    if (inverted_file == NULL) {
        printf("%s\n", "Error: failed to open the file");
        exit(EXIT_FAILURE);
    }

    unsigned int filename_size = (strlen(inverted_filename) - 4) * sizeof(char);
    char* filename = malloc(filename_size);
    strncpy(filename, inverted_filename, filename_size);

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("%s\n", "Error: failed to open the file to write");
        exit(EXIT_FAILURE);
    }

    unsigned char byte;
    while (!feof(inverted_file)) {
        fread(&byte, 1, 1, inverted_file);
        byte ^= 0xff;
        fwrite(&byte, 1, 1, file);
    }

    fclose(inverted_file);
    fclose(file);

    free(filename);
    return 0;
}