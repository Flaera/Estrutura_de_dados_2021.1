#include <stdio.h>
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
        int max_size;
        int *array;
    public:
        List(int max_size2){
            curr = 0;
            curr_size = 0;
            max_size = max_size2;
            array = new int[max_size];
        }
        ~List(){
            delete array;
        }
        void Insert(int element){
            if ((curr_size!=0) && (curr_size<max_size)){
                DEBUG{cout<<"AQUImax_size1: " << max_size << endl;}
                for (int j=curr_size; j>curr; j--){
                    array[j] = array[j-1];
                }
            }
            else if (curr_size>=max_size-1){
                DEBUG{cout<<"AQUImax_size2: " << max_size << endl;}
                cout << LIST_FULL;
                array = new int[2*max_size]; //It can generated out of memory
                for (int j=curr_size; j>curr; j--){
                    array[j] = array[j-1];
                }
            }
            
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
                cout << "Element in current position was removed\n";
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
                cout << "Setting for current element: " << array[curr] << endl;
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


int ShowMenu(){
    //1 for insert
    //2 get current
    //3 set  current
    //4 for remove
    //5 exit
    cout << "1 - insert one element in current position.\n";
    cout << "2 - get current element.\n";
    cout << "3 - set current element.\n";
    cout << "4 - remove element current.\n";
    cout << "5 - show all elements.\n";
    cout << "6 - exit.\n";
    cout << "Digit one option:\n";
    int opt;
    cin >> opt;
    getchar();
    if (opt==1){return 1;}
    else if (opt==2){return 2;}
    else if (opt==3){return 3;}
    else if (opt==4){return 4;}
    else if (opt==5){return 5;}
    else if (opt==6){return 6;}
    else{return ShowMenu();}
}


int main(){
    bool exit = false;
    int len;
    cout << "Digit lenght of array:\n";
    cin >> len;
    getchar();
    List list(len);
    while (exit==false){
        int opt = ShowMenu();
        if (opt==6){return 0;}
        else if (opt==1){
            cout << "Digit one number to inserted:\n";
            int element;
            cin >> element;
            getchar();
            list.Insert(element);
        }
        else if (opt==2){
            int element = list.GetCurrent();
            if (element==-1){
                cout << LIST_EMPTY;
            }
            else{
                cout << "Current element: " << list.GetCurrent() << endl;
            }
        }
        else if (opt==3){
            cout << "Digit the index position to set:\n";
            int index;
            cin >> index;
            getchar();
            list.SetCurrent(index);
        }
        else if (opt==4){
            list.Remove();
        }
        else if (opt==5){
            list.ShowAll();
        }
    }

    return 0;
}
