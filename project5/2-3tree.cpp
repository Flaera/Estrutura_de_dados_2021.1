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
            root = new Node(root_world, root_value); 
            cout << "Tree 2-3 created in form of dictionary.\n";
        }
        ~Tree_2_3(){}


        void Insert(string key, string value){
            //cout << "string:" << root->GetValue();
            if (root->GetValue()==""){
                root = new Node(key, value);
            }
            else{
                InsertAux(key, value, root);
            }
        }
        int InsertAux(string key, string value, Node* node){
            //cout << "AQUI SIM???\n" << node->GetLeft();
            if (node->GetLeft()!=NULL){
                string::iterator it1;
                it1 = key.begin();
                string::iterator it2;
                string left = node->GetLeft()->GetWordKey();
                it2 = left.begin();
                if (*it1<*it2){
                    //Go to left
                    cout<<"Left\n";
                    return InsertAux(key, value, node->GetLeft());
                }
            }
            if (node->GetRight()!=NULL){
                string::iterator it1;
                it1 = key.begin();
                string::iterator it2;
                string right = node->GetRight()->GetWordKey();
                it2 = right.begin();
                if (*it1>*it2){
                    //Go to right
                    cout<<"Right\n";
                    return InsertAux(key, value, node->GetRight());
                }
            }
            if (node->GetMid()!=NULL){
                // string::iterator it1;
                // it1 = key.begin();
                // string::iterator it2;
                // string mid = node->GetMid()->GetWordKey();
                // it2 = mid.begin();
                // if (*it1>*it2){
                    //Go to mid
                cout<<"Mid\n";
                return InsertAux(key, value, node->GetMid());
                // }
            }
            //cout << "AQUI!!!\n";
            //Insertions:
            if ((node->GetLeft()==NULL) && (node->GetRight()==NULL) && (node->GetMid()==NULL)){
                Node* new_node = new Node(key, value);
                node->SetLeft(new_node);
                return 1;
            }
            else if ((node->GetLeft()==NULL) && (node->GetRight()!=NULL) && (node->GetMid()==NULL)){
                Node* new_node = new Node(key, value);
                node->SetLeft(new_node);
                return 2;
            }
            else if ((node->GetLeft()!=NULL) && (node->GetRight()==NULL) && (node->GetMid()==NULL)){
                Node* new_node = new Node(key, value);
                node->SetRight(new_node);
                return 3;
            }
            else if ((node->GetLeft()!=NULL) && (node->GetRight()!=NULL) && (node->GetMid()==NULL)){
                Node* new_node = new Node(key, value);
                node->SetMid(new_node);
                return 4;
            }
            return 0;
        }


        Node* GetRoot(){return root;}


};
        

int main(){
    Tree_2_3 tree23;

    tree23.Insert("m", "rafael");
    tree23.Insert("x", "joao");
    tree23.Insert("z", "carla");
    tree23.Insert("c", "ana");
    tree23.Insert("b", "rebeca");
    tree23.Insert("a", "alice");   
    
    return 0;
}