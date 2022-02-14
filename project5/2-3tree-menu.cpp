//João Voctor dos Santos Araujo
//Rafael Luiz dos Santos
//Compilado em g++ utilizando C++
#include <iostream>
#include <string>
#include <cstring>
#define DEBUG if(0)
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
        string temp_mKey;
        string temp_mWord;
        string thirdKey;
        string thirdWord;
    public:
        Node(string theKey, string theValue){
            this -> lKey = theKey;          //Um nó vazio sempre terá os primeiros elementos 
            this -> lWord = theValue;       //(chave e palavra) colocados na parte esquerda do nó
            this -> left = NULL;            //ou seja, na lKey e na lWord
            this -> mid = NULL;
            this -> right = NULL;
            this -> rKey = "";
            this -> rWord = "";
            this -> temp_mKey = "";
            this -> temp_mWord = "";
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
        string GetTempMidKey(){return temp_mKey;}
        string GetTempMidKeyValue(){return temp_mWord;}
        //string GetRightKeyValue(){return rWord;}
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
        
        void setLeftField(Node* node, string key, string value){   //Este método serve para adicionar a
            node -> lKey = key; node -> lWord = value;              //chave e o valor no lado esquerdo do nó
        }

        void setTempMidField(Node* node, string key, string value){   //Este método serve para adicionar a
            node -> temp_mKey = key; node -> temp_mWord = value;              //chave e o valor no meio do nó
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

        int promote(Node* node, string side){
            DEBUG{cout << "promocao\n";}
            string key, value;
            if(side == "left"){
                tie(key, value) = node -> GetLeft() -> getMidChild(node);
                node -> GetLeft() -> popThirdField(node -> GetLeft());
                //fazer pop do third field, para preparar a separação dos nós
            }
            else if(side == "middle"){
                tie(key, value) = node -> GetMid() -> getMidChild(node);
                node -> GetMid() -> popThirdField(node -> GetMid());
            }
            else{
                tie(key, value) = node -> GetRight() -> getMidChild(node);
                node -> GetRight() -> popThirdField(node -> GetRight());
            }

            if(node -> rightFieldIsEmpty(node)){
                if(key < node -> GetLeftKey()){
                    node -> pushRight(node, key, value);
                    DEBUG{cout << "joab2\n";}
                }
                else{
                    node -> setRightField(node, key, value);
                    DEBUG{cout << "joab2   " << node ->GetLeftKey();}
                
                }

                if(side == "left"){
                    node -> mid = new Node(node -> GetLeft() -> GetRightKey(),
                                           node -> GetLeft() ->GetRightKeyValue());
                    node -> GetLeft() -> clearRightField(node -> GetLeft());
                }
                else if(side == "right"){
                    node -> mid = new Node(node -> GetRight() -> GetLeftKey(),
                                           node -> GetRight() ->GetLeftKeyValue());
                    node -> GetRight() -> popRight(node -> GetRight());
                }
                cout << "   " <<node ->GetLeftKey() << endl;

                return 0;
            }
            else{
                node -> setThirdField(node, key, value);

                if(side == "left"){
                    node -> mid = new Node(node -> GetLeft() -> GetRightKey(),
                                           node -> GetLeft() ->GetRightKeyValue());
                    node -> GetLeft() -> clearRightField(node -> GetLeft());
                }
                else if(side == "right"){
                    node -> mid = new Node(node -> GetRight() -> GetLeftKey(),
                                           node -> GetRight() ->GetLeftKeyValue());
                    node -> GetRight() -> popRight(node -> GetRight());
                }

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
            DEBUG{cout<<"rachou funcao\n";}
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
            DEBUG{cout<<"dividiu funcao\n";}
            node -> order(node);
            
            Node* leftNode = new Node(node ->GetLeftKey(), node -> GetLeftKeyValue(),
                                      node ->GetLeft() -> GetLeft(), 
                                      node -> GetMid() -> GetMid(),
                                      node -> GetRight() -> GetRight());

            Node* rightNode = new Node(node -> GetThirdKey(), node -> GetThirdKeyValue(),
                                       node -> GetMid(), NULL, node -> GetRight());
            node -> SetLeft(leftNode);
            node -> SetRight(rightNode);
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
                        DEBUG{cout<<"rachou\n";}
                    }
                }
                else if(key > root -> GetLeftKey()){
                    if(root -> rightFieldIsEmpty(root)){
                        root -> setRightField(root, key, value);
                    }
                    else{
                        splitRoot(root, key, value);
                        DEBUG{cout<<"rachou\n";}
                    }
                }
            }
            else{
                if(key < root -> GetLeftKey()){
                    int insertResult;
                    insertResult = Insert(key, value, root ->GetLeft());
                    if(insertResult == 1){
                        int promotionResult;
                        DEBUG{cout << "joab0\n";}
                        promotionResult = root -> promote(root, "left");
                        DEBUG{cout << "result: "<< promotionResult<<"  joab0 e:  " << root->GetLeftKey() <<endl;}
                        traversal(root);

                        if(promotionResult == 2){
                            splitRoot(root);
                            DEBUG{cout<<"dividiu\n";}
                        }
                    }
                    return;
                }
                else if(!root -> rightFieldIsEmpty(root) && key < root -> GetRightKey()){
                    int insertResult;
                    insertResult = Insert(key, value, root -> GetMid());
                    if(insertResult == 1){
                        int promotionResult;
                        promotionResult = root -> promote(root, "middle");

                        if(promotionResult == 2){
                            splitRoot(root);
                            DEBUG{cout<<"dividiu\n";}
                        }
                    }
                    return;
                }
                else{
                    int insertResult;
                    insertResult = Insert(key, value, root -> GetRight());
                    if(insertResult == 1){
                        int promotionResult;
                        promotionResult = root -> promote(root, "right");

                        if(promotionResult == 2){
                            splitRoot(root);
                            DEBUG{cout<<"dividiu\n";}
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
                        DEBUG{cout << "joab promovido aqui\n";}
                        node -> setThirdField(node, key, value);
                        node -> order(node);
                        return 1;
                    }
                }
                else{
                    if(node -> rightFieldIsEmpty(node)){
                        node -> setRightField(node, key, value);
                        node->order(node);
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
            return 0;
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
                DEBUG{cout<<"ola2\n";}
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

        //Chama a segunda declaração de Find() para por polimorfismo
        Node* Find(string key){
            Node* temp_root = root;
            Node* find = Find(key, temp_root);
            //root = temp_root;
            return find;
        }

        // Se aproveita do código da transversal para percorrer a árvore até achar a key certa. 
        // Se não, return null, se não o ponteiro para o node da key
        Node* Find(string key, Node* root){
            //DEBUG{cout<<"AQUI find\n";}
            if ((root->GetLeftKey().compare(key))==0 || (root->GetRightKey().compare(key)==0)){// || (root->GetLeft().compare(key)==0) || (root->GetRight().compare(key)==0) || (root->GetMid().compare(key)==0)){
                DEBUG{cout<<"achou\n";}
                return root;
            }
            if(root->GetLeft() != NULL){
                DEBUG{cout<<"go left\n";}
                return Find(key, root->GetLeft());
            }
            if(!root->rightFieldIsEmpty(root)){
                if (root->GetMid()!=NULL){
                    DEBUG{cout<<"go mid\n";}
                    return Find(key, root->GetMid());
                }
            }
            if(root->GetRight() != NULL){
                DEBUG{cout<<"go right\n";}
                return Find(key, root->GetRight());
            }
            DEBUG{cout<<"go null\n";}
            return NULL;
        }

        // Verifica se o nó tem filhos:
        Node* IsChildren(Node* node){
            if (node->GetMid()!=NULL){
                return node->GetMid();
            }
            if (node->GetLeft()!=NULL){
                return node->GetLeft();
            }
            if (node->GetRight()!=NULL){
                return node->GetRight();
            }
            return NULL;
        }

        // Utiliza a função Find para deletar:
        bool Delete(string key){
            DEBUG{cout << "AQUI!!"<<endl;}
            Node* search = Find(key);
            DEBUG{cout << "AQUI!!"<<endl;}
            if (search!=NULL){
                DEBUG{cout << "AQUI!!"<<endl;}
                Node* is_children = IsChildren(search);
                DEBUG{cout << "AQUI!!"<<endl;}
                if (is_children!=NULL){
                    DEBUG{cout << "AQUI!!"<<endl;}
                    if (search->GetLeftKey().compare(key)==0){
                        if ((!is_children->GetLeftKey().empty()) && (!is_children->GetRightKey().empty())){
                            string temp_key = is_children->GetLeftKey();
                            string temp_word = is_children->GetLeftKeyValue();
                            is_children->setLeftField(is_children, "", "");
                            search->setLeftField(search, temp_key, temp_word);
                        }
                        else{
                            search=is_children;
                        }
                    }
                    else if (search->GetRightKey().compare(key)==0){
                        if ((!is_children->GetLeftKey().empty()) && (!is_children->GetRightKey().empty())){
                            string temp_key = is_children->GetRightKey();
                            string temp_word = is_children->GetRightKeyValue();
                            is_children->setRightField(is_children, "", "");
                            search->setRightField(search, temp_key, temp_word);
                        }
                        else{
                            search=is_children;
                        }
                    }
                }
                else{
                    if (search->GetLeftKey().compare(key)==0){
                        search->setLeftField(search, "", "");
                    }
                    if (search->GetRightKey().compare(key)==0){
                        search->setRightField(search, "", "");
                    }
                }
                return true;
            }
            return false;
        }
};


int main(){
    Tree_2_3 tree23;
    int exit = 1;
    while (exit==1){
        int opt;
        cout << "1 - para inserir.\n";
        cout << "2 - para encontrar.\n";
        cout << "3 - para deletar.\n";
        cout << "4 - para mostrar todos elementos do dicionário.\n";
        cout << "0 - para sair.\n";
        cout << "Digite uma opção:\n";
        cin >> opt;
        if (opt==0){exit = 0;}
        else if (opt==1){
            string key;
            cout << "Digite o valor da chave: ";
            cin >> key;
            string value;
            cout << "Digite o valor para a chave: ";
            cin >> value;
            tree23.Insert(key, value);
        }
        else if (opt==2){
            cout << "Digite a chave a ser procurada: ";
            string finded;
            cin >> finded;
            Node* search = tree23.Find(finded);
            DEBUG{cout << "AQUI\n";}
            if (search!=NULL){
                if (search->GetRightKey().compare(finded)==0){
                    cout << "To "<< finded << " at " << search->GetRightKeyValue() << endl;
                }
                if (search->GetLeftKey().compare(finded)==0){
                    cout << "To "<< finded << " at " << search->GetLeftKeyValue() << endl;
                }
            }
            else{cout<<"Chave não encontrada."<<endl;}
            DEBUG{cout << "AQUI\n";}
        }
        else if (opt==3){
            string del;
            cout << "Digite a chave para deletar: ";
            cin >> del;
            bool is_deleted = tree23.Delete(del);
            if (is_deleted==true){
                cout<<"Chave e respectivo valor eliminadas."<<endl;
            }
            else{
                cout<<"Chave não encontrada."<<endl;
            }
        }
        else if (opt==4){
            tree23.traversal();
            cout << endl;
        }

    }
    return 0;
}