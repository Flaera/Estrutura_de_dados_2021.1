#include <stdio.h>
#include <iostream>
#define DEBUG if(0)
using namespace std;


char GetString(char string[]){
    scanf("%[^\n]", string);
    getchar();
    char initial = string[0];
    return initial;
}


void InitVector(int *len, char vector[]){
    for (int i=0; i<*len; ++i)
    {
        vector[i]=32;
    }
    return;
}


bool IsNatural(int *len, char num_str[]){
    for (int i=0; i<*len; ++i){
        DEBUG{printf("i:%d; num_str:%d\n", i, num_str[i]);}
        if ((num_str[i]<48) || (num_str[i]>57)){
            return false;
        }
    }
    return true;
}


bool IsInteger(int *len, char num_str[]){
    if (num_str[0]==45){
        for (int i=1; i<*len; ++i){
            if ((num_str[i]<48) || (num_str[i]>57)){
                return false;
            }
        }
    }
    return true;
}


bool IsReal(int *len, char num_str[]){
    int acc = 0;
    for (int i=0; i<*len; ++i){
        if ((num_str[i]==44) || (num_str[i]==46)){
            acc += 1;
        }
    }
    if (acc==1){return true;}
    else{return false;}
}


int GetLenghtString(char vector[]){
    int acc = 0;
    while (vector[acc] != 0){
        acc += 1;
    }
    return acc;
}


int main(){
    int len = 256;
    int *len_p;
    len_p = &len;
    char number[len];

    InitVector(len_p, number);
    GetString(number);
    int *len2_p;
    int len2 = GetLenghtString(number);
    len2_p = &len2;
    DEBUG{printf("number:%s-\n", number);}

    bool is_real = IsReal(len2_p, number);
    if (is_real==true){
        printf("Número real!\n");
    }
    else{
        bool is_nat = IsNatural(len2_p, number);
        if (is_nat==true){
            printf("Número natural!\n");
            return 0;
        }

        bool is_int = IsInteger(len2_p, number);
        if (is_int==true){
            printf("Número inteiro!\n");
            return 0;
        }

        printf("Número inválido!\n");
    }
    return 0;
}