#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DEBUG if(1)

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
    private:
        Link<E> *left;
        Link<E> *right; // Pointer to next node in list
    public:
        // Constructors
        Link(string city, int posX, int posY){
            string name_city = city;
            int positions[2];
            positions[0] = posX;
            positions[1] = posY;
            left = NULL;
            right = NULL;
            cout << "Node created." << endl;
        }
        string getNameCity(){return name_city;}
        int getPosX(){return positions[0];}
        int getPosY(){return positions[1];}
        Link<E> getLeft(){return left;}
        LINK<E> getRight(){return right;}
        void setLeftNode(Link *left2){left = left2;}
        void setRightNode(Link *right2){right = right2;}
};

template <typename T> class nodeTree{
    //private:
        
        
    public:
        Link<T> *root;    
        nodeTree(string city, int posX, int posY){  //constructor with 3 parameters
            root = NULL;
            cout << "Node root created." << endl;
        };

        void insert(){
            char city[256];
            int posX, posY;
            cout << "Enter the name of the city: ";
            scanf("%[^\n]", city);
            getchar();
            cout << "Enter the x coordinate of the city: ";
            cin >> posX;
            cout << "Enter the y coordinate of the city: ";
            cin >> posY;

            if (root==NULL){
                root = new Link<T>(city, posX, posY);
            }
            else{
                insertAux(root, city, posX, posY);
            }
            return;
        };


        void insertAux(Link<T> root, string name_city, int posx, int posy){
            if (root->getLeft()!=NULL){
                Link<T> new_node = new Link<T>(city, posx, posy);
                root->setLeftNode(new_node);
            }
            else{
                insertAux(root->getLeft(), name_city, posx, posy);
            }
            if (root->getRight()!=NULL){
                Link<T> new_node = new Link<T>(city, posx, posy);
                root->setRightNode(new_node);
            }
            else{
                insertAux(root->getRight(), name_city, posx, posy);
            }
        }


        Link<T> getRoot(){
            return root;
        }


        void ShowAllInOrder(Link<T> *root){
            if (root!=NULL){
                ShowAllInOrder(root->getLeft());
                cout << "-" << root->getNameCity() << "-" << endl;
                ShowAllInOrder(root->getRight());
            }
            return;
        };
};


void ShowMenu(){
    cout << "1 - Insert city." << endl;
    cout << "2 - Remove city by name." << endl;
    cout << "3 - Remove city by coordinate." << endl;
    cout << "4 - Search city by name." << endl;
    cout << "5 - Search city by coordinate." << endl;
    cout << "6 - Search by distance although of one point (x,y)." << endl;
    cout << "7 - Show all cities." << endl;
    cout << "8 - Exit the program." << endl;
    return;
}


int main(){

    nodeTree<int> arvore("Rio", 2, 3);

    int opt = 0;
    while (opt!=8){
        ShowMenu();
        cout << "Digit one option in list:" << endl;
        cin >> opt;
        getchar();
        if (opt==1){
            arvore.insert();
        }
        else if (opt==7){
            arvore.ShowAllInOrder(arvore.getRoot());
        }
    }

    return 0;
}