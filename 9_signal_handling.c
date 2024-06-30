#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Signal handler function
void sig_handler(int signum) {
    printf("Received signal: %d\n", signum);
}

int main() {
    struct sigaction sa;
    sigset_t new_mask;

    // Set up the signal handler
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Register signal handler for SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    printf("Signal handler registered for SIGINT (Ctrl+C)\n");

    // Initialize and add SIGINT to the new signal mask
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGINT);

    // Add SIGINT to the signal mask
    if (sigprocmask(SIG_BLOCK, &new_mask, NULL) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }
    printf("SIGINT is added to the signal mask.\n");

    // Wait for signals indefinitely
    while (1) {
        sleep(1);
    }

    return 0;
}
