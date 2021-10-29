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
    //if (a=='0'){printf("ZERO");}
    if (a=='1'){printf("UM");}
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


void PrintMilhar(char a){
    if (a==2){printf("MIL");}
    else if (a==3){printf("MILHÕES");}
    else if (a==4){printf("BILHÕES");}
    else if (a==5){printf("TRILHÕES");}
    else if (a==6){printf("QUATRILHÕES");}
    else if (a==7){printf("SEISTILHÕES");}
    else if (a==8){printf("SETESSENTILHÕES");}
    else if (a==9){printf("OITOSSENTILHÕES");}
    else if (a==10){printf("NOVESSENTILHÕES");}
    return;
}


int MultiSplit(int end, char vec2d[][4], int len_num, char num[]){
    int acc = len_num-1;
    int delta = 0;
    for (int i=0; i<end; ++i){
        try{
            if ((num[acc]>=48) && (num[acc]<=57)){
                vec2d[i][0] = num[acc];
                delta += 1;
                //vec2d[i][0+1] = 0;
            }
            else{throw 1;}
            if ((num[acc-1]>=48) && (num[acc-1]<=57)){
                vec2d[i][1] = num[acc-1];
                delta += 1;
                //vec2d[i][1+1] = 0;
            }
            else{throw 2;}
            if ((num[acc-2]>=48) && (num[acc-2]<=57)){
                vec2d[i][2] = num[acc-2];
                delta += 1;
                //vec2d[i][2+1] = 0;
            }
            else{throw 3;}
        }
        catch(int error){
            if (error==1){
                printf("Error space not in vector 2d-1\n");
                vec2d[i][1] = 0;
            }
            else if (error==2){
                printf("Error space not in vector 2d-2\n");
                vec2d[i][2] = 0;
            }
            else if (error==3){
                printf("Error space not in vector 2d-3\n");
                vec2d[i][3] = 0;
            }
        }
        //printf("delta:%d-i:%d-\n", delta, i);
        acc -= delta;
    }
    return 0;
}


int WriteNumberExtended(int *len, char num[]){
    int delta = 0;
    if (num[0]=='-'){
        *len -= 1;
        delta = 1;
        printf("MENOS ");
    }
    if (*len>=4){
        int end = *len/3;
        if (*len%3>0){
            end += 1;
        }
        char vec2d[end][4];
        MultiSplit(end, vec2d, *len, num);
        DEBUG{
            for (int i=0; i<end; ++i){
                printf("parts:-%s-\n", vec2d[i]);
            }
        }
        for (int j=end-1; j>=0; --j){
            int len2 = GetLenghtString(vec2d[j]);
            DEBUG{printf("len2:%d-j:%d-\n", len2, j);}
            int acc = len2-1;
            if ((len2==3)){
                PrintCent(vec2d[j][acc+delta]);
                if (vec2d[j][acc-1+delta]!='0'){printf(" E ");}
                if (vec2d[j][acc-1+delta]=='1'){
                    PrintDecimates(vec2d[j][acc-1+delta]);
                }
                else{
                    PrintDezenas(vec2d[j][acc-1+delta]);
                    if (vec2d[j][acc-1+delta]!='0'){printf(" E ");}
                    PrintUnits(vec2d[j][acc-2+delta]);
                }
            }
            else if ((len2==2) && (vec2d[j][acc]!='0')){
                if (vec2d[j][acc+delta]=='1'){
                    PrintDecimates(vec2d[j][acc+delta]);
                }
                else{
                    PrintDezenas(vec2d[j][acc+delta]);
                    printf(" E ");
                    PrintUnits(vec2d[j][acc+1+delta]);
                }
            }
            else if ((len2==1) && (vec2d[j][acc]!='0')){
                PrintUnits(vec2d[j][acc+delta]);
            }
            printf(" ");
            PrintMilhar(j+1);
            printf(" ");
            acc -= 1;
        }
    }
    else if (*len==3){
        PrintCent(num[0+delta]);
        if (num[1+delta]!='0'){printf(" E ");}
        if (num[1+delta]=='1'){
            PrintDecimates(num[2+delta]);
        }
        else{
            PrintDezenas(num[1+delta]);
            if (num[1+delta]!='0'){printf(" E ");}
            PrintUnits(num[2+delta]);
        }
    }
    else if (*len==2){
        if (num[0+delta]=='1'){
            PrintDecimates(num[1+delta]);
        }
        else{
            PrintDezenas(num[0+delta]);
            if (num[1+delta]!='0'){printf(" E ");}
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
    printf("Digite um número entre -999,999 e 999999,999999:\n");
    GetString(number);
    int *len2_p;
    int len2 = GetLenghtString(number);
    len2_p = &len2;
    DEBUG{printf("number:%s-%d-\n", number, len2);}

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