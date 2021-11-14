#include <stdio.h>
#define STACK_EMPTY printf("Stack empty!\n")
#define STACK_FULL printf("Stack full!\n")
#define DEBUG if(1)

using namespace std;


class Stack{
    private:
        int *vector;
        int max_len;
        int top;
    public:
        Stack(int len){
            max_len = len;
            vector = new int[max_len];
            top = -1;
        }
        ~Stack(){
            delete vector;
        }
        void Insert(int element){
            if (top==max_len){STACK_FULL;}
            else{
                ++top;
                vector[top] = element;
            }
            return;
        }
        void Remove(){
            if (top==-1){STACK_EMPTY;}
            else{
                --top;
            }
            return;
        }
        void ShowAll(){
            if (top==-1){STACK_EMPTY;}
            else{
                for (int i=0; i<=top; ++i){
                    printf("-%d-\n", vector[i]);
                }
            }
            return;
        }
        bool IsIntoStack(int element){
            if (top==-1){STACK_EMPTY;}
            else{
                for (int i=0; i<max_len; ++i){
                    if (vector[i] == element){return true;}
                }
            }
            return false;
        }
        int GetTop(){
            if (top!=-1)
            {
                return vector[top];
            }
            else{STACK_EMPTY;}
            return -1;
        }
        bool IsEmpty(){
            if (top==-1){return true;}
            else{return false;}
        }
};


void ShowMenu(){
    printf("Choice one option below:\n");
    printf("1 - Insert element.\n");
    printf("2 - Delete element\n");
    printf("3 - \n");
}


int main(){
    int len;
    bool exit = false;
    while (exit==false){
        scanf("%d", &len);
        getchar();
        Stack stack(len);
        ShowMenu();
    }


    return 0;
}