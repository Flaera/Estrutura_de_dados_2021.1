//#include <stdio.h>
#include <iostream>
#define DEBUG if(1)

using namespace std;

class List{
    private:
        int curr;
        int curr_size;
        int *array;
    public:
        List(int max_size){
            curr = 0;
            curr_size = 0;
            array = new int[max_size];
        }
        ~List(){
            delete array;
        }
        void Insert(int element){
            if (curr_size!=0){
                for (int j=curr_size; j>curr; j--){
                    array[j] = array[j-1];
                }
                
            }
            
            array[curr] = element;
            curr+=1;
            curr_size+=1;        
        }

        void ShowAll(){
            cout << "#####" << endl;
            for (int i=0; i<curr_size; ++i){
                cout << '-' << array[i] << '-' << endl;
            }
            cout << "#####" << endl;
        }
};

int main(){
    List list(10);

    list.Insert(11);
    list.Insert(456);
    list.Insert(2);

    list.ShowAll();


    return 0;
}
