#define _XOPEN_SOURCE 700 
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>

// commands:
// build: gcc -std=c11 -Wall -Wextra -O2 -o summarize_tree_ftw summarize_tree_ftw.c
// bats -f '^summarize_tree_ftw ' summarize_tree_test.bats
static int num_dirs, num_regular;

// count directories and regular files
// callback for ftw
static int callback(const char *fpath, const struct stat *sb, int typeflag) {
    (void)fpath; (void)sb;
    if (typeflag == FTW_D)      num_dirs++;
    else if (typeflag == FTW_F) num_regular++;
    return 0;
}

#define MAX_FTW_DEPTH 16

int main(int argc, char** argv) {
    // check arguments and set thing up
    if (argc != 2) {
        printf ("Usage: %s <path>\n", argv[0]);
        printf ("       where <path> is the file or root of the tree you want to summarize.\n");
        return 1;
    }

    num_dirs = 0;
    num_regular = 0;

    // traverse the tree and call counter
    (void)ftw(argv[1], callback, MAX_FTW_DEPTH);

    // Print out the results
    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
}
