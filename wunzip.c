//
//  wunzip.c
// 
//  Created by Gabriel Augustin.
//  wunzip is a UNIX utility that decompresses a file and
//  prints its contents onto the terminal.
//

#include <stdio.h>
#include <stdlib.h>

void wunzip(FILE* file) {
    int count;
    char ch;

    while (fread(&count, sizeof(int), 1, file) == 1 && (ch = getc(file)) != EOF) {
        for (int i = 0; i < count; i++) {
            putchar(ch);
        }
    }

    if (ferror(file)) {
        perror("fread");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "wunzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        if (file == NULL) {
            fprintf(stderr, "wunzip: cannot open file\n");
            return 1;
        }

        wunzip(file);

        if (fclose(file) != 0) {
            perror("fclose");
            return 1;
        }
    }

    return 0;
}
