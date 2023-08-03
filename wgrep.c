//
//  wgrep.c
//  
//  Created by Gabriel Augustin.
//  wgrep is UNIX utility that takes a searchword and prints
//  every line where the search word appears onto the terminal.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wgrep(const char* searchterm, FILE* file) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) {
        if (strstr(line, searchterm) != NULL) {
            printf("%s", line);
        }
    }

    free(line);

    if (ferror(file)) {
        perror("getline");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "wgrep: searchterm [filename.txt]\n");
        return 1;
    }

    if (argc == 2) {
        wgrep(argv[1], stdin);
    } else {
        for(int i = 2; i < argc; i++) {
            FILE* file = fopen(argv[i], "r");
            if (file == NULL) {
                fprintf(stderr, "wgrep: cannot open file\n");
                return 1;
            }
            wgrep(argv[1], file);

            if (fclose(file) != 0) {
                perror("fclose");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}
