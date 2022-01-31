/*int	indPai= -1;
% perguntar se o pai existe
for(i=0; i<numNo; i++){
	if (arvore[1,i]=pai);
		indPai = i;
}

%verifico se encontrei o pai
if (indPai == -1){
% não encontrei	
	printf(“erro pai não encontrado”);
}else {
%encontrei pai, verificar se posso incluir mais um nó na arvore
	if (numNo=10){
%não pode inserir
		printf(“erro estrutura cheia”);
	}else{
%pode inserir
		arvore[0,numNo]= indPai;
		arvore[1,numNo]= elemento;
		numNo++;
	}
}*/

#include <iostream>


class Node{
    private:
        int info;
        int* mother;
        int* chidrens;
    public:
        Node(int information, int* mother, int* childrens){
            info = information;
            mother = mother;
            childrens = childrens;
        }
        int getInfo(){return info;}
};


class NTree{
    private:
        int num_nodes;
        int* nodes;
    public:
        Ntree(){
            num_nodes = 0;
            nodes = NULL;
        }
        bool IsMother(int info){
            if (nodes==NULL){return false;}
            for (int i=0; i<num_nodes; ++i){
                if (nodes[i].getInfo() = info){return true;}
            }
            return false;
        }
        bool insertMother(int elem, int* mother){
            if (IsMother(elem)==true){
                cout << "Element already exist in tree." << endl;
                return false;
            }
            else if (num_nodes==10){
                cout << "Maximun number of nodes researched." << endl;
                return false;
            }
            else{
                nodes[num_nodes][0] = new Node(elem, &mother, NULL);
                num_nodes += 1;
            }
        }        
};


int main(){



    return 0;
}