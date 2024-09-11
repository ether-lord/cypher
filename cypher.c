#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <dirent.h>

const char* INVERTED_FILE_EXTENTION = ".v";
int decode = 0;

void process_file(char *filename);
void open_files(const char* filename, FILE** src_file, FILE** dst_file);
void reverse_bytes(FILE* input_file, FILE* output_file);
void swap_filenames(char** src, char** dst);
void remove_file(const char* filename);

int main(int argc, char* argv[]) {
    char* filename = NULL;
    char* directory_name = NULL;

    int opt = 0;

    while ((opt = getopt(argc, argv, "df:D:")) != -1) {
        switch (opt)
        {
        case 'd':
            decode = 1;
            break;
        case 'f':
            filename = optarg;
            break;
        case 'D':
            directory_name = optarg;
            break;
        default:
            break;
        }
    }

    if (directory_name) {
        DIR* dir_stream = opendir(directory_name);
        if (!dir_stream) {
            printf("%s\n", "Error: couldn't open the directory");
            exit(EXIT_FAILURE);
        }
        char filename[256];
       
        struct dirent* dir;
        while((dir = readdir(dir_stream)) != NULL) {
            if (dir->d_type == 8) {
                strcpy(filename, directory_name);
                strcat(filename, dir->d_name);
                printf("%s\n", filename);
                process_file(filename);
                memset(filename, 0, sizeof(filename));
            }
        }

        return 0;
    }

    if (!filename) {;
        printf("%s\n", "Error: no filename provided");
        exit(EXIT_FAILURE);
    }
    
    process_file(filename);

    return 0;
}

void process_file(char *filename) {;
    FILE *src_file, *dst_file;
    open_files(filename, &src_file, &dst_file);
    reverse_bytes(src_file, dst_file);
    fclose(src_file);
    fclose(dst_file);
    remove_file(filename);
}

void open_files(const char *filename, FILE **src_file, FILE **dst_file) {;
    unsigned int filename_size = (strlen(filename) * sizeof(char));

    char* source_filename = malloc(filename_size);
    strcpy(source_filename, filename);

    char* dest_filename = malloc(filename_size + strlen(INVERTED_FILE_EXTENTION) * sizeof(char));
    strcpy(dest_filename, filename);
    strcat(dest_filename, INVERTED_FILE_EXTENTION);

    if (decode)
        swap_filenames(&source_filename, &dest_filename);

    *src_file = fopen(source_filename, "rb");
    if (!(*src_file)) {
        printf("%s - %s\n", "Error: couldn't open the source file", source_filename);
        exit(EXIT_FAILURE);
    }

    *dst_file = fopen(dest_filename, "wb");
    if (!(*src_file)) {
        printf("%s\n", "Error: couldn't open the destination file");
        exit(EXIT_FAILURE);
    }

    free(source_filename);
    free(dest_filename);
}

void reverse_bytes(FILE *source_file, FILE *dest_file) {
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

void remove_file(const char *filename) {
    unsigned int filename_size = (strlen(filename) * sizeof(char));
    if (decode) {
        char* file = malloc(filename_size + strlen(INVERTED_FILE_EXTENTION) * sizeof(char));
        strcpy(file, filename);
        strcat(file, INVERTED_FILE_EXTENTION);
        remove(file);
        return;
    }
    remove(filename);
}
