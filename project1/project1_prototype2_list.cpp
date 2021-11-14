#include <stdio.h>
#define DEBUG if(1)


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
                int after_elements[curr_size+1];
                for (int i=curr; i<curr_size-curr+1; ++i){
                    after_elements[i+1] = array[i]; 
                }
                array[curr] = element;
                ++curr;
                for (int j=curr; j<curr_size-curr+1; ++j){
                    array[j] = after_elements[j-1];
                }
                ++curr_size;
            }
            else{
                array[curr] = element;
                curr+=1;
                curr_size+=1;
            }
            return;          
        }

        void ShowAll(){
            printf("#####\n");
            for (int i=0; i<curr_size; ++i){
                printf("-%d-\n", array[i]);
            }
            printf("#####\n");
            return;
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