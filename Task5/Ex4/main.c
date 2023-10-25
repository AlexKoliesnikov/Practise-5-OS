#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char *FILE_NAME = "default";

void create_child_process(int number) {
    pid_t pid = fork();

    if (pid == 0) {
        char filename[50];
        sprintf(filename, "%s_%d.txt", FILE_NAME, number);

        FILE *file = fopen(filename, "w");
        if (file != NULL) {
            for (int i = 0; i < number; i++) {
                double random_number = (double)rand() / RAND_MAX;
                fprintf(file, "%lf\n", random_number);
            }
            fclose(file);
        } else {
            fprintf(stderr, "Error: Unable to open file for writing at %s\n", filename);
            exit(1);
        }
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    int num_children = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
            if (i + 1 < argc) {
                FILE_NAME = argv[i + 1];
                i++;
            } else {
                fprintf(stderr, "Error: Argument expected for option -f\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0) {
            if (i + 1 < argc) {
                num_children = atoi(argv[i + 1]);
                i++;
            } else {
                fprintf(stderr, "Error: Argument expected for option -n\n");
                return 1;
            }
        }
    }

    for (int i = 1; i <= num_children; i++) {
        create_child_process(i);
    }

    for (int i = 1; i <= num_children; i++) {
        wait(NULL);
    }

    return 0;
}
