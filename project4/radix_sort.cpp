#include <iostream>
#include <stdio.h>
#include <time.h>
#define DEBUG if(1)

using namespace std;


int getMax(int array[], int size){
    int maxElem = array[0];
    for (int i=1; i<size; ++i){
        if (array[i]>maxElem){maxElem = array[i];}
    }
    return maxElem;
}


void CountingSort(int array[], int size, int div, int output[]){
    int temp, acum;
    temp = acum = 0;
    int count[10] = {0};

    #define DIGIT(X) (X/div)%10

    for (int i=0; i<size; ++i){
        count[ DIGIT(array[i]) ] += 1;
    }

    for (int j=0; j<10; ++j){
        temp = count[j];
        count[j] = acum;
        acum += temp;
    }

    for (int k=0; k<size; ++k){
        output[count[DIGIT(array[k])]] = array[k];
        count[DIGIT(array[k])] += 1;
    }

    for (int l=0; l<size; ++l){
        array[l] = output[l];
    }
}


int RadixSort(int array[], int size){
    int max_elem_array = getMax(array, size);
    int output[size];

    for (int i=1; (max_elem_array/i)>0; i=i*10){
        CountingSort(array, size, i, output);
    }
    return 0;
}


int main(){
    int size;
    cout << "Enter with size of array: ";
    cin >> size;
    getchar();

    int array[size];
    cout << "Enter with " << size<<" elements in array:";
    for (int j=0; j<size; ++j){
        cin >> array[j];
        getchar();
    }

    cout << "Before sorting:" << endl;
    for (int k=0; k<size; ++k){cout << array[k] <<" ";}
    cout << endl;

    time_t time_diff, t_end, t_init;
    t_init = time(NULL);
    RadixSort(array, size);
    t_end = time(NULL);
    time_diff = difftime(t_end, t_init);
    printf("Radix sorting have delta time equal: %f.\n", (double)time_diff);

    cout << "After sorting:" << endl;
    for (int l=0; l<size; ++l){cout << array[l] <<" ";}
    cout << endl;

    return 0;
}