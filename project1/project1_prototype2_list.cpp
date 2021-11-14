//#include <stdio.h>
#include <iostream>
#define DEBUG if(1)
#define LIST_FULL printf("List full.\n")
#define LIST_EMPTY printf("List empty.\n")

using namespace std;

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

        void Remove(){
            if (curr_size!=0){
                int after_elements[curr_size];
                for (int i=curr+1; i<curr_size-curr; ++i){
                    after_elements[i] = array[i+1]; 
                }
                for (int j=curr; j<curr_size-curr+1; ++j){
                    array[j] = after_elements[j+1];
                }
                --curr_size;
                --curr;
            }
            else{
                array[curr] = -1;
            }
        }

        int GetCurrent(){
            //DEBUG{printf("curr:%d-\n", curr);}
            return array[curr-1];
        }

        int SetCurrent(int index){
            if (index<curr_size){
                curr = index;
                return array[curr];
            }
            printf("Index parameter most that current size list.\n");
            return -1;
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
    int len;
    scanf("%d", &len);
    getchar();
    List list(len);

    list.Insert(11);
    list.Insert(456);
    list.Insert(2);
    printf("GetCurrent:%d\n", list.GetCurrent());
    printf("SetCurrent:%d\n", list.SetCurrent(0));
    list.Remove();

    list.ShowAll();


    return 0;
}
