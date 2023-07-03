#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int isDirectory(const char *folderPath, const char *entryName) {
    char path[FILENAME_MAX];
    snprintf(path, sizeof(path), "%s/%s", folderPath, entryName);

    struct stat statbuf;
    if (stat(path, &statbuf) != 0) {
        return 0;
    }

    return S_ISDIR(statbuf.st_mode);
}

void renameFiles(const char *folderPath, const char *oldName, const char *newName) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(folderPath);
    if (dir == NULL) {
        printf("Unable to open directory: %s\n", folderPath);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (isDirectory(folderPath, entry->d_name)) {
            char subDirPath[FILENAME_MAX];
            snprintf(subDirPath, sizeof(subDirPath), "%s/%s", folderPath, entry->d_name);

            renameFiles(subDirPath, oldName, newName);
        } else {
            if (strncmp(entry->d_name, oldName, strlen(oldName)) == 0) {
                char oldPath[FILENAME_MAX];
                snprintf(oldPath, sizeof(oldPath), "%s/%s", folderPath, entry->d_name);

                char newPath[FILENAME_MAX];
                snprintf(newPath, sizeof(newPath), "%s/%s%s", folderPath, newName, entry->d_name + strlen(oldName));

                if (rename(oldPath, newPath) != 0) {
                    printf("Error renaming file: %s\n", entry->d_name);
                }
            }
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: ./program <folderPath> <oldName> <newName>\n");
        return 1;
    }

    const char *folderPath = argv[1];
    const char *oldName = argv[2];
    const char *newName = argv[3];

    renameFiles(folderPath, oldName, newName);

    return 0;
}
