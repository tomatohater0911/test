#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 100  

// Функция для вычисления хеша поступаемой строки
unsigned int hash(const char* str) {
    unsigned int hash_value = 0;
    while (*str) {
        hash_value = (hash_value * 21) + (*str);
        str++;
    }
    return hash_value;
}

// Функция для поиска хеша в файле
int searchHashInFile(unsigned int targetHash, const char *DB) {
    FILE* file = fopen("DB.txt", "r");
    if (file == NULL) {
        perror("Oshibka otrkriti'a fai'la");
        return -1;
    }

    unsigned int hash_value;
    char line[MAX_STRING_LENGTH];

    while (fscanf(file, "%u %s", &hash_value, line) != EOF) {
        if (hash_value == targetHash) {
            printf("Dubl' nai'den: %s\n", line);
            fclose(file);
            return 1; // Нашли дубль
        }
    }

    fclose(file);
    return 0; // Не нашли дубль
}


void saveHashAndStringToFile(unsigned int hash_value, const char* str, const char* DB) {
    FILE* file = fopen("DB.txt", "a");
    if (file == NULL) {
        perror("Oshibka pri otrkritii fai'la");
        return;
    }

    fprintf(file, "%u %s\n", hash_value, str);
    fclose(file);
}

int main() {
    char input[MAX_STRING_LENGTH];
    printf("Vvedite stroku: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        perror("Oshibka pri chtenii stroki");
        return 1;
    }

    
    input[strcspn(input, "\n")] = '\0';

    unsigned int hash_value = hash(input);

   
    int result = searchHashInFile(hash_value, "DB.txt");

    if (result == 0) {
        saveHashAndStringToFile(hash_value, input, "DB.txt");
        printf("Stroka sohranena v fai'le.\n");
    }
    else if (result == -1) {
        printf("Oshibka pri poiske v fai'le.\n");
    }

    return 0;
}
