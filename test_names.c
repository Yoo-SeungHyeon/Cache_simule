#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_LINE_LENGTH 1024
#define OUTPUT_FILE_NAME "output.txt"

void extractAndWriteToFile(const char *filePath) {
    FILE *inputFile = fopen(filePath, "r");
    FILE *outputFile = fopen(OUTPUT_FILE_NAME, "a");

    if (inputFile == NULL || outputFile == NULL) {
        perror("File opening error");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int currentLine = 0;

    while (fgets(line, sizeof(line), inputFile) != NULL) {
        currentLine++;

        // 83번째 행에서 문장을 가져옴
        if (currentLine == 83) {
            // 파일 이름과 문장을 출력 파일에 저장
            fprintf(outputFile, "File: %s\n%s\n\n", filePath, line);
            break;
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}

void searchAndExtractTxtFiles(const char *path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        // 파일 이름이 ".txt"로 끝나는지 확인
        if (strlen(entry->d_name) >= 4 &&
            strcmp(entry->d_name + strlen(entry->d_name) - 4, ".txt") == 0) {
            char filePath[MAX_LINE_LENGTH];
            sprintf(filePath, "%s/%s", path, entry->d_name);
            extractAndWriteToFile(filePath);
        }
    }

    closedir(dir);
}

int main(void) {
    // 기존의 출력 파일을 초기화
    FILE *outputFile = fopen(OUTPUT_FILE_NAME, "w");
    if (outputFile != NULL) {
        fclose(outputFile);
    }

    // 현재 디렉토리에서 .txt 파일을 찾고 83번째 행의 문장을 출력 파일에 저장
    searchAndExtractTxtFiles(".");

    return 0;
}

