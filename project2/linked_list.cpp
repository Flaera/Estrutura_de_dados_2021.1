#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define DEBUG if(0)

using namespace std;

template <typename T> class List{
private:
    /* data */
public:
    //List();
    //~List();

    virtual void arrayDoubled() = 0;

    virtual void insert(const T& element) = 0;
    /*
    Estas funções estão comentadas pois não sei se ainda serão utilizadas
    e funções virtuais tem de ser implementadas nas classes derivadas,
    desse modo, como não sei se ainda serão utilizadas eu não implementei
    virtual void doubleList(const T& element) = 0;
    virtual int maxSize() = 0;
    */
    virtual void remove() = 0;

    virtual void getCurrentElem() = 0;

    virtual void setCurrent(const int element) = 0;

    virtual int length() = 0;

    virtual T getCurrentPos() = 0;

    virtual bool nextPos() = 0;

    virtual bool prevPos() = 0;

    virtual void moveToStart() = 0;

    virtual void moveToEnd() = 0;

    virtual void clear() = 0;

    virtual bool find(const T& element) = 0;

    virtual void append(const T& element) = 0;
};

// Singly linked list node
template <typename E> class Link {
    public:
        E element; // Value for this node
        Link *next; // Pointer to next node in list
        // Constructors
        Link(const E& elemval, Link* nextval =NULL)
            { element = elemval; next = nextval; }
        Link(Link* nextval =NULL) { next = nextval; }
};

template <typename T> class LinkedList : public List<T>{
    private:
        Link<T>* head;
        Link<T>* tail;
        Link<T>* curr;
        int count;

        void init(){
            curr = tail = head = new Link<T>;
            count = 0;
        }

    public:
        void clear(){
            while (head != NULL){
                curr = head;
                head = head -> next;
                delete curr;
            }
            count=0;
        }
        LinkedList(int size){
            int max_size = size;
            init();
        }
        ~LinkedList(){ 
            clear();
        }

        void arrayDoubled(){
            if (count==max_size){cout<<"Array doubled."<<endl;}
        }

        //insert in initial
        void insert(const T& it){
            curr->next = new Link<T>(it, curr->next);
            if (tail==curr){tail = curr->next;}
            count++;
            arrayDoubled();
        }

        void append(const T& it){
            tail = tail->next = new Link<T>(it, NULL);
            count++;
            arrayDoubled();
        }

        void remove(){
            if(curr == tail){
                cout << "You are at the end of the list!! Move to previous position and remove the element." << endl;
                return;
            } 
            Link<T>* ltemp = curr -> next;
            int it = (curr->next)->element;
            if(tail == curr -> next) {
                tail = curr;
            }else{
                curr -> next = (curr -> next) -> next;
            }
            delete ltemp;
            count--;
            cout << "Element " << it << " removed.";
        }

        void moveToStart(){
            curr = head;
        }

        void moveToEnd(){
            curr = tail;
        }

        bool prevPos(){
            if(curr == head) return false;
            Link<T>* temp = head;
            while(temp -> next != curr) temp = temp -> next;
            curr = temp;
            return true;
        }

        bool nextPos(){
            if(curr != tail) {
                curr = curr -> next;
                return true;
            }
            return false;
        }

        int length(){
            cout << count << endl;
            return 0;
        }

        T getCurrentPos(){
            Link<T>* temp = head;
            int i;
            for(i = 0; curr != temp; i++)
                temp = temp -> next;
            return i;
        }

        void setCurrent(const int pos){
            curr = head;
            for(int i = 0; i < pos; i ++) curr = curr -> next;
        }

        void getCurrentElem(){
            cout << curr -> next -> element;
        }

        void showAll(){
            cout << "##########\n";
            if (count>0){
                Link<T> *tempCurr = curr;
                curr = head;
                for(int i=0; i<count; i++){
                    cout << "-" << (curr->next)->element << "-" << endl;
                    curr = curr->next;
                }
                curr = tempCurr;
            }
            cout << "##########\n";
            return;
        }

        bool find(const T& element){
            Link<T> *ltemp_curr = curr;
            for(int i = 0; i!=count; ++i ){
                curr = curr->next;
                if (element==curr->element){
                    curr = ltemp_curr;
                    return true;
                }
            }
            curr = ltemp_curr;
            return false;
        };
};


int ShowMenu(){
    char title[] = "List of the Numbers Integers\0"; //28
    int len = 0;
    while (title[len]!=0){len++;}
    for (int i=0; i<len; ++i){cout<<'-';}
    cout << endl;
    cout << title << endl;
    for (int j=0; j<len; ++j){cout<<'-';}
    cout << endl;

    cout << "Digit 1 to insert." << endl;
    cout << "Digit 2 to append." << endl;
    cout << "Digit 3 to remove." << endl;
    cout << "Digit 4 to move at start." << endl;
    cout << "Digit 5 to move at end." << endl;
    cout << "Digit 6 to advance at previous position." << endl;
    cout << "Digit 7 to advance at next position." << endl;
    cout << "Digit 8 to know lenght of list." << endl;
    cout << "Digit 9 to get current position." << endl;
    cout << "Digit 10 to set position." << endl;
    cout << "Digit 11 to get the current element." << endl;
    cout << "Digit 12 to clear list." << endl;
    cout << "Digit 13 to find one element." << endl;
    cout << "Digit 14 to show all elements." << endl;
    cout << "Digit 15 to exit the program." << endl;
    int opt;
    cin >> opt;
    getchar();
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
    else{return ShowMenu();}
}


int main (){
    int tamanho;
    cout << "Digit the lenght of list: ";
    cin >> tamanho;
    getchar();
    LinkedList<int> aLista(tamanho);
    
    while (tamanho>0){
        int opt = ShowMenu();
        if (opt==1){
            cout << "Digit one element to insert: ";
            int elem;
            cin >> elem;
            getchar();
            aLista.insert(elem);
            cout << "Element " << elem << " inserted." << endl;
        }
        else if (opt==2){
            cout << "Digit one element to append: ";
            int elem;
            cin >> elem;
            getchar();
            aLista.append(elem);
            cout << "Element " << elem << " appended." << endl;
        }
        else if (opt==3){
            aLista.remove();
            cout << endl;
        }
        else if (opt==4){
            aLista.moveToStart();
            cout << "Moved to start of list" << endl;
        }
        else if (opt==5){
            aLista.moveToEnd();
            cout << "Moved to end of list" << endl;
        }
        else if (opt==6){
            bool status = aLista.prevPos();
            if (status==true){cout << "Moved to previous position." << endl;}
            else{cout<<"Already in initial position."<<endl;}
        }
        else if (opt==7){
            bool status = aLista.nextPos();
            if (status==true){cout << "Moved to next position." << endl;}
            else{cout<<"Already in final position."<<endl;}
        }
        else if (opt==8){
            cout << "The current lenght is ";
            aLista.length();
        }
        else if (opt==9){
            cout << "The current position is ";
            cout << aLista.getCurrentPos();
            cout << endl;
        }
        else if (opt==10){
            cout << "Digit one position " << endl;
            int pos;
            cin >> pos;
            getchar();
            aLista.setCurrent(pos);
        }
        else if (opt==11){
            cout << "The current element is ";
            aLista.getCurrentElem();
            cout << endl;
        }
        else if (opt==12){
            aLista.clear();
            cout << "The list was clear." << endl;
        }
        else if (opt==13){
            int elem;
            cout << "Digit one element to be finded: ";
            cin >> elem;
            getchar();
            if (aLista.find(elem)==true) {cout << "Element " << elem << " finded." << endl;}
            else{cout << "Element " << elem << " not found." << endl;}
        }
        else if (opt==14){
            aLista.showAll();
        }
        else if (opt==15) {return 0;}
        //system("@clear||cls");
    }
    // aLista.length();
    // aLista.insert(10);
    // aLista.length();
    // cout << aLista.find(0) << endl;

    return 0;
}