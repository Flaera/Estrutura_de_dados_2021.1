#include <stdio.h>
#include <iostream>
#define DEBUG if(0)
#define LIST_FULL "List full.\n"
#define LIST_EMPTY "List empty.\n"

using namespace std;

using namespace std;

class List{
    private:
        int curr, curr_size, max_size, initMaxSize;
        int *array;
    public:
        List(int max_size2){
            curr = 0;
            curr_size = 0;
            max_size = initMaxSize = max_size2;
            array = new int[max_size];
        }
        ~List(){
            delete array;
        }
        void Insert(int element){
            if ((curr_size!=0) && (curr_size<max_size)){
                DEBUG{cout<<"AQUImax_size1: " << max_size << endl;}
                for (int j=curr_size; j>=curr; j--){
                    array[j] = array[j-1];
                }
            }
            else if (curr_size>=max_size-1){
                doubleList(element);
                return;
            }
            
            array[curr] = element;
            //curr+=1;
            curr_size+=1;        
            return;
        }

        void doubleList(int element){
            DEBUG{cout<<"AQUImax_size2: " << max_size << endl;}
            cout << LIST_FULL;
            //Copying array:
            int array_copy[max_size + 1];
            for (int i=0; i<curr; ++i){
               array_copy[i] = array[i];
            }
            array_copy[curr] = element;
            curr_size+=1;
            for (int j=curr+1; j<curr_size; ++j){
                array_copy[j] = array[j-1];
            }
            DEBUG{
                for (int l=0; l<curr_size; ++l){
                    cout << "-" << array_copy[l] << "-" << endl;
                }
            }
            //Creating new array
            delete[] array;
            max_size = 2*max_size;
            array = new int[max_size]; //It can generated out of memory
            for (int k=0; k<curr_size; ++k){
                array[k] = array_copy[k];
            }
            cout << "Array doubled." << endl << endl;
            return;
        }

        void Remove(){
            if (curr_size!=0){
                for (int i=curr; i<curr_size; ++i){
                    array[i] = array[i+1];
                }
                curr_size--;
                cout << "Element in current position was removed.\n";
            }
            else{
                cout << LIST_EMPTY;
                array[curr] = -1;
            }
        }

        //Return element on the actual position on the list
        int GetCurrentElem(){
            if(curr_size == 0)
                return -1;
            
            return array[curr];
            //DEBUG{printf("curr:%d-\n", curr);}
        }

        int SetCurrent(int index){
            if ((index<curr_size) && (index >= 0)){
                curr = index;
                cout << "Setting for current element: " << array[curr] << endl;
                return array[curr];
            }
            cout << "Index parameter most that current size list." << endl;
            return -1;
        }

        int length(){
            return curr_size;
        }

        int maxSize(){
            return max_size;
        }

        //Return actual position in the list
        int getCurrentPos(){
            return curr;
        }

        void nextPos(){
            if(curr == curr_size)
                cout << "No more positions ahead! Already at the end of the list." << endl << endl;
            else{
                curr += 1;
                cout << "Moved 1 position to the rigth." << endl << endl;
            }
        }

        void prevPos(){
            if(curr == 0)
                cout << "No more positions behind! Already at the beginning of the list." << endl << endl;
            else{
                curr -= 1;
                cout << "Moved 1 position to the left." << endl << endl;
            }
        }

        void moveToStart(){
            if (curr == 1)
                cout << "Already at the beginning of the list." << endl << endl;
            else{
                curr = 0;
                cout << "Moved to the first position on the list." << endl << endl;
            }
        }

        void moveToEnd(){
            if (curr == curr_size)
                cout << "Already at the end of the list." << endl << endl;
            else{
                curr = curr_size;
                cout << "Moved to the last occupied position on the list." << endl << endl;
            }
        }

        void clear(){
            delete array;
            curr = 0;
            curr_size = 0;
            max_size = initMaxSize;
            array = new int[initMaxSize];
        }

        int find(int value){
            for(int i = 0; i < curr_size; i++){
                if(value == array[i]){
                    cout << "The element " << value << " is in position " << i << "." << endl << endl;
                    return 0;
                }
            }
            
            cout << "The element " << value << " isn't in the list." << endl << endl;

            return 0;
        }

        void doubleListAppend(int element){
            DEBUG{cout<<"AQUImax_size2: " << max_size << endl;}
            cout << LIST_FULL;
            //Copying array:
            int array_copy[max_size + 1];
            for (int i=0; i<curr_size; ++i){
               array_copy[i] = array[i];
            }
            curr_size+=1;
            array_copy[curr_size-1] = element;
            DEBUG{
                for (int l=0; l<curr_size; ++l){
                    cout << "-" << array_copy[l] << "-" << endl;
                }
            }
            //Creating new array
            delete[] array;
            max_size = 2*max_size;
            array = new int[max_size]; //It can generated out of memory
            for (int k=0; k<curr_size; ++k){
                array[k] = array_copy[k];
            }
            cout << "Array doubled." << endl << endl;
            return;
        }

        void append(int value){
            if(curr_size == max_size){
                doubleListAppend(value);
            }else{
                array[curr_size] = value;
                curr_size += 1;
            }
        }

        void ShowAll(){
            cout << endl << "#####" << endl;
            for (int i=0; i<curr_size; ++i){
                cout << '-' << array[i] << '-' << endl;
            }
            cout << "#####" << endl << endl ;
        }
};


int ShowMenu(){
    //1 for insert
    //2 get current
    //3 set  current
    //4 for remove
    //5 show all
    //6 length
    //7 maxSize
    //10 exit
    char title[] = "List of the Numbers Integers\0"; //28
    int len = 0;
    while (title[len]!=0){len++;}
    for (int i=0; i<len; ++i){cout<<'-';}
    cout << endl;
    cout << title << endl;
    for (int j=0; j<len; ++j){cout<<'-';}
    cout << endl;
    
    cout << "1 - Insert one element in current position." << endl;
    cout << "2 - Get current element." << endl;
    cout << "3 - Set current element." << endl;
    cout << "4 - Remove element current." << endl;
    cout << "5 - Show all elements." << endl;
    cout << "6 - Show how many elements the list has at the moment." << endl;
    cout << "7 - Show the actual maximum size of the list." << endl;
    cout << "8 - Get current position in the list." << endl;
    cout << "9 - Set position to next position." << endl;
    cout << "10 - Set position to previous position." << endl;
    cout << "11 - Set position to start of the list." << endl;
    cout << "12 - Set position to the end of the list." << endl
         << "     Note that \"end of the list\" means the last position in the actual size of the list." << endl;
    cout << "13 - Erase all content from the list." << endl;
    cout << "14 - Append one element on the list." << endl;
    cout << "15 - Find one element in the list." << endl;
    cout << "16 - Exit of the program." << endl << endl;
    cout << "Digit one option: ";
    int opt;
    cin >> opt;
    getchar();
    cout << endl;
    if (opt==1){return 1;}
    else if (opt==2){return 2;}
    else if (opt==3){return 3;}
    else if (opt==4){return 4;}
    else if (opt==5){return 5;}
    else if (opt==6){return 6;}
    else if (opt==7){return 7;}
    else if (opt==8){return 8;}
    else if (opt==9){return 9;}
    else if (opt==10){return 10;}
    else if (opt==11){return 11;}
    else if (opt==12){return 12;}
    else if (opt==13){return 13;}
    else if (opt==14){return 14;}
    else if (opt==15){return 15;}
    else if (opt==16){return 16;}
    else{
        cout << "Invalid Option." << endl;
        return ShowMenu();
    }
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
        DEBUG{cout << "opt= " << opt << endl;}
        if (opt==16){return 0;}
        else if (opt==1){
            cout << "Digit one number to inserted: ";
            int element;
            cin >> element;
            getchar();     
            DEBUG{cout << "element: " << element << endl;}
            list.Insert(element);
            cout << endl;
        }
        else if (opt==2){
            int element = list.GetCurrentElem();
            if (element==-1)
                cout << LIST_EMPTY;
            else
                cout << "Current element: " << list.GetCurrentElem() << endl << endl;
            
        }
        else if (opt==3){
            cout << "Digit the index position to set: ";
            int index;
            cin >> index;
            getchar();
            list.SetCurrent(index);
            cout << endl;
        }
        else if (opt == 4)
            list.Remove();
        else if (opt == 5)
            list.ShowAll();
        else if (opt == 6)
            cout << "The list has " << list.length() << " element(s) right now." << endl << endl;
        else if (opt == 7)
            cout << "The actual maximum size of the list is " << list.maxSize() << endl << endl;
        else if (opt == 8)
            cout << "Your current position in the list is: " << list.getCurrentPos() << endl << endl;
        else if(opt == 9)
            list.nextPos();
        else if(opt == 10)
            list.prevPos();
        else if(opt == 11)
            list.moveToStart();
        else if(opt == 12)
            list.moveToEnd();
        else if(opt == 13)
            list.clear();
        else if(opt == 14){
            int value;
            cout << "Insert the value you wanna append: ";
            cin >> value;
            //getchar();
            cout << endl;
            list.append(value);
        }
        else if(opt == 15){
            int value;
            cout << "Enter the value you wanna find: ";
            cin >> value;
            cout << endl;
            list.find(value);
        }
    }

    return 0;
}