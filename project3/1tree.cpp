#include <iostream>
#include <string.h>
#include <cmath>
#include <stdio.h>
#define DEBUG if(1)

using namespace std;

template <typename E> class Link {
    private:
        Link<E>* left;
        Link<E>* right; // Pointer to next node in list
        string name_city;
        int positions[2];
    public:
        // Constructors
        Link(string city, int posX, int posY){
            this->name_city = city;
            this->positions[0] = posX;
            this->positions[1] = posY;
            left = NULL;
            right = NULL;
            cout << "Node created." << endl;
        }
        Link(){}
        string getNameCity(){return name_city;}
        int getPosX(){return positions[0];}
        int getPosY(){return positions[1];}
        Link<E>* getLeft(){return left;}
        Link<E>* getRight(){return right;}
        void setLeftNode(Link<E>* left2){left = left2;}
        void setRightNode(Link<E>* right2){right = right2;}
};

template <typename T> class nodeTree{
    //private:
        //Link<T> *root;
    public:
        Link<T>* root;
        nodeTree(){  //constructor with 3 parameters
            root = NULL;
            cout << "Node root created." << endl;
        };

        void insert(){
            string city;
            int posX, posY;
            cout << "Enter the name of the city: ";
            cin >> city;
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
        }

        //Cidades com inicial maiúsculas tem precedência alfabética
        //em relação à cidades com inicial minúscula. Bug deve ser consertado
        //antes de envio.
        void insertAux(Link<T>* root, string name_city, int posx, int posy){
            if(root->getNameCity() > name_city){
                if (root->getLeft()==NULL){
                    Link<T>* new_node = new Link<T>(name_city, posx, posy);
                    root->setLeftNode(new_node);
                }
                else{
                    insertAux(root->getLeft(), name_city, posx, posy);
                }
            }else{
                if (root->getRight()==NULL){
                    Link<T>* new_node = new Link<T>(name_city, posx, posy);
                    root->setRightNode(new_node);
                }
                else{
                    insertAux(root->getRight(), name_city, posx, posy);
                }
            }
        }

        int deleteChildren(Link<T>* node){
            if (node != NULL){
                int check = 1;
                check = deleteChilren(node->getLeft());
                if(check == 0){
                    delete root->getLeft();
                }
                check = deleteChilren(node->getRight());
                if(check == 0){
                    delete root->getRight();
                }
            }
            return 0;
        }

        Link<T>* getRoot(){
            return root;
        }


        void ShowAllInOrder(nodeTree<T> object){
            //Link<T> root = object.getRoot();
            if (object.root!=NULL){
                ShowAllInOrder(object.root->getLeft(), 0);
                cout << "City " << object.root->getNameCity() << " in ("<<object.root->getPosX()<<", "<<object.root->getPosY()<<")."<< endl;
                ShowAllInOrder(object.root->getRight(), 0);
            }
        }
    
        void ShowAllInOrder(Link<T>* root, int a){
            //Link<T> root = object.getRoot();
            if (root!=NULL){
                ShowAllInOrder(root->getLeft(), 0);
                cout << "City " << root->getNameCity() << " in ("<<root->getPosX()<<", "<<root->getPosY()<<")."<< endl;
                ShowAllInOrder(root->getRight(), 0);
            }
        }

        void deleteByCoordinate(nodeTree<T> object, int posX, int posY){
            int check;
            check = traverseCoordinate(object.root, posX, posY);
            if(check == 0){cout << "City not finded. Deletion could not occur." << endl;}
        }

        int traverseCoordinate(Link<T>* root, int posX, int posY){
            int check = 0;
            if (root!=NULL){
                check = traverseCoordinate(root->getLeft(), posX, posY);
                if(root->getPosX() == posX && root->getPosY() == posY){
                    if(root->getLeft() != NULL || root->getRight() != NULL){
                        char choice;
                        cout << endl <<"WARNING!! The node you want delete have children." << endl;
                        cout << "Deleting that node will delete it's children too." << endl;
                        cout << "Confirm deletion? (Y for yes | N for no)." << endl;
                        cout << "Enter your choice: ";
                        cin >> choice;
                        if(choice == 'n' || choice == 'N'){
                            cout << endl << "Deletion denied by user." << endl;
                            return 2;
                        }
                    }
                    delete root;
                    cout << "Node deleted" << endl;
                    return 1;
                }
                if(check == 1){
                    root->setLeftNode(NULL);
                    return check;
                }
                check = traverseCoordinate(root->getRight(), posX, posY);
                if(root->getPosX() == posX && root->getPosY() == posY){
                    if(root->getLeft() != NULL || root->getRight() != NULL){
                        char choice;
                        cout << endl <<"WARNING!! The node you want delete have children." << endl;
                        cout << "Deleting that node will delete it's children too." << endl;
                        cout << "Confirm deletion? (Y for yes | N for no)." << endl;
                        cout << "Enter your choice: ";
                        cin >> choice;
                        if(choice == 'n' || choice == 'N'){
                            cout << endl << "Deletion denied by user." << endl;
                            return 2;
                        }
                    }
                    delete root;
                    cout << "Node deleted" << endl;
                    return 1;
                }if(check == 1){
                    root->setRightNode(NULL);
                    return check;
                }
            }
            return check;
        }


        Link<T>* searchByName(nodeTree<T> object, string city, int trash){
            Link<T>* info = new Link<T>;
            info = searchByName(object.root, city);
            return info;
        }

        Link<T>* searchByName(Link<T>* root, string city){
            Link<T>* sroot = NULL;
            if (root->getNameCity() == city){return root;}
            if (root->getLeft()!=NULL){
                sroot = searchByName(root->getLeft(), city);
            }
            if (root->getRight()!=NULL){
                sroot = searchByName(root->getRight(), city);
            }
            return sroot;
        }

        void withinDistance(Link<T>* root, int posX, int posY, int radius){
            double distance;
            distance = sqrt(pow(abs(posX - root->getPosX()), 2) + pow(abs(posY- root->getPosY()), 2));
            if (distance <= radius){cout << "-" << root->getNameCity() << "-" << endl;}
        }

        void ShowAllInOrder(Link<T>* root, int posX, int posY, int radius){
            if (root!=NULL){
                ShowAllInOrder(root->getLeft(), posX, posY, radius);
                withinDistance(root, posX, posY, radius);
                ShowAllInOrder(root->getRight(), posX, posY, radius);
            }
        }

        bool searchByCoordinate(Link<T>* root, int posx, int posy){
            bool search = false;
            if (root!=NULL){
                if ((root->getPosX()==posx) && (root->getPosY()==posy)){return true;}
                search = searchByCoordinate(root->getLeft(), posx, posy);
                search = searchByCoordinate(root->getRight(), posx, posy);
            }
            return search;
        }
        
};


void ShowMenu(){
    char title[] = "TREE OF CITIES\0";
    for (int i=0; i<14; ++i){cout<<"#";}
    cout << endl << title << endl;
    for (int j=0; j<14; ++j){cout<<"#";}
    cout<<endl;

    cout << "1 - Insert city." << endl;
    cout << "2 - Remove city by name." << endl;
    cout << "3 - Remove city by coordinate." << endl;
    cout << "4 - Search city by name." << endl;
    cout << "5 - Search city by coordinate." << endl;
    cout << "6 - Search by distance although of one point (x,y)." << endl;
    cout << "7 - Show all cities." << endl;
    cout << "8 - Show root of the tree." << endl;
    cout << "9 - Exit the program." << endl;
    return;
}


int main(){

    nodeTree<int> arvore;

    int opt = 0;
    while (opt!=9){
        ShowMenu();
        cout << "Digit one option in list:" << endl;
        cin >> opt;
        getchar();
        if (opt==1){
            arvore.insert();
        }
        else if (opt==3){
            int posX, posY;
            cout << "Enter the x coordinate: ";
            cin >> posX;
            cout << "Enter the y coordinate: ";
            cin >> posY;
            arvore.deleteByCoordinate(arvore, posX, posY);
        }
        else if (opt==4){
            string city;
            cout << "Digit the name of city to search: " << endl;
            cin >> city;
            Link<int>* search_city = arvore.searchByName(arvore, city, 0);
            if (search_city != NULL){cout << "City finded." << endl;}
            else{cout << "City not found." << endl;}
        }else if (opt==5){
            int x, y;
            cout << "Digit the coordinate x: ";
            cin >> x;
            cout << "Digit the coordinate y: ";
            cin >> y;
            if ((arvore.getRoot()->getPosX()==x) && (arvore.getRoot()->getPosY()==y)){
                cout << "City finded." << endl;
            }
            else{
                bool search = arvore.searchByCoordinate(arvore.getRoot(), x, y);
                if (search==true){cout<<"City finded."<<endl;}
                else{cout<<"City not found."<<endl;}
            }
        }
        else if(opt==6){
            int posX, posY, radius;
            cout << "Enter the x coordinate: ";
            cin >> posX;
            cout << "Enter the y coordinate: ";
            cin >> posY;
            cout << "Enter the distance to the origin: ";
            cin >> radius;
            arvore.ShowAllInOrder(arvore.root, posX, posY, radius);
        }
        else if (opt==7){
            arvore.ShowAllInOrder(arvore);
        }
        else if (opt==8){
            if (arvore.getRoot()!=NULL){
                cout << "City "<< arvore.getRoot()->getNameCity()<< " in the root." << endl << endl;
            }
            else{cout<<"Root not created."<<endl;}
        }
        else if (opt==9){return 0;}
    }

    return 0;
}