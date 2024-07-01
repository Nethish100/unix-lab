#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];
    struct stat file_stat;

    // Create hard link
    if (link(filename, "hard_link") == -1) {
        perror("Error creating hard link");
        exit(EXIT_FAILURE);
    }

    // Create symbolic link
    if (symlink(filename, "sym_link") == -1) {
        perror("Error creating symbolic link");
        exit(EXIT_FAILURE);
    }

    // Get file information for the original file
    if (stat(filename, &file_stat) == -1) {
        perror("Error getting file information");
        exit(EXIT_FAILURE);
    }
    printf("Original file links: %ld\n", file_stat.st_nlink);

    // Get file information for the symbolic link
    if (lstat("sym_link", &file_stat) == -1) {
        perror("Error getting symbolic link information");
        exit(EXIT_FAILURE);
    }
    printf("Symbolic link links: %ld\n", file_stat.st_nlink);

    return 0;
}
