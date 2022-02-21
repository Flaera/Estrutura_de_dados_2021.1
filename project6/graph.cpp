/*  Os objetivos deste programa é testar a eficiência de grafos em 3 situações:
    1 - grafo implementado com matriz de adjacência ou lista de adjacência;
    2 - algoritmo de Djikstra utilizando fila de prioridade ou tabela de distância de vértices;
    3 - usar grafos esparsos e densos
*/  
#include <iostream>
#define VISITED true
#define UNVISITED false
#define INFINITY 1  //aqui n sei qual é o valor desta diretriz, mas coloquei 1
                    //porque em outro momento do código é dita como 0
#define LIST_EMPTY "List empty."
#define LIST_FULL "List fully."
#define DEBUG if(0)

using namespace std;


//Classe abstrata de um grafo
class Graph{
    public:
        Graph() {}
        virtual ~Graph() {}
        virtual void init(int n) = 0;
        virtual int n() = 0;
        virtual int e() = 0;
        virtual int first(int v) = 0;
        virtual int next(int v, int w) = 0;
        virtual void setEdge(int v1, int v2, int weight) = 0;
        virtual void delEdge(int v1, int v2) = 0;
        virtual bool isEdge(int i, int j) = 0;
        virtual int weight(int v1, int v2) = 0;
        virtual int getMark(int v) = 0;
        virtual void setMark(int v, int val) = 0;
};

//Classe para o vértice utilizado no grafo com lista de adjacência
class Edge{
    private:
        int vert, wt;
    public:
        Edge() {vert = -1; wt = -1;}
        Edge(int v, int w) {vert = v; wt = w;}
        int vertex() {return vert;}
        int weight() {return wt;}
};

//Classe de lista ligada para o grafo por lista de adjacência
template <typename E>
class List{
    // E List(){
        
    // };
    private:
        int curr, curr_size, max_size, initMaxSize;
        int *array;
    public:
        List(int max_size2){
            curr = 0;
            curr_size = 0;
            max_size = initMaxSize = max_size2;
            array = new int[max_size];
        }
        ~List(){
            delete array;
        }
        void Insert(int element){
            if ((curr_size!=0) && (curr_size<max_size)){
                DEBUG{cout<<"AQUImax_size1: " << max_size << endl;}
                for (int j=curr_size; j>=curr; j--){
                    array[j] = array[j-1];
                }
            }
            else if (curr_size>=max_size-1){
                doubleList(element);
                return;
            }
            
            array[curr] = element;
            //curr+=1;
            curr_size+=1;        
            return;
        }

        void doubleList(int element){
            DEBUG{cout<<"AQUImax_size2: " << max_size << endl;}
            cout << LIST_FULL;
            //Copying array:
            int array_copy[max_size + 1];
            for (int i=0; i<curr; ++i){
               array_copy[i] = array[i];
            }
            array_copy[curr] = element;
            curr_size+=1;
            for (int j=curr+1; j<curr_size; ++j){
                array_copy[j] = array[j-1];
            }
            DEBUG{
                for (int l=0; l<curr_size; ++l){
                    cout << "-" << array_copy[l] << "-" << endl;
                }
            }
            //Creating new array
            delete[] array;
            max_size = 2*max_size;
            array = new int[max_size]; //It can generated out of memory
            for (int k=0; k<curr_size; ++k){
                array[k] = array_copy[k];
            }
            cout << "Array doubled." << endl << endl;
            return;
        }

        void Remove(){
            if (curr_size!=0){
                for (int i=curr; i<curr_size; ++i){
                    array[i] = array[i+1];
                }
                curr_size--;
                cout << "Element in current position was removed.\n";
            }
            else{
                cout << LIST_EMPTY;
                array[curr] = -1;
            }
        }

        //Return element on the actual position on the list
        int GetCurrentElem(){
            if(curr_size == 0)
                return -1;
            
            return array[curr];
            //DEBUG{printf("curr:%d-\n", curr);}
        }

        int SetCurrent(int index){
            if ((index<curr_size) && (index >= 0)){
                curr = index;
                cout << "Setting for current element: " << array[curr] << endl;
                return array[curr];
            }
            cout << "Index parameter most that current size list." << endl;
            return -1;
        }

        int length(){
            return curr_size;
        }

        int maxSize(){
            return max_size;
        }

        //Return actual position in the list
        int getCurrentPos(){
            return curr;
        }

        void nextPos(){
            if(curr == curr_size)
                cout << "No more positions ahead! Already at the end of the list." << endl << endl;
            else{
                curr += 1;
                cout << "Moved 1 position to the rigth." << endl << endl;
            }
        }

        void prevPos(){
            if(curr == 0)
                cout << "No more positions behind! Already at the beginning of the list." << endl << endl;
            else{
                curr -= 1;
                cout << "Moved 1 position to the left." << endl << endl;
            }
        }

        void moveToStart(){
            if (curr == 1)
                cout << "Already at the beginning of the list." << endl << endl;
            else{
                curr = 0;
                cout << "Moved to the first position on the list." << endl << endl;
            }
        }

        void moveToEnd(){
            if (curr == curr_size)
                cout << "Already at the end of the list." << endl << endl;
            else{
                curr = curr_size;
                cout << "Moved to the last occupied position on the list." << endl << endl;
            }
        }

        void clear(){
            delete array;
            curr = 0;
            curr_size = 0;
            max_size = initMaxSize;
            array = new int[initMaxSize];
        }

        int find(int value){
            for(int i = 0; i < curr_size; i++){
                if(value == array[i]){
                    cout << "The element " << value << " is in position " << i << "." << endl << endl;
                    return 0;
                }
            }
            
            cout << "The element " << value << " isn't in the list." << endl << endl;

            return 0;
        }

        void doubleListAppend(int element){
            DEBUG{cout<<"AQUImax_size2: " << max_size << endl;}
            cout << LIST_FULL;
            //Copying array:
            int array_copy[max_size + 1];
            for (int i=0; i<curr_size; ++i){
               array_copy[i] = array[i];
            }
            curr_size+=1;
            array_copy[curr_size-1] = element;
            DEBUG{
                for (int l=0; l<curr_size; ++l){
                    cout << "-" << array_copy[l] << "-" << endl;
                }
            }
            //Creating new array
            delete[] array;
            max_size = 2*max_size;
            array = new int[max_size]; //It can generated out of memory
            for (int k=0; k<curr_size; ++k){
                array[k] = array_copy[k];
            }
            cout << "Array doubled." << endl << endl;
            return;
        }

        void append(int value){
            if(curr_size == max_size){
                doubleListAppend(value);
            }else{
                array[curr_size] = value;
                curr_size += 1;
            }
        }

        void ShowAll(){
            cout << endl << "#####" << endl;
            for (int i=0; i<curr_size; ++i){
                cout << '-' << array[i] << '-' << endl;
            }
            cout << "#####" << endl << endl ;
        }
};

template <typename E>
class LList: public List{
    // E LList(){

    // };
    private:
        bool status_list;
        int *array;
        int len2;
    public:
        LList(int len){
            len2 = len;
            array = (int *)malloc(sizeof(List(len2)));
            if (array==NULL){
                cout << "Memory full. No space in the memory." << endl;
                status_list = false;
            }
            cout << "Array created." << endl;
            status_list = true;
        }
        ~LList(){
            free(array);
        }
        bool Status(){
            return status_list;
        }
};

//Classe para o grafo utilizando matriz de adjacência
class GraphM : public Graph{
    private:
        int numVertex, numEdge;
        int **matrix;
        int *mark;
    public:
        GraphM(int numVert){
            init(numVert);
        }

        ~GraphM(){
            delete [] mark;
            for(int i = 0; i<numVertex; i++)
                delete [] matrix[i];
            delete [] matrix;
        }

        void init(int n){
            int i;
            numVertex = n;
            numEdge = 0;
            mark = new int[n];

            for(i = 0; i < numVertex; i++){
                mark[i] = UNVISITED; //Tem escrito assim no livro mas não compila
            }
            
            matrix = (int**) new int*[numVertex];
            for(i = 0; i < numVertex; i++)
                matrix[i]= new int[numVertex];

            for(i = 0; i < numVertex; i++)
                for(int j = 0; j < numVertex; j++)
                    matrix[i][j] = 0;
        }

        int n() {return numVertex;}
        int e() {return numEdge;}

        int first(int v){
            for(int i = 0; i < numVertex; i++)
                if(matrix[v][i] != 0) return i;
            return numVertex;
        }

        int next(int v, int w){
            for(int i = w + 1; i < numVertex; i++)
                if(matrix[v][i] != 0) return i;
            return numVertex;
        }

        void setEdge(int v1, int v2, int wt){
            //Assert(wt > 0, "Illegal weight value");
            if(matrix[v1][v2] == 0) numEdge++;
            matrix[v1][v2] = wt;
        }

        void delEdge(int v1, int v2){
            if(matrix[v1][v2] != 0) numEdge--;
            matrix[v1][v2] = 0;
        }

        bool isEdge(int i, int j){
            return matrix[i][j] != 0;
        }

        int weight(int v1, int v2) {return matrix[v1][v2];}
        int getMark(int v) {return mark[v];}
        void setMark(int v, int val) {mark[v] = val;}
};

//Classe para o grafo utilizando lista de adjacência
class GraphL : public Graph{
    private:
        List<Edge>** vertex; // implementar nesse arquivo uma classe de lista ligada
        int numVertex, numEdge;
        int *mark;
    public:
        GraphL(int numVert){
            init(numVert);
        }

        ~GraphL(){
            delete [] mark;
            for(int i = 0; i < numVertex; i++) 
                delete [] vertex[i];
            delete [] vertex;
        }

        void init(int n){
            int i;
            numVertex = 0;
            numEdge = 0;
            mark = new int[n];
            for(i = 0; i < numVertex; i++){                
                mark[i] = UNVISITED ////Tem escrito assim no livro mas não compila
            }
            vertex = (List<Edge>**) new List<Edge>*[numVertex];
            for(i = 0; i < numVertex; i++)
                vertex[i] = new LList<Edge>();
        }

        int n() {return numVertex;}
        int e() {return numEdge;}

        int first(int v){
            if(vertex[v] -> length() == 0){
                return numVertex;
            }
            vertex[v] -> moveToStart();
            Edge it = vertex[v] -> getValue();
            return it.vertex();
        }

        int next(int v, int w){
            Edge it;
            if(isEdge(v, w)){
                if((vertex[v]->currPos()+1) < vertex[v]->lenght()){
                    vertex[v] -> next();
                    it = vertex[v] -> getValue();
                    return it.vertex();
                }
            }
            return n();
        }

        void setEdge(int i, int j, int weight){
            Edge currEdge(j, weight);
            if(isEdge(i, j)){
                vertex[i] -> remove();
                vertex[i] -> insert(currEdge);
            }
            else{
                numEdge++;
                for(vertex[i] -> moveToStart();
                    vertex[i] -> currPos() < vertex[i] -> length();
                    vertex[i] -> next()){
                        Edge temp = vertex[i] -> getValue();
                        if(temp.vertex() > j) break;
                    }
                vertex[i] -> insert(currEdge);
            }
        }

        void delEdge(int i, int j){
            if(isEdge(i, j)){
                vertex[i] -> remove();
                numEdge--;
            }
        }

        bool isEdge(int i, int j){
            Edge it;
            for(vertex[i] -> moveToStart();
                vertex[i] -> currPos() < vertex[i] -> length();
                vertex[i] -> next()){
                    Edge temp = vertex[i] -> getValue();
                    if(temp.vertex() == j)
                        return true;
                }
                return false;
        }

        int weight(int i, int j){
            Edge curr;
            if(isEdge(i, j)){
                curr = vertex[i] -> getValue();
                return curr.weight();
            }
            else return 0;
        }

        int getMark(int v) {return mark[v];}
        void setMark(int v, int val) {mark[v] = val;}
};


//Class graph with list adjacency and algorithm of Dijsktra:
class GraphLDijsktra: public GraphL{
    public:
        int minVertex(Graph* G, int* D) { // Find min cost vertex
            int i, v = -1;
            // Initialize v to some unvisited vertex
            for (i=0; i<G->n(); i++)
                if (G->getMark(i) == UNVISITED) { v = i; break; }
            for (i++; i<G->n(); i++) // Now find smallest D value
                if ((G->getMark(i) == UNVISITED) && (D[i] < D[v]))
                    v = i;
            return v;
        }

        // Compute shortest path distances from "s".
        // Return these distances in "D".
        void Dijkstra(Graph* G, int* D, int s) {
            int i, v, w;
            for (int i=0; i<G->n(); i++)
                // Initialize
                D[i] = INFINITY;
            D[0] = 0;
            for (i=0; i<G->n(); i++) {
                // Process the vertices
                v = minVertex(G, D);
                if (D[v] == INFINITY) return; // Unreachable vertices
                G->setMark(v, VISITED);
                for (w=G->first(v); w<G->n(); w = G->next(v,w))
                    if (D[w] > (D[v] + G->weight(v, w)))
                    D[w] = D[v] + G->weight(v, w);
            }
        }
};


//class graph with implementation of matrix adjacency of Dijsktra:
class GraphMDijsktra: public GraphM{
    public:
        int minVertex(Graph* G, int* D) { // Find min cost vertex
            int i, v = -1;
            // Initialize v to some unvisited vertex
            for (i=0; i<G->n(); i++)
                if (G->getMark(i) == UNVISITED) { v = i; break; }
            for (i++; i<G->n(); i++) // Now find smallest D value
                if ((G->getMark(i) == UNVISITED) && (D[i] < D[v]))
                    v = i;
            return v;
        }

        // Compute shortest path distances from "s".
        // Return these distances in "D".
        void Dijkstra(Graph* G, int* D, int s) {
            int i, v, w;
            for (int i=0; i<G->n(); i++)
                // Initialize
                D[i] = INFINITY;
            D[0] = 0;
            for (i=0; i<G->n(); i++) {
                // Process the vertices
                v = minVertex(G, D);
                if (D[v] == INFINITY) return; // Unreachable vertices
                G->setMark(v, VISITED);
                for (w=G->first(v); w<G->n(); w = G->next(v,w))
                    if (D[w] > (D[v] + G->weight(v, w)))
                    D[w] = D[v] + G->weight(v, w);
            }
        }
};


int main(){

    int opt = 1;
    while (opt!=0){
        cout<<"1 - Test graph with matrix of adjacency."<<endl;
        cout<<"2 - Test graph with list of adjacency."<<endl;
        cout<<"3 - Test graph with matrix of adjacency and algorithm of Dijsktra."<<endl;
        cout<<"4 - Test graph with list of adjacency and algorithm of Dijsktra."<<endl;
        cout<<"5 - Test with graph sparse."<<endl;
        cout<<"6 - Test with graph dense."<<endl;
        cout<<"0 - Exit."<<endl;
        cout << "Digit one option: ";
        cin >> opt;
        if (opt==1){
            return 1;
        }
    }


    return 0;
}