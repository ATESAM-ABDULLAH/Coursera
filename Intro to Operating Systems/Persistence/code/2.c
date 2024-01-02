#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    if ((dir = opendir(argv[1])) == NULL)
    {
        perror("opendir");
        return EXIT_FAILURE;
    }

    printf("Inode\tName\n");

    while ((entry = readdir(dir)) != NULL)
    {
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);

        if (lstat(path, &fileStat) < 0)
        {
            perror("lstat");
            return EXIT_FAILURE;
        }

        printf("%ld\t%s\n", (long)fileStat.st_ino, entry->d_name);
    }

    closedir(dir);
    return EXIT_SUCCESS;
}
