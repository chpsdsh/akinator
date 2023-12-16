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

void getAnswer(char *str){
    int ind = 0, ressize = 0;
    char *res = (char*) malloc(sizeof(char));

    while(str[ind] != '?')
        ind++;

    for (int i = ind-1; str[i] != ' '; i--){
        res[ressize++] = str[i];
        realloc(res,ressize*sizeof(char));
        res[ressize] = '\0';
    }
    printf("It is");

    for(int i = strlen(res); i >= 0; i--)
        printf("%c",res[i]);

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
void Game(TREE *T){
    int game = 1;
    char answer[4];
    puts("Answer only yes/no");
    while(game){
        printf("%s\n",T->value);
        puts("Your answer:");
        scanf("%s",&answer);
        if(strcmp(answer,"yes")==0){
            if(T->left)
                T = T->left;
            else{
                getAnswer(T->value);
                exit(0);
            }

        }
        else if(strcmp(answer,"no") == 0){
            if(T->right)
                T = T->right;
            else

        }
    }
}

void FileToTree(TREE *T, FILE *file){
    char buffer[256];
    fgets(buffer,sizeof(buffer),file);

    T = create(getQuestion(buffer), getnum(buffer));
    while(fgets(buffer,sizeof(buffer),file) != NULL){
        add(T, getQuestion(buffer), getnum(buffer));
    }
    printf("%s",T->left->value);
    Game(T);
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
