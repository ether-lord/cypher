#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("%s\n", "Error: no filename provied");
        exit(EXIT_FAILURE);
    }

    char* filename = argv[1];
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("%s\n", "Error: failed to open the file");
        exit(EXIT_FAILURE);
    }

    char* inverted_filename = malloc(strlen(filename) * sizeof(char));
    strcpy(inverted_filename, filename);
    strcat(inverted_filename, ".inv");
    FILE* inverted_file = fopen(inverted_filename, "wb");
    if (inverted_file == NULL) {
        printf("%s\n", "Error: failed to open the file to write");
        exit(EXIT_FAILURE);
    }

    unsigned char byte;
    while (!feof(file)) {
        fread(&byte, 1, 1, file);
        byte ^= 0xff;
        fwrite(&byte, 1, 1, inverted_file);
    }

    fclose(file);
    return 0;
}