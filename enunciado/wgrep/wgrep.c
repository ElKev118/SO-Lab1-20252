#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void search_and_print(FILE *stream, const char *searchterm) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line, &len, stream)) != -1) {
        if (strstr(line, searchterm) != NULL) {
            printf("%s", line);
        }
    }
    free(line);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    const char *searchterm = argv[1];

    if (argc == 2) {
        search_and_print(stdin, searchterm);
    } else {
        for (int i = 2; i < argc; i++) {
            FILE *file_pointer = fopen(argv[i], "r");
            if (file_pointer == NULL) {
                printf("wgrep: cannot open file\n");
                exit(1);
            }
            search_and_print(file_pointer, searchterm);
            fclose(file_pointer);
        }
    }

    return 0;
}
