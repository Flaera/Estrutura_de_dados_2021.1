#include <stdio.h>
#include <iostream>
#include <math.h>
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


void PrintUnits(char a){
    if (a=='0'){printf("ZERO");}
    else if (a=='1'){printf("UM");}
    else if (a=='2'){printf("DOIS");}
    else if (a=='3'){printf("TRÊS");}
    else if (a=='4'){printf("QUATRO");}
    else if (a=='5'){printf("CINCO");}
    else if (a=='6'){printf("SEIS");}
    else if (a=='7'){printf("SETE");}
    else if (a=='8'){printf("OITO");}
    else if (a=='9'){printf("NOVE");}
    return;
}


void PrintDecimates(char a){
    if (a=='1'){printf("ONZE");}
    else if (a=='2'){printf("DOZE");}
    else if (a=='3'){printf("TREZE");}
    else if (a=='4'){printf("QUATORZE");}
    else if (a=='5'){printf("QUINZE");}
    else if (a=='7'){printf("DEZESSEIS");}
    else if (a=='7'){printf("DEZESSETE");}
    else if (a=='8'){printf("DEZEOITO");}
    else if (a=='9'){printf("DEZENOVE");}
    return;
}


void PrintDezenas(char a){
    if (a=='1'){printf("DEZ");}
    else if (a=='2'){printf("VINTE");}
    else if (a=='3'){printf("TRINTA");}
    else if (a=='4'){printf("QUARENTA");}
    else if (a=='5'){printf("CINQUENTA");}
    else if (a=='6'){printf("SESSENTA");}
    else if (a=='7'){printf("SETENTA");}
    else if (a=='8'){printf("OITENTA");}
    else if (a=='9'){printf("NOVENTA");}
    return;
}


void PrintCent(char a){
    if (a=='1'){printf("CEMTO");}
    else if (a=='2'){printf("DUZENTOS");}
    else if (a=='3'){printf("TREZENTOS");}
    else if (a=='4'){printf("QUATROCENTOS");}
    else if (a=='5'){printf("QUIENTOS");}
    else if (a=='6'){printf("SEISSENTOS");}
    else if (a=='7'){printf("SETESSENTOS");}
    else if (a=='8'){printf("OITOSSENTOS");}
    else if (a=='9'){printf("NOVESSENTOS");}
    return;
}


int WriteNumberExtended(int *len, char num[]){
    int delta = 0;
    if (num[0]=='-'){
        *len -= 1;
        delta = 1;
        printf("MENOS ");
    }
    if (*len==3){
        PrintCent(num[0+delta]);
        printf(" E ");
        if (num[1+delta]=='1'){
            PrintDecimates(num[2+delta]);
        }
        else{
            PrintDezenas(num[1+delta]);
            printf(" E ");
            PrintUnits(num[2+delta]);
        }
    }
    else if (*len==2){
        if (num[0+delta]=='1'){
            PrintDecimates(num[1+delta]);
        }
        else{
            PrintDezenas(num[0+delta]);
            printf(" E ");
            PrintUnits(num[1+delta]);
        }
    }
    else if (*len==1){
        PrintUnits(num[0]);
    }
    return 0;
}


void Split(int len, char num[], char string1[], char string2[]){
    int acc = 0;
    bool changed = false;
    while ((num[acc]!=0)){
        if (((num[acc]!=44) && (num[acc]!=46)) && (changed==false)){
            string1[acc] = num[acc];
            acc+=1;
        }
        else{
            changed = true;
            string1[acc]=0;
            acc += 1;
        }
    }
    int len_str1 = GetLenghtString(string1);
    int delta_len_loop = len-len_str1;
    for (int i=0; i<delta_len_loop; ++i){
        if (i<len){
            string2[i] = num[len_str1+i+1];
        }
    }
    return;
}


void WriteNumberRealExtended(int *len, char num[]){
    int len2 = 256;
    char string1[len2];
    char string2[len2];
    Split(*len, num, string1, string2);
    DEBUG{printf("str1=%s;str2:%s.", string1, string2);}
    int len1_p;
    len1_p = GetLenghtString(string1);
    WriteNumberExtended(&len1_p, string1);
    printf(", ");
    int len2_p;
    len2_p = GetLenghtString(string2);
    if (IsNatural(&len2_p, string2)==true){
        WriteNumberExtended(&len2_p, string2);
    }
    return;
}


int main(){
    int len = 256;
    int *len_p;
    len_p = &len;
    char number[len];

    InitVector(len_p, number);
    printf("Digite um número até 999,99:\n");
    GetString(number);
    int *len2_p;
    int len2 = GetLenghtString(number);
    len2_p = &len2;
    DEBUG{printf("number:%s-\n", number);}

    bool is_real = IsReal(len2_p, number);
    if (is_real==true){
        WriteNumberRealExtended(len2_p, number);
        printf("\n");
    }
    else{
        bool is_nat = IsNatural(len2_p, number);
        if (is_nat==true){
            //printf("Número natural!\n");
            WriteNumberExtended(len2_p, number);
            printf("\n");
            return 0;
        }

        bool is_int = IsInteger(len2_p, number);
        if (is_int==true){
            WriteNumberExtended(len2_p, number);
            printf("\n");
            return 0;
        }

        printf("Número inválido!\n");
    }
    return 0;
}