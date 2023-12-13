#include <stdio.h>
#include "tree.h"
#include <malloc.h>


int main() {
    FILE *file = fopen("data.txt","r");
    TREE *T = Create(0);
    if (file == NULL) {
        puts("ERROR");
        return 0;
    }
    char buffer[256];
    while(fgets(buffer,sizeof(buffer),file) != NULL){

    }
    return 0;
}
