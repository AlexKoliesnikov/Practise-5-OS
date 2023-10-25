#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[1024];

    printf("Enter commands (type 'exit' to quit):\n");

    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        }

        char *token = strtok(input, ";");

        while (token != NULL) {
            printf("Executing command: %s\n", token);
            int result = system(token);
            printf("Exit code: %d\n", result);
            token = strtok(NULL, ";");
        }
    }

    return 0;
}
