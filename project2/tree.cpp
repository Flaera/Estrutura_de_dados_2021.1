#include <iostream>

using namespace std;

template <typename T> class nodeTree{
    public:
        T element;
        nodeTree *left;
        nodeTree *right;

    nodeTree(T elemValue){
        left = NULL;
        element = elemValue;
        right = NULL;
    }
};


int main(){

    int value;
    cout << "Enter the element of the root node: ";
    cin >> value;

    nodeTree<int> arvore(value);

    cout << arvore.element << endl;
    cout << arvore.left << endl;
    cout << arvore.right << endl;

    return 0;
}