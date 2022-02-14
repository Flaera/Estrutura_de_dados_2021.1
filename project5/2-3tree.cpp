#include <iostream>
#include <string>
#include <tuple>

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
        string thirdKey;
        string thirdWord;
    public:
        Node(string theKey, string theValue){
            this -> lKey = theKey;          //Um nó vazio sempre terá os primeiros elementos 
            this -> lWord = theValue;       //(chave e palavra) colocados na parte esquerda do nó
            this -> left = NULL;            //ou seja, na lKey e na lWord
            this -> mid = NULL;
            this -> right = NULL;
        }

        Node(string theKey, string theValue, Node* left, Node* mid, Node* right){
            this -> lKey = theKey;
            this -> lWord = theValue;
            this -> left = left;
            this -> mid = mid;
            this -> right = right;
        }

        Node(){}
        ~Node(){}
        Node* GetLeft(){return left;}
        Node* GetMid(){return mid;}
        Node* GetRight(){return right;}
        string GetLeftKey(){return lKey;}
        string GetRightKey(){return rKey;}
        string GetThirdKey(){return thirdKey;}
        string GetLeftKeyValue(){return lWord;}
        string GetRightKeyValue(){return rWord;}
        string GetThirdKeyValue(){return thirdWord;}
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

        void setThirdField(Node* node, string key, string value){
            node -> thirdKey = key; node -> thirdWord = value;
        }

        void pushRight(Node* node, string key, string value){   //Este método serve para "empurrar" os valores
            node -> rKey  = node -> lKey;                        //do lado esquerdo ao lado direito e adicionar
            node -> rWord = node -> lWord;                       //os valores indicados no parâmetro da função
            node -> lKey  = key;                                 //ao lado esquerdo do nó
            node -> lWord = value;
        }

        void popRight(Node* node){
            node -> lKey  = node -> rKey;
            node -> lWord = node -> rWord;
            node -> rKey.clear();
            node -> rWord.clear();
        }

        void popThirdField(Node* node){
            node -> rKey  = node -> thirdKey;
            node -> rWord = node -> thirdWord;
            node -> thirdKey.clear();
            node -> thirdWord.clear();
        }

        void order(Node* node){
            string smallKey, smallVal, midKey, midVal, highKey, highVal;

            smallKey = node->lKey; midKey = node->rKey; highKey = node->thirdKey;
            smallVal = node->lWord; midVal = node->rWord; highVal = node->thirdWord;
            if(highKey < smallKey){
                string tempKey = smallKey; string tempValue = smallVal;
                node -> lKey = highKey;
                node -> lWord = highVal;
                node -> thirdKey = midKey;
                node -> thirdWord = midVal;
                node -> rKey = tempKey;
                node -> rWord = tempValue;
                
                return;
            }
            if(highKey < midKey){
                string tempKey = midKey; string tempValue = midVal;
                node -> rKey = highKey;
                node -> rWord = highVal;
                node -> thirdKey = midKey;
                node -> thirdWord = midVal;
            }
        }

        void clearRightField(Node* node){
            node -> rKey.clear();
            node -> rWord.clear();
        }

        void clearThirdField(Node* node){
            node -> thirdKey.clear();
            node -> thirdWord.clear();
        }

        bool isLeaf(Node* node){
            return node -> GetLeft() == NULL;
        }

        tuple<string, string> getMidChild(Node* node){
            return make_tuple(node->GetRightKey(), node->GetRightKeyValue());
        }

        void splitNode(Node* node){
            Node* leftNode = new Node(node -> GetLeftKey(), node -> GetLeftKeyValue(), 
                                      node->GetLeft(), NULL, NULL);
            Node* rightNode = new Node(node -> GetRightKey(), node -> GetRightKeyValue(),
                                      node -> GetMid(), NULL, node -> GetRight());
            node -> SetLeft(leftNode);
            node -> SetRight(rightNode);
        }

        int promote(Node* node, string side){
            cout << "promocao\n";
            cout << "promote   " << node ->GetLeftKey() << endl;
            string key, value;
            //tie(key, value);
            if(side == "left"){
                tie(key, value) = node -> GetLeft() -> getMidChild(node->GetLeft());
                node -> GetLeft() -> popThirdField(node -> GetLeft());
                cout <<"valores  "<< key << "   "<< value << endl;
                //fazer pop do third field, para preparar a separação dos nós
            }
            else if(side == "middle"){
                tie(key, value) = node -> GetMid() -> getMidChild(node->GetMid());
                node -> GetMid() -> popThirdField(node -> GetMid());
            }
            else{
                tie(key, value) = node -> GetRight() -> getMidChild(node->GetRight());
                node -> GetRight() -> popThirdField(node -> GetRight());
            }

            if(node -> rightFieldIsEmpty(node)){
                if(key < node -> GetLeftKey()){
                    node -> pushRight(node, key, value);
                    cout << "joab23\n";
                    cout << "joab23   " << node ->GetLeftKey();
                }
                else{
                    node -> setRightField(node, key, value);
                    cout << "joab25   " << node ->GetLeftKey();
                
                }

                if(side == "left"){
                    cout << "Left\n";
                    cout << "joabLeft   " << node ->GetLeftKey();
                    node -> mid = new Node(node -> GetLeft() -> GetRightKey(),
                                           node -> GetLeft() ->GetRightKeyValue());
                    node -> GetLeft() -> clearRightField(node -> GetLeft());
                }
                else if(side == "right"){
                    cout << "Right\n";
                    node -> mid = new Node(node -> GetRight() -> GetLeftKey(),
                                           node -> GetRight() ->GetLeftKeyValue());
                    node -> GetRight() -> popRight(node -> GetRight());
                }
                cout << "valor promo   " <<node ->GetLeftKey() << endl;


                return 0;
            }
            else{
                node -> setThirdField(node, key, value);
                node -> order(node);
                //splitNode(node);
                if(side == "left"){
                    Node* midNode = new Node(node -> GetLeft() -> GetRightKey(),
                                             node -> GetLeft() ->GetRightKeyValue());
                    node -> SetMid(midNode);
                    node -> GetLeft() -> clearRightField(node -> GetLeft());
                }
                else if(side == "right"){
                    Node* midNode = new Node(node -> GetRight() -> GetLeftKey(),
                                             node -> GetRight() ->GetLeftKeyValue());
                    node -> SetMid(midNode);
                    node -> GetRight() -> popRight(node -> GetRight());
                }
                cout << "valor promo   " <<node ->GetLeftKey() << endl;

                return 2;
            }
            return 0;
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

        void splitRoot(Node* node, string extraKey, string extraValue){
            cout<<"rachou funcao\n";
            node ->setThirdField(node, extraKey, extraValue);
            if(extraKey < node ->GetRightKey()){
                node -> order(node);
            }
            Node* leftNode = new Node(node ->GetLeftKey(), node -> GetLeftKeyValue());
            Node* rightNode = new Node(node -> GetThirdKey(), node -> GetThirdKeyValue());
            node -> SetLeft(leftNode);
            node -> SetRight(rightNode);
            node -> popRight(node);
            node -> clearThirdField(node);
        }

        void splitRoot(Node* node){
            cout<<"dividiu funcao\n";
            node -> order(node);
            //node -> splitNode(node -> GetLeft());
            Node* leftNode = new Node(node -> GetLeftKey(), node -> GetLeftKeyValue(),
                                      node -> GetLeft(), 
                                      node -> GetLeft() -> GetMid(),
                                      node -> GetLeft() -> GetRight());

            Node* midNode = new Node("", "");

            Node* rightNode = new Node(node -> GetThirdKey(), node -> GetThirdKeyValue(),
                                       node -> GetMid(), NULL, node -> GetRight()->GetRight());
            node -> SetLeft(leftNode);
            node -> SetRight(rightNode);
            node -> SetMid(midNode);
            node -> popRight(node);
            node -> clearThirdField(node);
        }

        void Insert(string key, string value){
            if(root ->isLeaf(root)){
                if(key < root -> GetLeftKey()){
                    if(root -> rightFieldIsEmpty(root)){
                        root -> pushRight(root, key, value);
                    }
                    else{
                        splitRoot(root, key, value);
                        cout<<"rachou\n";
                    }
                }
                else if(key > root -> GetLeftKey()){
                    if(root -> rightFieldIsEmpty(root)){
                        root -> setRightField(root, key, value);
                    }
                    else{
                        splitRoot(root, key, value);
                        cout<<"rachou\n";
                    }
                }
            }
            else{
                if(key < root -> GetLeftKey()){
                    int insertResult;
                    insertResult = Insert(key, value, root ->GetLeft());
                    if(insertResult == 1){
                        int promotionResult;
                        cout << "joab0Left\n";
                        promotionResult = root -> promote(root, "left");
                        cout << "result: "<< promotionResult<<" joab0Left e:  " << root->GetLeftKey() <<endl;
                        //traversal(root);

                        if(promotionResult == 2){
                            splitRoot(root);
                            cout<<"dividiuLeft\n";
                        }
                    }
                    return;
                }
                else if(!root -> rightFieldIsEmpty(root) && key < root -> GetRightKey()){
                    int insertResult;
                    insertResult = Insert(key, value, root -> GetMid());
                    if(insertResult == 1){
                        int promotionResult;
                        cout << "joab0Middle\n";
                        promotionResult = root -> promote(root, "middle");
                        cout << "result: "<< promotionResult<<" joab0Middle e:  " << root->GetLeftKey() <<endl;
                        if(promotionResult == 2){
                            splitRoot(root);
                            cout<<"dividiuMiddle\n";
                        }
                    }
                    return;
                }
                else{
                    int insertResult;
                    insertResult = Insert(key, value, root -> GetRight());
                    if(insertResult == 1){
                        int promotionResult;
                        cout << "joab0Middle\n";
                        promotionResult = root -> promote(root, "right");
                        cout << "result: "<< promotionResult<<" joab0Right e:  " << root->GetLeftKey() <<endl;
                        if(promotionResult == 2){
                            splitRoot(root);
                            cout<<"dividiuRight\n";
                        }
                    }
                    return;
                }
            }
            //cout << "fim da insert:  " << root ->GetLeftKey() << endl;
        }

        //Este método insere os valores da chave e do valor no campo esquerdo ou direito do nó.
        //Além disto este método não necessita saber se a posição do nó é à esquerda, ao meio, 
        //ou à direita do nó pai. Isso possibilita mais liberdade no uso deste método
        int Insert(string key, string value, Node* node){
            if(node -> isLeaf(node)){
                if(key < node -> GetLeftKey()){
                    if(node -> rightFieldIsEmpty(node)){
                        node -> pushRight(node, key, value);
                        return 0;
                    }
                    else{
                        //Aqui tem de haver a promoção
                        cout << "joab promovido aqui\n";
                        node -> setThirdField(node, key, value);
                        node -> order(node);
                        return 1;
                    }
                }
                else{
                    if(node -> rightFieldIsEmpty(node)){
                        node -> setRightField(node, key, value);
                        return 0;
                    }
                    else{
                        //Aqui tem de haver a promoção
                        node -> setThirdField(node, key, value);
                        node -> order(node);
                        return 1;
                    }
                }
            }
            else{
                if(key < node -> GetLeftKey()){
                    Insert(key, value, node ->GetLeft());
                }
                else if(key < node -> GetRightKey()){
                    Insert(key, value, node -> GetMid());
                }
                else{
                    Insert(key, value, node -> GetRight());
                }
            }
        }

        //Este método serve para iniciar a "travessia" pela árvore
        void traversal(){
            //cout<<"oi\n";
            if(root -> GetLeft() != NULL){
                traversal(root -> GetLeft());
            }
            //root -> GetRightKey().compare(root ->GetLeftKey())
            cout <<"Key: " << root -> GetLeftKey() << "  Word: " << root -> GetLeftKeyValue() << endl;
            if(!root -> rightFieldIsEmpty(root)){
                if(root -> GetMid() != NULL){
                    traversal(root -> GetMid());
                }
                cout <<"Key: " << root -> GetRightKey() << "  Word: " << root -> GetRightKeyValue() << endl;
            }
            if(root -> GetRight() != NULL){
                traversal(root -> GetRight());
            }
        }

        //Este método tem o intuito de efetuar a "travessia" pela árvore e faz isto de forma recursiva
        void traversal(Node* node){
            //cout<<"ola\n";
            if(node -> GetLeft() != NULL){
                cout<<"ola2\n";
                traversal(node ->GetLeft());
            }
            //cout<<"ola3\n";
            cout <<"Key: " << node -> GetLeftKey() << "  Word: " << node -> GetLeftKeyValue() << endl;
            if(!node -> rightFieldIsEmpty(node)){
                //cout<<"ola5\n";
                if(node -> GetMid() != NULL){
                    //cout<<"ola4\n";
                    traversal(node -> GetMid());
                }
                cout <<"Key: " << node -> GetRightKey() << "  Word: " << node -> GetRightKeyValue() << endl;
            }
            if(node -> GetRight() != NULL){
                //cout<<"ola6\n";
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
    tree23.traversal();
    cout << endl;
    tree23.Insert("x", "joao");
    tree23.traversal();
    cout << endl;
    tree23.Insert("z", "carla");
    tree23.traversal();
    cout << endl;
    tree23.Insert("m", "rafael");
    tree23.traversal();
    cout << endl;
    tree23.Insert("b", "rebeca");
    tree23.traversal();
    cout << endl;
    tree23.Insert("c", "ana");
    tree23.traversal();
    cout << endl;
    tree23.Insert("g", "manoel");   
    tree23.traversal();
    cout << endl;
    tree23.Insert("a", "alice");   
    tree23.traversal();
    
    return 0;
}