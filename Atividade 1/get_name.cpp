#include <stdio.h>
#include <iostream>
#define DEBUG if(0)
using namespace std;


char GetString(char string[]){
    scanf("%[^\n]", string);
    getchar();
    char initial = string[0];
    DEBUG{printf("char_initial-%c-\n", initial);}
    return initial;
}


void GetName(int len, char string[]){
    char initial = GetString(string);
    while ((initial < 65) || (initial > 90)){
        printf("Nome deve começar apenas com letra Maiúscula.\n");
        initial = GetString(string);
        DEBUG{printf("char_initial2-%d-\n", initial);}
    }
    return;
}


int main(){

    int len = 256;
    char name[len];
    for (int i=0; i<len; ++i){
        name[i]=32;
    }

    GetName(len, name);

    printf("Name: -%s-\n", name);

    return 0;
}