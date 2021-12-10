#include <iostream>
#include <stdio.h>

using namespace std;


void InsertSort(int vetor[], int size){
	int j = size;
	int aux;
    for (int k = 0; k < 4; k++) {
		j = k + 1;
        	while ((vetor[j]<vetor[j-1]) && (j<=5) && (j-1>=0)){
            		printf("\n[%d] = %d e [%d] = %d, ", k, vetor[k], j, vetor[j]);

            		if (vetor[j] < vetor[j-1]) {
                		aux          = vetor[j];
                		vetor[j]     = vetor[j-1];
                		vetor[j-1]   = aux;
            		}
            		j = j - 1;
        	}
    	}
}


int main(){
	int size = 5;
    int vec[size] = {10,2,3,98,131};
    InsertSort(vec, size);
	cout << endl;
    for (int i=0; i<size; ++i){
        cout << vec[i] << " ";
    }
    cout << endl;
}
