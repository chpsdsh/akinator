#include <stdio.h>
#include "tree.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int getnum(char *str){
    int i = 0, ressize = 0;
    char *res = (char*) malloc(sizeof(char));
    while(str[i] != '_'){
        res[i] = str[i];
        ressize++;
        realloc(res,ressize*sizeof(char));
        i++;
    }
    res[i] = '\0';
    return atoi(res);
}
char *getQuestion(char *str){
    int ind = 0, ressize = 0;
    char *res = (char*) malloc(sizeof(char));

    while(str[ind] != '_')
        ind++;


    for (int i = ind+1; i < strlen(str); i++){
        res[i - ind - 1] = str[i];
        ressize++;
        realloc(res,ressize*sizeof(char));
        res[i+1] = '\0';
    }

    return res;
}

void FileToTree(TREE *T, FILE *file){
    char buffer[256];
    fgets(buffer,sizeof(buffer),file);

    T = create(getQuestion(buffer), getnum(buffer));
    while(fgets(buffer,sizeof(buffer),file) != NULL){
        add(T, getQuestion(buffer), getnum(buffer));
    }
    PreOrder(T);
}


int main() {
    FILE *file;
    file = fopen("data.txt","r");
    TREE *T;


    if (file == NULL) {
        puts("ERROR");
        exit(0);
    }

    FileToTree(T,file);
    fclose(file);
    return 0;
}
