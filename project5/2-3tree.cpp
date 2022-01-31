#include <iostream>
#include <string>

using namespace std;

class Node{
    private:
        Node* left;
        Node* right;
        string word;

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


};

int main(){
    cout << "Ola";
}