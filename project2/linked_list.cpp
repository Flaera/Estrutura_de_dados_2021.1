#include <iostream>


using namespace std;

template <typename T> class List{
private:
    /* data */
public:
    //List();
    //~List();

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

    virtual void nextPos() = 0;

    virtual void prevPos() = 0;

    virtual void moveToStart() = 0;

    virtual void moveToEnd() = 0;

    virtual void clear() = 0;

    virtual void find(const T& element) = 0;

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

    void clear(){
        while (head != NULL){
            curr = head;
            head = head -> next;
            delete curr;
        }
    }

    public:
        LinkedList(int size){
            init();
        }
        ~LinkedList(){ 
            clear();
        }

        void insert(const T& it){
            curr -> next = new Link<T>(it, curr -> next);
            if(tail == curr) tail = curr -> next;
            count++;
        }

        void append(const T& it){
            tail = tail -> next = new Link<T>(it, NULL);
            count++;
        }

        void remove(){
            T it = curr -> next -> element;
            Link<T>* ltemp = curr -> next;
            if(tail == curr -> next) tail = curr;
            curr -> next = curr -> next -> next;
            delete ltemp;
            count--;
            cout << it;

        }

        void moveToStart(){
            curr = head;
        }

        void moveToEnd(){
            curr = tail;
        }

        void prevPos(){
            if(curr == head) return;
            Link<T>* temp = head;
            while(temp -> next != curr) temp = temp -> next;
            curr = temp;
        }

        void nextPos(){
            if(curr != tail) curr = curr -> next;
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

        void find(const T& element){
            //for(int i = 0 )
        };
};

int main (){
    int tamanho = 0;
    LinkedList<int> aLista(tamanho);

    aLista.length();
    aLista.insert(10);
    aLista.length();

    return 0;
}