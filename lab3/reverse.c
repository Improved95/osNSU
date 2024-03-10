#include <dirent.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void reverseString(char *string) {
    int len = strlen(string);
    for (int i = 0; i < len / 2; i++) {
        char c = string[i];
        string[i] = string[len - 1 - i];
        string[len - 1 - i] = c;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) exit(-1);

    DIR *d;
    struct dirent *dir;
    d = opendir(argv[1]);

    if (!d) exit(-1);

    reverseString(argv[1]);
    mkdir(argv[1], 0700);

    struct stat buf;
    int x;
    while ((dir = readdir(d)) != NULL) {
        
        char filePath[2560];
        reverseString(argv[1]);
        snprintf(filePath, sizeof filePath, "%s/%s", argv[1], dir->d_name);
        reverseString(argv[1]);

        x = stat(filePath, &buf);
        if (!S_ISREG(buf.st_mode)) continue;

        reverseString(dir->d_name);
        snprintf(filePath, sizeof filePath, "%s/%s", argv[1], dir->d_name);

        FILE *fileOut = fopen(filePath, "wи");
        if (fileOut == NULL) {
            printf("File not create\n");
            exit(-1);
        }

        // fclose(fileOut);
    }

    closedir(d);
    return 0;
}