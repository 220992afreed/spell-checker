 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_TABLE_SIZE 100
#define MAX_WORD_LENGTH 50


typedef struct Node {
    char word[MAX_WORD_LENGTH];
    struct Node* next;
} Node;

Node* hashTable[HASH_TABLE_SIZE];

int hash(const char* word) {

    int sum = 0;

    while (*word) {
        sum += tolower(*word);
        word++;
    }
    return sum % HASH_TABLE_SIZE;
}


void insert(const char* word) {
    int index = hash(word);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);

    }

    strncpy(newNode->word, word, MAX_WORD_LENGTH - 1);
    newNode->word[MAX_WORD_LENGTH - 1] = '\0';
    newNode->next = NULL;

    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }
}


int checkSpelling(const char* word) {

    int len = strlen(word);
    char cleanWord[MAX_WORD_LENGTH];
    int cleanIdx = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(word[i])) {

            cleanWord[cleanIdx++] = tolower(word[i]);
        }
    }

    cleanWord[cleanIdx] = '\0';

    int index = hash(cleanWord);
    Node* current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->word, cleanWord) == 0) {
            return 1; 
        }
        current = current->next;
    }
    return 0; 
}


int main() {
   for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    const char* words[] = {
        "hello", "world", "programming", "language", "computer",
        "algorithm", "code", "software", "developer", "debug",
        "variable", "function", "loop", "data", "structure",
        "java", "python", "c", "pointer", "logic"
    };

    for (int i = 0; i < sizeof(words) / sizeof(words[0]); ++i) {
        insert(words[i]);
    }

    char userInput[MAX_WORD_LENGTH];
    printf("Enter a word to check its spelling: ");

    scanf("%s", userInput);

    if (checkSpelling(userInput)) {
        printf("%s is correctly spelled.\n", userInput);
    } else {
        printf("%s is misspelled.\n", userInput);
    }

    return 0;
}
