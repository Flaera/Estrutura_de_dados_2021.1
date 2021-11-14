//#include <stdio.h>
#include <iostream>
#define DEBUG if(1)
#define LIST_FULL "List full.\n"
#define LIST_EMPTY "List empty.\n"

using namespace std;

using namespace std;

class List{
    private:
        int curr;
        int curr_size;
        int *array;
        int max_size;
    public:
        List(int max_size){
            curr = 0;
            curr_size = 0;
            max_size = max_size;
            array = new int[max_size];
        }
        ~List(){
            delete array;
        }
        void Insert(int element){
            if ((curr_size!=0) && (curr_size<max_size)){
                for (int j=curr_size; j>curr; j--){
                    array[j] = array[j-1];
                }
            }
            //else if (curr_size<max_size){
                //
            //}
            
            array[curr] = element;
            //curr+=1;
            curr_size+=1;        
        }

        void Remove(){
            if (curr_size!=0){
                for (int i=curr; i<curr_size; ++i){
                    array[i] = array[i+1];
                }
                curr_size--;
            }
            else{
                cout << LIST_EMPTY;
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
            cout << "Index parameter most that current size list.\n";
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
    cin >> len;
    List list(len);

    list.Insert(11);
    list.Insert(456);
    list.Insert(2);
    list.Insert(4);
    cout << "GetCurrent: " << list.GetCurrent() << endl;
    cout << "SetCurrent: " << list.SetCurrent(1) << endl;
    list.Remove();
    list.Remove();
    list.Remove();

    list.ShowAll();


    return 0;
}
