#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


void Remove(int arvore[][10], int element, int* numNo){
    for (int i=0; i<*numNo; ++i){

        if (arvore[1][i]==element){
            i+=1;
            *numNo -= 1;
        }
    }
}


int main()
{
	int arvore[2][10];
	int i,indPai, elemento, pai, numNo;

        printf("\n\n Forneça um nó raiz para a árvore: \n ");
	arvore[0][0] = -1;
	scanf("%d",&arvore[1][0]); 
	numNo = 1;
       printf("\n Forneça os elementos e os pais dos nós da árvore: ");
        printf("\n um elemento com pai -1 encerra a insersão de nós na árvore ");
        printf("\n Forneça um valor para ser inserido na árvore:  ");
	scanf("%d",&elemento); 
        printf("\n Forneça o valor para o pai desse valor: ");
	scanf("%d",&pai); 
	pai = 0;
	while(pai != -1){
		indPai = -1;

		for(i = 0; i < numNo; i++){
			if (arvore[1][i] == pai)
				indPai = i;
		}
		if (indPai < 0 ){
			printf("\n erro pai não encontrado");
		}else {
			if (numNo == 10){
				printf("erro estrutura cheia");
			}else{
				arvore[0][numNo]= indPai;
				arvore[1][numNo]= elemento;
				numNo = numNo + 1;
			}
		}
    	printf("\n Forneça um valor para ser inserido na árvore:  ");
		scanf("%d",&elemento); 
        	printf("\n Forneça o valor para o pai desse valor: ");
		scanf("%d",&pai);
	}
    
    char choice;
    cout << "Quer remover algum elemento (S/n): ";
    cin >> choice;
    if ((choice=='S') || (choice=='s')){
        int element;
        cin >> element;
        Remove(arvore, element, &numNo);
    }

        printf("\n\n estrutura arvore: \n\n");
	for (i=0; i < numNo; i++)
		printf(" tree[0][%d]= %d, ", i, arvore[0][i]);
        printf("\n");
	for (i=0; i < numNo; i++)
		printf(" tree[1][%d]= %d, ", i, arvore[1][i]);

        printf("\n\n Fim ");
    return 0;
}
