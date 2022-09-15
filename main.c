#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseWord (char *strList, char *words[]);
void getWord (char *enterWord);
void searchWord (char *words[], int numWordsList, const char *enterWord);

int main() {
    FILE *pFileList = NULL;
    char *strList = NULL;
    char  enterWord[20];
    long  numBytesList = 0;
    long  numWordsList = 0;

    //read word list
    pFileList = fopen("words", "r");
    if(!pFileList) {
        printf("The words file was not found.");
        return 1;
    }

    fseek(pFileList, 0L, SEEK_END);
    numBytesList = ftell(pFileList);
    fseek(pFileList, 0L, SEEK_SET);

    strList = (char*)calloc(numBytesList, sizeof(char));
    if(!strList) {
        printf("Memory allocation failed.");
        return 1;
    }


    fread(strList, sizeof(char), numBytesList, pFileList);
    fclose(pFileList);

    //parse word list
    for (int i = 0; i < numBytesList; i++)
        if (strList[i]=='\n')
            numWordsList++;

    char *words[numWordsList+1];
    for (int i = 0; i < numWordsList; i++)
        words[i] = NULL;

    parseWord(strList, words);

    getWord(enterWord);

    searchWord(words, numWordsList, enterWord);

    free(strList);
    strList = NULL;

    return 0;
}

void parseWord (char *strList, char *words[]){

    int i = 0;

    char *pch = strtok (strList,"\n");
    words[i++] = pch;

    while (pch != NULL)
    {
        pch = strtok (NULL, "\n");
        words[i++] = pch;
    }

}

void getWord (char *enterWord) {

    printf("Enter a word:");
    scanf("%s", enterWord);

}

void searchWord (char *words[], int numWordsList, const char *enterWord) {

    int j = 1;
    int i = 0;
    for (; i < numWordsList && j != 0; i++) {
        j = strcmp(words[i], enterWord);
    }


    if (j == 0)
        printf("The word \"%s\" was found as \"%s\".\n", enterWord, words[--i]);
    else
        printf("The word \"%s\" was not found.\n", enterWord);

}
