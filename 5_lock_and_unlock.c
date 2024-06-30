#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// Function to lock a file
void file_lock(int fd) {
    struct flock fl = {0};
    fl.l_type = F_WRLCK; // Write lock
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0; // Lock entire file
    fcntl(fd, F_SETLKW, &fl); // Acquire the lock
    printf("File locked successfully!\n");
}

// Function to unlock a file
void file_unlock(int fd) {
    struct flock fl = {0};
    fl.l_type = F_UNLCK; // Unlock
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0; // Unlock entire file
    fcntl(fd, F_SETLK, &fl); // Release the lock
    printf("File unlocked successfully!\n");
}

int main() {
    // Open the file, creating it if it does not exist
    int fd = open("testfile.txt", O_RDWR | O_CREAT, 0666);

    // Write initial content to the file
    write(fd, "Hello, world!\n", 14);

    // Lock the file
    file_lock(fd);

    // Write to the locked file
    write(fd, "Locked file content\n", 20);

    // Unlock the file
    file_unlock(fd);

    // Write to the unlocked file
    write(fd, "Unlocked file content\n", 22);

    // Close the file
    close(fd);

    return 0;
}
