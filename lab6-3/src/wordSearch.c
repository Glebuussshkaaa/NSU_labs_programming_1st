#include "wordSearch.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_LENGTH_STRING 10000

static char* CreateNewPrefix(const char* currentPrefix, const int currentPrefixLength, const char* key, const int keyLength) {
    int newPrefixLength = currentPrefixLength + keyLength;
    char* newPrefix = (char*)malloc(newPrefixLength + 1);
    assert(newPrefix != NULL);
    strncpy(newPrefix, currentPrefix, currentPrefixLength);
    strncpy(newPrefix + currentPrefixLength, key, keyLength);
    newPrefix[newPrefixLength] = '\0';
    return newPrefix;
}

static void FindWordsWithLink(const TTree* tree, const char* currentPrefix, const int currentPrefixLength) {
    if (tree == NULL) {
        return;
    }

    char* newPrefix = CreateNewPrefix(currentPrefix, currentPrefixLength, tree->Key, tree->KeyLength);

    if (tree->IsWord) {
        printf("%s ", newPrefix);
    }

    FindWordsWithLink(tree->Link, newPrefix, currentPrefixLength + tree->KeyLength);
    free(newPrefix);
    FindWordsWithLink(tree->Next, currentPrefix, currentPrefixLength);
}

static void FindWords(const TTree* tree, const char* searchPrefix, const int searchPrefixLength, const char* currentPrefix, const int currentPrefixLength) {
    if (tree == NULL) {
        printf("None");
        return;
    }

    int commonLength = GetCommonLength(tree->Key, searchPrefix);

    if (commonLength == searchPrefixLength) {
        char* newPrefix = CreateNewPrefix(currentPrefix, currentPrefixLength, tree->Key, tree->KeyLength);

        if (tree->IsWord) {
            printf("%s ", newPrefix);
        }

        FindWordsWithLink(tree->Link, newPrefix, currentPrefixLength + tree->KeyLength);

        free(newPrefix);
    } else if (commonLength == tree->KeyLength) {
        char* newPrefix = CreateNewPrefix(currentPrefix, currentPrefixLength, tree->Key, tree->KeyLength);

        FindWords(tree->Link, searchPrefix + commonLength, searchPrefixLength - commonLength, newPrefix, currentPrefixLength + tree->KeyLength);

        free(newPrefix);
    } else {
        FindWords(tree->Next, searchPrefix, searchPrefixLength, currentPrefix, currentPrefixLength);
    }
}

void PrintWords(const TTree* tree, const char* searchPrefix) {
    char* currentPrefix = malloc(sizeof(char) * (MAX_LENGTH_STRING + 1));
    assert(currentPrefix != NULL);
    currentPrefix[0] = '\0';

    FindWords(tree, searchPrefix, (int)strlen(searchPrefix), currentPrefix, 0);

    free(currentPrefix);
}
