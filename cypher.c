#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

const char* INVERTED_FILE_EXTENTION = ".v";

void reverse_bytes(FILE* input_file, FILE* output_file);
void swap_filenames(char** src, char** dst);

int main(int argc, char* argv[]) {
    int decode = 0;
    char* filename = NULL;

    int opt = 0;
    while ((opt = getopt(argc, argv, "df:")) != -1) {
        switch (opt)
        {
        case 'd':
            decode = 1;
            break;
        case 'f':
            filename = optarg;
            break;
        default:
            break;
        }
    }

    if (filename == NULL) {
        printf("%s\n", "Error: no filename provided");
        exit(EXIT_FAILURE);
    }
    
    unsigned int filename_size = (strlen(filename) * sizeof(char));

    char* source_filename = malloc(filename_size);
    strcpy(source_filename, filename);

    char* dest_filename = malloc(filename_size + strlen(INVERTED_FILE_EXTENTION));
    strcpy(dest_filename, filename);
    strcat(dest_filename, INVERTED_FILE_EXTENTION);

    if (decode)
        swap_filenames(&source_filename, &dest_filename);

    FILE* src_file = fopen(source_filename, "rb");
    if (src_file == NULL) {
        printf("%s\n", "Error: couldn't open the source file");
        exit(EXIT_FAILURE);
    }

    FILE* dst_file = fopen(dest_filename, "wb");
    if (src_file == NULL) {
        printf("%s\n", "Error: couldn't open the destination file");
        exit(EXIT_FAILURE);
    }

    reverse_bytes(src_file, dst_file);

    fclose(src_file);
    fclose(dst_file);

    remove(source_filename);

    free(source_filename);
    free(dest_filename);
    return 0;
}

void reverse_bytes(FILE* source_file, FILE* dest_file) {
    unsigned char byte;
    while (!feof(source_file)) {
        fread(&byte, 1, 1, source_file);
        byte ^= 0xff;
        fwrite(&byte, 1, 1, dest_file);
    }
}

void swap_filenames(char** src, char** dst) {
    char* tmp = *src;
    *src = *dst;
    *dst = tmp;
}
