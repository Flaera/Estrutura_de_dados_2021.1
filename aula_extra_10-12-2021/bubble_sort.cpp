

void BubbleSort(int vetor[])
for (k = 0; k < 4; k++) {
        	for (j = k+1; j < 5; j++) {
            		printf("\n[%d] = %d e [%d] = %d, ", k, vetor[k], j, vetor[j]);

            		if (vetor[j] > vetor[k]) {
                		aux          = vetor[j];
                		vetor[j]     = vetor[k];
                		vetor[k] = aux;
            		}
        	}
    	}