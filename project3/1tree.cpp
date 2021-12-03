#include <iostream>
#define DEBUG if(0)

using namespace std;

/*  Esse código creio que não precisaremos mais
    Mas não exclui só por não ter certeza
    se vamos ou não usar ainda.
    
template <typename N> class CreateNode{
    public:
        *left;
        *right;
        N data[2];
        CreateNode(N element){
            char name_city[256];
            int positions[2];
            data[0] = name_city[256];
            data[1] = positions[2];
            cout << "Digit the name of city:\n";
            cin >> name_city;
            cout << "Digit the positions in x and y of this city:" << endl;
            cin >> positions[0];
            cin >> positions[1];
            left = NULL;
            right = NULL;
        };
};*/

template <typename E> class Link {
    public:
        E element; // Value for this node
        Link *next; // Pointer to next node in list
        // Constructors
        Link(const E& elemval, Link* nextval =NULL)
            { element = elemval; next = nextval; }
        Link(Link* nextval =NULL) { next = nextval; }
};

template <typename T> class nodeTree{
    private:
        nodeTree<T>* root;  
        string name_city;   
        int position[2];    //x and y coordinates of the city
        nodeTree<T>* left;
        nodeTree<T>* right;
    public:
        nodeTree(string city, int posX, int posY){  //constructor with 3 parameters
            name_city = city;
            position[0] = posX;
            position[1] = posY;
            left = NULL;
            right = NULL;
            cout << "Node root created. Tree created." << endl;
        };

        void insert(){
            string city;
            int posX, posY;
            cout << "Enter the name of the city: ";
            cin >> city;
            cout << "Enter the x coordinate of the city: ";
            cin >> posX;
            cout << "Enter the y coordinate of the city: ";
            cin >> posY;
            if (root->left == NULL){
                root->left = new nodeTree<T>(city, posX, posY);
                return;
            }
            else if (root->right==NULL){
                root->right = new nodeTree<T>(city, posX, posY);
                return;
            }
            //insert(root->left); // to left
            //insert(root->right); // to right
            return;
        };
};


void ShowMenu(){
    cout << "Insert city." << endl;
    cout << "Remove city by name." << endl;
    cout << "Remove city by coordinate." << endl;
    cout << "Search city by name." << endl;
    cout << "Search city by coordinate." << endl;
    cout << "Search by distance although of one point (x,y)." << endl;
    return;
}


int main(){

    nodeTree<int> arvore("Rio", 2, 3);

    int opt = 0;
    while (opt!=9){
        ShowMenu();
        cout << "Digit one option in list:" << endl;
        cin >> opt;
        if (opt==1){
            arvore.insert();
        }
    }

    return 0;
}