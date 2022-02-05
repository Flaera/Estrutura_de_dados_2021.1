#include <iostream>
#include <string>

using namespace std;

class Node{
    private:
        Node* left;
        Node* mid;
        Node* right;
        string lKey;
        string lWord;
        string rKey;
        string rWord;
    public:
        Node(string theKey, string theValue){
            this -> lKey = theKey;          //Um nó vazio sempre terá os primeiros elementos 
            this -> lWord = theValue;       //(chave e palavra) colocados na parte esquerda do nó
            this -> left = NULL;            //ou seja, na lKey e na lWord
            this -> mid = NULL;
            this -> right = NULL;
        }
        Node(){}
        ~Node(){}
        Node* GetLeft(){return left;}
        Node* GetMid(){return mid;}
        Node* GetRight(){return right;}
        string GetLeftKeyValue(){return lWord;}
        string GetLeftKey(){return lKey;}
        string GetRightKeyValue(){return rWord;}
        string GetRightKey(){return rKey;}
        void SetLeft(Node* node){left = node;}
        void SetMid(Node* node){mid = node;}
        void SetRight(Node* node){right = node;}
        bool isEmpty(Node* node){       //Este método serve para indicar se um nó é vazio. Ele retorna
            return node -> lKey.empty();//verdadeiro caso o valor da chave esquerda do nó seja uma string
        }                               //vazia

        bool rightFieldIsEmpty(Node* node){ //Este método serve para indicar se o lado direito do nó é
            return node -> rKey.empty();    //vazio. Retorna verdadeiro caso a chave direita seja uma 
        }                                   //string vazia
        
        void setRightField(Node* node, string key, string value){   //Este método serve para adicionar a
            node -> rKey = key; node -> rWord = value;              //chave e o valor no lado direito do nó
        }
        void pushRight(Node* node, string key, string value){   //Este método serve para "empurrar" os valores
            node -> rKey = node -> lKey;                        //do lado esquerdo ao lado direito e adicionar
            node -> rWord =node -> lWord;                       //os valores indicados no parâmetro da função
            node -> lKey = key;                                 //ao lado esquerdo do nó
            node -> lWord = value;
        }
};


class Tree_2_3{
    private:
        Node* root;
    public:
        Tree_2_3(){
            string root_word;
            string root_value;
            cout << "Digit word/key of the node root: ";
            cin >> root_word;
            cout << "Digit value of the node root: ";
            cin >> root_value;
            root = new Node(root_word, root_value); 
            cout << "Tree 2-3 created in form of dictionary.\n";
        }
        ~Tree_2_3(){}


        void Insert(string key, string value){
            if (key < root->GetLeftKey()){      //Se o valor da chave for menor que o da raiz e não
                if(root->GetLeft() == NULL){    //houver nó à esquerda, a chave seráinserida num
                    Node* leftNode = new Node(key, value);//novo nó à esquerda da raiz
                    root->SetLeft(leftNode);
                }
                else{                                   //Caso já exista nó na esquerda
                    Insert(key, value, root->GetLeft());
                }
            }
            else if(key > root->GetRightKey()){ //Se o valor da chave for maior que o da raize não
                if(root->GetRight() == NULL){   //houver nó à direita, a chave será inserida 
                    Node* rightNode = new Node(key, value);//num novo nó à direita da raiz
                    root->SetRight(rightNode);
                }
                else{                                   //Caso já exista nó na esquerda
                    Insert(key, value, root->GetRight());
                }
            }
            }

        //Este método insere os valores da chave e do valor no campo esquerdo ou direito do nó.
        //Além disto este método não necessita saber se a posição do nó é à esquerda, ao meio, 
        //ou à direita do nó pai. Isso possibilita mais liberdade no uso deste método
        void Insert(string key, string value, Node* node){
            if(!node->isEmpty(node)){
                if(node->GetLeftKey() > key){
                    node->pushRight(node, key, value);
                }
                else{
                    node -> setRightField(node, key, value);
                }
            }
        }

        //Este método serve para iniciar a "travessia" pela árvore
        void traversal(){
            traversal(root -> GetLeft());
            cout <<"Key: " << root -> GetLeftKey() << "  Word: " << root -> GetLeftKeyValue() << endl;
            if(!root -> rightFieldIsEmpty(root)){
                traversal(root -> GetMid());
                cout <<"Key: " << root -> GetRightKey() << "  Word: " << root -> GetRightKeyValue() << endl;
            }
            traversal(root -> GetRight());
        }

        //Este método tem o intuito de efetuar a "travessia" pela árvore e faz isto de forma recursiva
        void traversal(Node* node){
            if(node -> GetLeft() != NULL){
                traversal(node ->GetLeft());
            }
            cout <<"Key: " << node -> GetLeftKey() << "  Word: " << node -> GetLeftKeyValue() << endl;
            if(!root -> rightFieldIsEmpty(node)){
                cout <<"Key: " << node -> GetRightKey() << "  Word: " << node -> GetRightKeyValue() << endl;
            }
            if(node -> GetRight() != NULL){
                traversal(node ->GetRight());
            }
            
        }

        //Este método serve para indicar se um nó é folha (Ainda não vi serventia nisso, mas deixei para
        //caso nos precisemos, mas se ao fim não precisarmos dele é só excluir mesmo)
        bool isLeaf(Node* node){
            return node->isEmpty(node);
        }
};

int main(){
    Tree_2_3 tree23;

    tree23.Insert("m", "rafael");
    tree23.Insert("x", "joao");
    tree23.Insert("z", "carla");
    tree23.Insert("c", "ana");
    tree23.Insert("b", "rebeca");
    tree23.Insert("a", "alice");   

    tree23.traversal();
    
    return 0;
}