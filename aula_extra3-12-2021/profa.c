#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1


typedef struct{
    int elemento;
} Elem;


typedef struct {
    Elem elemento;
} No;


typedef struct{
    No *raiz;
    int *esquerda;
    int *direita;
} ArvoreBinaria;


int CriaArvoreBinaria(ArvoreBinaria **a){
    *a = (ArvoreBinaria*)malloc(sizeof(ArvoreBinaria));
	if(*a == NULL){
		return 1;
	} else{
		return 0;
	}
}


int InsereNaoOrdenada(ArvoreBinaria *a, int novo_elemento){
	No *novo;
	if ((novo = malloc(sizeof(No))) == NULL)
		return FALSE;
	novo->elemento = novo_elemento;
	if (a->raiz.elemento != NULL) && (novo_elemento > a->raiz.elemento) {
		novo->direita = NULL;
		novo->esquerda = a->raiz;
	} else {
		novo->direita = a->raiz;
		novo->esquerda = NULL;		
	}
	return TRUE;
}

void MostraArvoreBinaria(No *a){ //aqui antes era do tipo ArvoreBinaria
	if (a == NULL)
		printf("()");
	else{
		printf("(");
		MostrarArvoreBinaria(a->esquerda)
    }
}

void MostraArvoreBinaria(ArvoreBinaria *a){
	if (a == NULL)
		printf("()");
	else{
		printf("(");
		MostrarArvoreBinaria(a->esquerda);
		printf(",%d, ", a->raiz);
		MostrarArvoreBinaria(a->direita);
		printf(")");
	} //novo->elemento = novo_elemento;
}

int main(){
    No *arvore;
	
	if (CriaArvoreBinaria(&arvore)==0){
		printf("Erro árvore não foi criada");
	} else {
			InsereNaoOrdenada(arvore,10);
			InsereNaoOrdenada(arvore,4);
			InsereNaoOrdenada(arvore,1);
			InsereNaoOrdenada(arvore,5);
			MostraArvoreBinaria(arvore);
		}	

	return 0;
}