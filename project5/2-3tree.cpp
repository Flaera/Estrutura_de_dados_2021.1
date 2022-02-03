#include <iostream>
#include <string>

using namespace std;


class Node{
    private:
        Node* left;
        Node* mid;
        Node* right;
        Node* temp_third;
        string value;
        string word;
    public:
        Node(string theWord, string theValue){
            this -> word = theWord;
            this -> value = theValue;
            this -> left = NULL;
            this -> mid = NULL;
            this -> right = NULL;
            this -> temp_third = NULL;
        }
        Node(){}
        ~Node(){}
        Node* GetLeft(){return left;}
        Node* GetMid(){return mid;}
        Node* GetRight(){return right;}
        string GetWordKey(){return word;}
        string GetValue(){return value;}
        void SetLeft(Node* node){left = node;}
        void SetMid(Node* node){mid = node;}
        void SetRight(Node* node){right = node;}
};


class Tree_2_3{
    private:
        Node* root;
    public:
        Tree_2_3(){
            string root_world;
            string root_value;
            cout << "Digit word/key of the node root: ";
            cin >> root_world;
            cout << "Digit value of the node root: ";
            cin >> root_value;
            Insert(root_world, root_value);
            cout << "Tree 2-3 created in form of dictionary.\n";
        }
        ~Tree_2_3(){}


        void Insert(string key, string value){
            // cout << "string:" << root->GetValue();
            // if (root->GetValue()==""){
            //     root(key, value);
            // }
            // else{
            InsertAux(key, value, root);
        }
        int InsertAux(string key, string value, Node* node){
            cout << "AQUI SIM???\n";
            if (node->GetLeft()!=NULL){
                cout<<"left\n";
                cout << key; // problema ta nesses couts!! Verficar amanhã!!!!!!!!!!!!
                cout << node->GetLeft()->GetWordKey()[0] << "??\n"; 
                if (key[0]<node->GetLeft()->GetWordKey()[0]){
                    //Go to left
                    return InsertAux(key, value, node->GetMid());
                }
            }
            else if (node->GetRight()!=NULL){
                if (key[0]>node->GetRight()->GetWordKey()[0]){
                    //Go to right
                    cout<<"right\n";
                    return InsertAux(key, value, node->GetRight());
                }
            }
            else if (node->GetMid()!=NULL){
                if (key[0]>node->GetMid()->GetWordKey()[0]){
                    //Go to mid
                    cout<<"mid\n";
                    return InsertAux(key, value, node->GetMid());
                }
            }
            cout << "AQUI!!!\n";
            //Insertions:
            if ((node->GetLeft()==NULL) && (node->GetRight()!=NULL) && (node->GetMid()==NULL)){
                Node* node = new Node(key, value);
                node->SetLeft(node);
                return 1;
            }
            else if ((node->GetLeft()!=NULL) && (node->GetRight()==NULL) && (node->GetMid()==NULL)){
                Node* node = new Node(key, value);
                node->SetRight(node);
                return 2;
            }
            else if ((node->GetLeft()!=NULL) && (node->GetRight()!=NULL) && (node->GetMid()==NULL)){
                Node* node = new Node(key, value);
                node->SetMid(node);
                //if ()
                return 3;
            }
        return 0;
        }
};
        

int main(){
    Tree_2_3 tree23;

    tree23.Insert("m", "rafael");
    tree23.Insert("2", "joao");
    tree23.Insert("t", "ana");
    tree23.Insert("4", "rebeca");
    tree23.Insert("a", "alice");   
    
    return 0;
}