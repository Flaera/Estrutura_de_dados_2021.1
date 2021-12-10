#include <stdio.h>


int Partition(int array[], int init, int end){
    int left, right, aux, pivot;
    left = init;
    right = end;
    pivot = array[init];
    while (left<right){
        while (array[left]<=pivot){left++;}
        while (array[right]>pivot){right--;}
        if (left<right){
            aux = array[left];
            array[left] = array[right];
            array[right] = aux;
        }
    }
    array[init] = array[right];
    array[right] = pivot;
    return right;
}


void QuickSort(int array[], int init, int end){
    int pivot;
    if (end > init){
        pivot = Partition(array, init, end);
        QuickSort(array, init, pivot-1);
        QuickSort(array, pivot+1, end);
    }
}


int main(){
    int size;

    printf("Digit the lenght of vector: ");
    scanf("%d", &size);
    getchar();
    int array[size];

    printf("Digit the numbers of array: ");
    for (int i=0; i<size; ++i){
        scanf("%d", &array[i]);
        getchar();
    }
    
    QuickSort(array, 0, size);

    printf("After quick sorting:\n");
    for (int j=0; j<size; ++j){printf("%d ", array[j]);}
    printf("\n\n");

    return 0;
}
