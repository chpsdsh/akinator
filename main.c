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


    for (int i = ind+1; i < strlen(str) && str[i] != '\n'; i++){
        res[i - ind - 1] = str[i];
        ressize++;
        realloc(res,ressize*sizeof(char));
        res[i+1] = '\0';

    }

    return res;
}

char* inttostr(int num){
    char tmp;
    char *res = (char*) malloc(sizeof(char));
    int ressize = 1;
    for(int i = 0; num!=0; i++){
        res[i] = '0' + num % 10;
        num /= 10;
        ressize++;
        realloc(res,ressize*sizeof(char));
    }

    res[ressize-1] = '\0';
    for(int i = 0; i < strlen(res)/2; i++){
        tmp = res[i];
        res[i] = res[strlen(res) - 1 - i];
        res[strlen(res) - 1 - i] = tmp;
    }

    return res;
}

void replaceString(int num, char* str, char* new_str) {

    FILE *file = fopen("data.txt","r");
    char buffer[256];
    char **arr = NULL;
    int len = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        arr = realloc(arr, (len + 1) * sizeof(char*));
        arr[len] = strdup(buffer);
        len++;
    }

    fclose(file);
    file = fopen("data.txt","w");
    for(int i = 0;i < len; i++){

        if(strstr(arr[i],str)!=0){
            fprintf(file, "%s\n",new_str);
        }
        else
            fprintf(file, "%s",arr[i]);
    }
    fclose(file);

}

char *getstring(char*str){
    int len = strlen(str)+1;

    str[len-1] = '_';
    str[len] = '\0';
    realloc(str,len*sizeof(char));
    char s;
    s = getchar();
    while(s != '\n'){
        str[len++] = s;
        str = (char*)realloc(str, sizeof(char)*(len));
        s = getchar();
    }
    str[len] = '\0';
    return str;
}

char *createans(int num, char *answer, int flag){
    char *res = inttostr(num);
    if (flag == 1){
        strcat(res,"_Is this ");
        strcat(res, answer);
        strcat(res,"?");
    }
    else if(flag == 0){
        strcat(res,"_");
        strcat(res, answer);
    }
    printf("%s",res);
    return res;
}

void Game(TREE *T){
    FILE *file = fopen("data.txt","a");
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
            else{
                printf("What did you wish for?\n");
                char wish[256];
                scanf("%s",wish);
                printf("Ask a question to differ it from other\n");
                char *new_str = inttostr(T->nmb);
                char c = getchar();
                new_str = getstring(new_str);
                replaceString(T->nmb,T->value,new_str);
                printf("%s\n",new_str);
                puts("Answer your question:");
                scanf("%s",&answer);
                if(strcmp(answer,"yes")==0){
                    //fputs(createans(T->nmb*2,wish,1),file);
                    //fputs(createans(T->nmb*2+1,T->value,0),file);
                    /*if(T->value[strlen(T->value)] != '\n')
                        fprintf(file, "%s","\n");
                    fprintf(file, "%s", createans(T->nmb*2,wish,1));
                    fprintf(file, "\n%s", createans(T->nmb*2+1,T->value,0));*/
                }
                else if (strcmp(answer,"no")==0){
                    //fputs(createans(T->nmb*2,T->value,0),file);
                    //fputs(createans(T->nmb*2+1,wish,1),file);
                    /*if(T->value[strlen(T->value)] != '\n')
                        fprintf(file, "%s","\n");
                    fprintf(file, "%s", createans(T->nmb*2,T->value,0));
                    fprintf(file, "\n%s", createans(T->nmb*2+1,wish,1));*/
                }
                fclose(file);
                exit(0);
            }

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
