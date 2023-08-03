//
//  wzip.c
//
//  Created by Gabriel Augustin.
//  wzip is a UNIX utility that compresses the contents of a file.
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int count;
    char c, current;

    // Ensure correct usage
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    // Iterate through each file
    for (int i = 1; i < argc; i++) {
        if ((fp = fopen(argv[i], "r")) == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        // If first file, initialize variables
        if (i == 1) {
            current = fgetc(fp);
            count = 1;
        }

        // Read file character by character
        while ((c = fgetc(fp)) != EOF) {
            if (c == current) {
                count++;
            } else {
                // Write count and character to stdout
                fwrite(&count, 4, 1, stdout);
                fwrite(&current, 1, 1, stdout);

                // Reset count and current character
                count = 1;
                current = c;
            }
        }

        fclose(fp);
    }

    // Write count and character for last sequence
    fwrite(&count, 4, 1, stdout);
    fwrite(&current, 1, 1, stdout);

    return 0;
}
