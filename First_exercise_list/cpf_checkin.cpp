#include <stdio.h>
#include <iostream>
#define DEBUG if(0)
#define CPF_INVALID if(1){printf("Entrada inválida.\n");}

using namespace std;


bool CPFInput(char vec_cpf[]){
    printf("Digite seu cpf sem pontos e/ou traços (Somente números):\n");
    scanf("%s", vec_cpf);
    getchar();

    int acc = 0;
    while (vec_cpf[acc]!=0){
        if (acc >= 11){
            CPF_INVALID;
            printf("Aviso: mais de 11 números e/ou letras.\n");
            return false;
        }
        acc += 1;
    }
    if (acc<10){
        CPF_INVALID;
        printf("Aviso: menos de 11 números.\n");
        return false;
    }

    bool is_equal = true;
    for (int i=0; i<10; ++i){
        if (vec_cpf[i]!=vec_cpf[i+1]){
            is_equal = false;
        }
    }
    if (is_equal==true){
        CPF_INVALID;
        printf("Cpf formado por uma repetição de um só digito (Formato 111.111.111-11).\n");
        return false;
    }

    DEBUG{printf("cpf:%s-\n", vec_cpf);}
    return true;
}


int CharToInt(char a){
    if (a==48){return 0;}
    else if (a==49){return 1;}
    else if (a==50){return 2;}
    else if (a==51){return 3;}
    else if (a==52){return 4;}
    else if (a==53){return 5;}
    else if (a==54){return 6;}
    else if (a==55){return 7;}
    else if (a==56){return 8;}
    else if (a==57){return 9;}
    return -1;
}


void PrintResult(bool dv1, bool dv2){
    if ((dv1==true) && (dv2==true)){
        printf("Cpf válido.\n");
    }
    else{
        printf("Cpf inválido.\n");
    }
    return;
}


int main(){
    char cpf[11];
    bool cpf_input = CPFInput(cpf);
    while (cpf_input==false){
        cpf_input = CPFInput(cpf);
    }
    
    bool dv1, dv2;
    dv1 = dv2 = false;

    int sum = 0;
    for (int i=0; i<9; ++i){
        sum += (CharToInt(cpf[i])*(10-i));
    }
    DEBUG{printf("sum1:%d-\n", sum);}
    int rest = 11-(sum%11);
    if (rest<10){
        if (CharToInt(cpf[9])==rest){
            dv1 = true;
        }
        else{
            dv1 = false;
        }
    }
    else if (rest>=10){
        if (CharToInt(cpf[9])==0){
            dv1 = true;
        }
        else{
            dv1 = false;
        }
    }

    int sum2 = 0;
    for (int i=0; i<10; ++i){
        sum2 += (CharToInt(cpf[i])*(11-i));
    }
    DEBUG{printf("sum2:%d-\n", sum2);}
    int rest2 = 11-(sum2%11);
    if (rest2<10){
        if (CharToInt(cpf[10])==rest){
            dv2 = true;
        }
        else{
            dv2 = false;
        }
    }
    else if (rest2>=10){
        if (CharToInt(cpf[10])==0){
            dv2 = true;
        }
        else{
            dv2 = false;
        }
    }

    DEBUG{printf("dvs:%i-%i-\n", dv1, dv2);}
    PrintResult(dv1, dv2);

    return 0;
}