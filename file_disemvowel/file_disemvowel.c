#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Testing command line:
// gcc -std=c11 -Wall -Wextra -O2 -o file_disemvowel file_disemvowel.c
// bats tests/file_disemvowel_test.bats
// valgrind --leak-check=full ./file_disemvowel < tests/small_input > /dev/null

// buffer size for reading/writing
#define BUF_SIZE 1024

// return true if char c fall into being a vowel, false otherwise
// for both upper and lower case
bool is_vowel(char c) {
    switch (c) {
        case 'a': case 'e': case 'i': case 'o': case 'u':
        case 'A': case 'E': case 'I': case 'O': case 'U':
            return true;
        default:
            return false;
    }
}

// this copy all non vowels from in_buf to out_buf
// then return with the number of non-vowel chars copied
int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    int w = 0;
    for (int r = 0; r < num_chars; r++) {
        if (!is_vowel(in_buf[r])) {
            out_buf[w++] = in_buf[r];
        }
    }
    return w;
}

// read from input file -> disemvowel it -> write to output file
void disemvowel(FILE* inputFile, FILE* outputFile) {
    char in_buf[BUF_SIZE];
    char out_buf[BUF_SIZE];
    size_t got;

    while ((got = fread(in_buf, 1, sizeof(in_buf), inputFile)) > 0) {
        int keep = copy_non_vowels((int)got, in_buf, out_buf);
        if (keep > 0) {
            // write to output file only if there's something to write
            fwrite(out_buf, 1, (size_t)keep, outputFile);
        }
    }
}

// handle files open/close
int main(int argc, char *argv[]) {
    FILE *inputFile = stdin;
    FILE *outputFile = stdout;
    bool close_in = false, close_out = false;

    // handle command line arguments
    if (argc > 3) {
        fprintf(stderr, "Usage: %s [input_file [output_file]]\n", argv[0]);
        return 1;
    }

    // open input file if provided
    if (argc >= 2) {
        inputFile = fopen(argv[1], "rb");
        if (!inputFile) { perror("fopen input"); return 1; }
        close_in = true;
    }

    // open output file if provided
    if (argc == 3) {
        outputFile = fopen(argv[2], "wb");
        if (!outputFile) {
            perror("fopen output");
            if (close_in) fclose(inputFile);
            return 1;
        }
        close_out = true;
    }

    // process the files
    disemvowel(inputFile, outputFile);

    // close input files if opened
    if (close_in) fclose(inputFile);
    // close output file if opened
    if (close_out) fclose(outputFile);
    return 0;
}
