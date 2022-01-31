#include <iostream>
#include <string>

using namespace std;

class Node{
    private:
        Node* left;
        Node* right;
        string word;
    public:
        Node(string theWord){
            this -> word = theWord;
            this -> left = NULL;
            this -> right = NULL;
        }
        Node(){}
        ~Node(){}
};

class Tree_2_3{
    private:
        Node* root;
    public:
        Tree_2_3(){
            cout << "Digit word of the node root: "
            string word;
            cin << word;
        }
};

int main(){
    cout << "Ola";
    
    
    return 0;
}