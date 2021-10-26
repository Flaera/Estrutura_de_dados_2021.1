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
        printf("O nome deve começar apenas com letra Maiúscula.\n");
        initial = GetString(string);
    }
    bool invalid_upper_case = false;
    int acc = 0;
    while (string[acc]!=0){
        int acc2 = acc+1;
        while ((string[acc2]!=32) || (string[acc2]!=0)){
            if (((string[acc2]<97) || (string[acc2]>122)) && (string[acc2]!=32) && (string[acc2]!=0)){
                DEBUG{printf("str:%d-\n", string[acc2]);}
                invalid_upper_case = true;
                break;
            }
            else if (string[acc2]==32){
                acc2 += 1;
                break;
            }
            else if (string[acc2]==0){
                break;
            }
            acc2 += 1;
        }
        if (invalid_upper_case==true){
            break;
        }
        acc = acc2;
    }
    if (invalid_upper_case==true){
        printf("O nome não pode conter maiúsculas ou outros caracteres no meio de cada palavra.\n");
        GetName(len, string);
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