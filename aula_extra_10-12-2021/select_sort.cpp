for (k = 0; k < 4; k++) {
    		menor = k;
        	for(j = k+1; j < 5; j++){
            		printf("\n[%d] = %d e [%d] = %d, ", k, vetor[k], j, vetor[j]);

            		if (vetor[menor] > vetor[j]) {
            			menor = j;
            		}
        	}
           	aux          	= vetor[menor];
           	vetor[menor]  	= vetor[k];
           	vetor[k]   	= aux;

    	}