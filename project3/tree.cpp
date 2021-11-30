#include <iostream>
#define DEBUG if(0)

using namespace std;


template <typename N> class CreateNode{
    public:
        CreateNode(N left2, N right2){
            char name_city[256];
            int positions[2];
            cout << "Digit the name of city:\n";
            cin >> name_city;
            cout << "Digit the positions in x and y of this city:" << endl;
            cin >> positions[0];
            cin >> positions[1];
            N left = left2;
            N right = right2;
        };
};


template <typename T> class nodeTree{
    private:
        CreateNode<int> *root;
    public:
        nodeTree(){
            *root = CreateNode<int>(0, 0); // node root
            cout << "Node root created. Tree created." << endl;
        }

        void insert(){
            if (root->left == 0){
                root->left = CreateNode<int>(0, 0);
                return;
            }
            else if (root->right==0){
                root->right = CreateNode<int>(0, 0);
                return;
            }
            insert(root->left); // to left
            insert(root->right); // to right
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

    nodeTree<int> arvore;

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