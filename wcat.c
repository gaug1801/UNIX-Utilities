//
//  wcat.c
//
//  Created by Gabriel Augustin.
//  wcat is a UNIX utility that prints out a selected file onto the terminal.
//
#include <stdio.h>
#include <stdlib.h>

void wcat(const char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char ch;
    while((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    if (ferror(file)) {
        perror("fgetc");
        exit(EXIT_FAILURE);
    }

    if (fclose(file) != 0) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    for(int i = 1; i < argc; i++) {
        wcat(argv[i]);
    }

    return 0;
}
