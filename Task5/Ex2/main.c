#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int num_handlers;

void signal_handler(int signum) {
    static int count = 0;
    count++;
    printf("Handler %d: Delaying for 1 second. Signal %d received.\n", count, signum);
    sleep(1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_handlers>\n", argv[0]);
        return 1;
    }

    num_handlers = atoi(argv[1]);

    if (num_handlers < 1) {
        printf("Number of handlers should be greater than 0.\n");
        return 1;
    }

    for (int i = 1; i <= num_handlers; i++) {
        if (signal(SIGINT, signal_handler) == SIG_ERR) {
            printf("Error registering handler for SIGINT.\n");
            return 1;
        }
    }

    printf("Waiting for process termination handlers. PID = %d\n", getpid());

    while (1) {
    }

    return 0;
}
