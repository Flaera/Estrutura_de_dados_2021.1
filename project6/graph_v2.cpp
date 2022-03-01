/*  Desenvolvido por João Victor dos Santos Araujo e Rafael Luiz dos Santos

    Referente ao projeto 11.3 do livro

    Os objetivos deste programa são testar a eficiência de grafos em 3 situações:
        1 - grafo implementado com matriz de adjacência ou lista de adjacência;
        2 - algoritmo de Djikstra utilizando fila de prioridade ou tabela de distância de vértices;
        3 - usar grafos esparsos e densos

    Para tal medimos com o tempo de execução do algoritmo em cada uma das 8 situações
*/  
#include <iostream>
#include <list>
#include <queue>
#include <chrono>

#define VISITED 1
#define UNVISITED 0
#define INFINITY 5000 //Este valor representa uma distancia infinita entre 2 vértices, pois, 
                      //de início o Algoritmo de Dijkstra não sabe a distancia entre os vértices
#define LIST_EMPTY "List empty."
#define LIST_FULL "List fully."
#define DEBUG if(0)

using namespace std; 
using namespace chrono;

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
template <typename E> class List { // List ADT
    private:
        void operator =(const List&) {} // Protect assignment
        List(const List&) {} // Protect copy constructor
    public:
        List() {} // Default constructor
        virtual ~List() {} // Base destructor
        // Clear contents from the list, to make it empty.
        virtual void clear() = 0;
        // Insert an element at the current location.
        // item: The element to be inserted
        virtual void insert(const E& item) = 0;
        // Append an element at the end of the list.
        // item: The element to be appended.
        virtual void append(const E& item) = 0;
        // Remove and return the current element.
        // Return: the element that was removed.
        virtual E remove() = 0;
        // Set the current position to the start of the list
        virtual void moveToStart() = 0;
        // Set the current position to the end of the list
        virtual void moveToEnd() = 0;
        // Move the current position one step left. No change
        // if already at beginning.
        virtual void prev() = 0;
        // Move the current position one step right. No change
        // if already at end.
        virtual void next() = 0;
        // Return: The number of elements in the list.
        virtual int length() const = 0;
        // Return: The position of the current element.
        virtual int currPos() const = 0;
        // Set current position.
        // pos: The position to make current.
        virtual void moveToPos(int pos) = 0;
        // Return: The current element.
        virtual const E& getValue() const = 0;
};

template <typename E> class Link {
    public:
    E element; // Value for this node
    Link *next; // Pointer to next node in list
    // Constructors
    Link(const E& elemval, Link* nextval = NULL){
        element = elemval; next = nextval; 
        }
    Link(Link* nextval =NULL) { next = nextval; }
};

// Linked list implementation
template <typename E> class LList: public List<E> {
    private:
        Link<E>* head; // Pointer to list header
        Link<E>* tail; // Pointer to last element
        Link<E>* curr; // Access to current element
        int cnt; // Size of list
        void init() { // Intialization helper method
            curr = tail = head = new Link<E>;
            cnt = 0;
        }
        void removeall() { // Return link nodes to free store
            while(head != NULL) {
                curr = head;
                head = head->next;
                delete curr;
            }
        }
    public:
        LList(int size) { init(); } // Constructor
        ~LList() { removeall(); } // Destructor
        void print() const; // Print list contents
        void clear() { removeall(); init(); } // Clear list
        // Insert "it" at current position
        void insert(const E& it) {
            curr->next = new Link<E>(it, curr->next);
            if (tail == curr) tail = curr->next; // New tail
                cnt++;
        }
        void append(const E& it) { // Append "it" to list
            tail = tail->next = new Link<E>(it, NULL);
            cnt++;
        }
        // Remove and return current element
        E remove() {
            E it = curr->next->element; // Remember value
            Link<E>* ltemp = curr->next; // Remember link node
            if (tail == curr->next) tail = curr; // Reset tail
                curr->next = curr->next->next; // Remove from list
            delete ltemp; // Reclaim space
            cnt--; // Decrement the count
            return it;
        }
        void moveToStart() // Place curr at list start
            { curr = head; }
        void moveToEnd() // Place curr at list end
            { curr = tail; }
        // Move curr one step left; no change if already at front
        void prev() {
            if (curr == head) return; // No previous element
            Link<E>* temp = head;
        // March down list until we find the previous element
            while (temp->next!=curr) temp=temp->next;
                curr = temp;
        }
        // Move curr one step right; no change if already at end
        void next(){ 
            if (curr != tail) 
                curr = curr->next; 
        }
        int length() const { return cnt; } // Return length
        // Return the position of the current element
        int currPos() const {
            Link<E>* temp = head;
            int i;
            for (i=0; curr != temp; i++)
                temp = temp->next;
            return i;
        }
        // Move down list to "pos" position
        void moveToPos(int pos) {
            curr = head;
            for(int i=0; i<pos; i++) curr = curr->next;
        }
        const E& getValue() const { // Return current element
            return curr->next->element;
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

        // ~GraphL(){
        //     delete [] mark;
        //     for(int i = 0; i < numVertex; i++) 
        //         delete [] vertex[i];
        //     delete [] vertex;
        // }

        void init(int n){
            int i;
            numVertex = n;
            numEdge = 0;
            mark = new int[n];
            for(i = 0; i < numVertex; i++){                
                mark[i] = UNVISITED; ////Tem escrito assim no livro mas não compila
            }
            vertex = (List<Edge>**) new List<Edge>*[numVertex];
            for(i = 0; i < numVertex; i++){
                vertex[i] = new LList<Edge>(1);
            }
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
                if((vertex[v]->currPos()+1) < vertex[v]->length()){
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

int minUnvisited(Graph* G, int* D){
    int i, v = -1;
    // Initialize v to some unvisited vertex
    for (i=0; i<G->n(); i++){        
        if (G->getMark(i) == UNVISITED) { v = i; break; }
    }
    for (i++; i<G->n(); i++){   // Now find smallest D value
        if ((G->getMark(i) == UNVISITED) && (D[i] < D[v])){            
            v = i;
        }
    }
    return v;
}

//Function to find shortest path between two vertices using table vertex method.
//It's usable in the two graphs implementations.
void DijkstraTable(Graph* G, int* D, int start, int destination){
    //Inicializando as distancias e as marcações de visita para os vertices
    for (int i = 0; i < G -> n(); i++){
        D[i] = INFINITY;            
        G -> setMark(i, UNVISITED);
    }

    D[start] = 0; //A distancia para o vertice de inicio é 0, já que já estamos neste vertice
    int v;        //Vertice que será visitado e faremos os calculos das distancias

    while (G -> getMark(destination) == UNVISITED){
        v = minUnvisited(G, D);

        G -> setMark(v, VISITED);
        
        for(int j = G -> first(v); j < G -> n(); j = G -> next(v, j)){
            if((D[v] + G -> weight(v, j)) < D[j]){
                D[j] = (D[v] + G -> weight(v, j));
            }
        }
    }
}


class DijkstraPriorQueueList{
    private:
        int V; // número de vértices

        // ponteiro para um array contendo a lista de adjacência
        list<pair<int, int> > *adj;

    public:
        DijkstraPriorQueueList(int V){
            this->V = V; // atribui o número de vértices
            
            //cria as listas onde cada lista é uma lista de pairs
            //onde cada pair é formado pelo vértice destino e o custo
            adj = new list<pair<int, int> >[V];
        }

        // adiciona uma aresta ao grafo de v1 à v2
        void addAresta(int v1, int v2, int custo){
            adj[v1].push_back(make_pair(v2, custo));
        }

        // algoritmo de Dijkstra
        int dijkstra(int orig, int dest){
            int dist[V];    // vetor de distâncias

            //vetor de visitados serve para caso o vértice já tenha sido
            //expandido (visitado), não expandir mais            
            int visitados[V];

            // fila de prioridades de pair (distancia, vértice)
            priority_queue < pair<int, int>,
                        vector<pair<int, int> >, greater<pair<int, int> > > pq;

            // inicia o vetor de distâncias e visitados
            for(int i = 0; i < V; i++){
                dist[i] = INFINITY;
                visitados[i] = false;
            }

            dist[orig] = 0; // a distância de orig para orig é 0

            pq.push(make_pair(dist[orig], orig)); // insere na fila

            // loop do algoritmo
            while(!pq.empty()){
                pair<int, int> p = pq.top(); // extrai o pair do topo
                int u = p.second; // obtém o vértice do pair
                pq.pop(); // remove da fila

                // verifica se o vértice não foi expandido
                if(visitados[u] == false){
                    // marca como visitado
                    visitados[u] = true;

                    list<pair<int, int> >::iterator it;

                    // percorre os vértices "v" adjacentes de "u"
                    for(it = adj[u].begin(); it != adj[u].end(); it++){
                        // obtém o vértice adjacente e o custo da aresta
                        int v = it->first;
                        int custo_aresta = it->second;

                        // relaxamento (u, v)
                        if(dist[v] > (dist[u] + custo_aresta)){
                            // atualiza a distância de "v" e insere na fila
                            dist[v] = dist[u] + custo_aresta;
                            pq.push(make_pair(dist[v], v));
                        }
                    }
                }
            }

            // retorna a distância mínima até o destino
            return dist[dest];
        }
};


class DijkstraPriorQueueMatrix{
    private:
        int V; // número de vértices

        // ponteiro para um array contendo matriz de adjacência
        GraphM* graph;
    public:
        DijkstraPriorQueueMatrix(int V){
            this->V = V; // atribui o número de vértices
            graph = new GraphM(V);
        }

        // adiciona uma aresta ao grafo de v1 à v2
        void addAresta(int v1, int v2, int custo){
            graph->setEdge(v1, v2, custo);
        }

        // algoritmo de Dijkstra
        int dijkstra(int orig, int dest){
            int dist[V]; // vetor de distâncias

            //vetor de visitados serve para caso o vértice já tenha sido
            //expandido (visitado), não expandir mais
            int visitados[V];

            // fila de prioridades de pair (distancia, vértice)
            priority_queue < pair<int, int>,
                        vector<pair<int, int> >, greater<pair<int, int> > > pq;

            // inicia o vetor de distâncias e visitados
            for(int i = 0; i < V; i++){
                dist[i] = INFINITY;
                visitados[i] = false;
            }

            // a distância de orig para orig é 0
            dist[orig] = 0;

            // insere na fila
            pq.push(make_pair(dist[orig], orig));
            
            // loop do algoritmo
            while(!pq.empty()){
                pair<int, int> p = pq.top(); // extrai o pair do topo
                int u = p.second; // obtém o vértice do pair
                pq.pop(); // remove da fila

                // verifica se o vértice não foi expandido
                    if(visitados[u] == false){
                        // marca como visitado
                        visitados[u] = true;

                        //list<pair<int, int> >::iterator it;

                        // percorre os vértices "v" adjacentes de "u"
                        for (int v = graph -> first(u); v < graph-> n(); v = graph -> next(u, v)){
                            // obtém o vértice adjacente e o custo da aresta
                            int custo_aresta = graph -> weight(u, v);

                            // relaxamento (u, v)
                            if(dist[v] > (dist[u] + custo_aresta)){
                                // atualiza a distância de "v" e insere na fila
                                dist[v] = dist[u] + custo_aresta;
                                pq.push(make_pair(dist[v], v));
                            }
                        }
                }
            }

            // retorna a distância mínima até o destino
            return dist[dest];
        }
};

int main(){
    DijkstraPriorQueueMatrix graphPriorMatrix(9);   //Adjacency matrix graph who uses 
                                                    //dijkstra with priority queue method

    DijkstraPriorQueueList graphPriorList(9);       //Adjacency list graph who uses 
                                                    //dijkstra with priority queue method

    GraphM graphTableMatrix(9);                     //Adjacency matrix graph who uses
                                                    //dijkstra with table vertex method

    GraphL graphTableList(9);                       //Adjacency list graph who uses
                                                    //dijkstra with table vertex method

    //The start vertex, the destination vertex, and an array 
    //to store the distance of each vertex
    int start = 0, destination = 4, array[9];


    //Setting edges to make the graphs be sparse
    graphPriorMatrix.addAresta(0, 7, 8);
    graphPriorMatrix.addAresta(0, 1, 4);
    graphPriorMatrix.addAresta(7, 6, 1);
    graphPriorMatrix.addAresta(1, 7, 11);
    graphPriorMatrix.addAresta(1, 2, 8);
    graphPriorMatrix.addAresta(6, 5, 2);
    graphPriorMatrix.addAresta(5, 3, 14);
    graphPriorMatrix.addAresta(5, 4, 10);
    graphPriorMatrix.addAresta(7, 8, 7);
    graphPriorMatrix.addAresta(6, 8, 6);
    graphPriorMatrix.addAresta(2, 3, 7);
    graphPriorMatrix.addAresta(2, 5, 4);
    graphPriorMatrix.addAresta(3, 4, 9);

    graphPriorList.addAresta(0, 7, 8);
    graphPriorList.addAresta(0, 1, 4);
    graphPriorList.addAresta(7, 6, 1);
    graphPriorList.addAresta(1, 7, 11);
    graphPriorList.addAresta(1, 2, 8);
    graphPriorList.addAresta(6, 5, 2);
    graphPriorList.addAresta(5, 3, 14);
    graphPriorList.addAresta(5, 4, 10);
    graphPriorList.addAresta(7, 8, 7);
    graphPriorList.addAresta(6, 8, 6);
    graphPriorList.addAresta(2, 3, 7);
    graphPriorList.addAresta(2, 5, 4);
    graphPriorList.addAresta(3, 4, 9);

    graphTableMatrix.setEdge(0, 7, 8);
    graphTableMatrix.setEdge(0, 1, 4);
    graphTableMatrix.setEdge(7, 6, 1);
    graphTableMatrix.setEdge(1, 7, 11);
    graphTableMatrix.setEdge(1, 2, 8);
    graphTableMatrix.setEdge(6, 5, 2);
    graphTableMatrix.setEdge(5, 3, 14);
    graphTableMatrix.setEdge(5, 4, 10);
    graphTableMatrix.setEdge(7, 8, 7);
    graphTableMatrix.setEdge(6, 8, 6);
    graphTableMatrix.setEdge(2, 3, 7);
    graphTableMatrix.setEdge(2, 5, 4);
    graphTableMatrix.setEdge(3, 4, 9);
    
    graphTableList.setEdge(0, 7, 8);
    graphTableList.setEdge(0, 1, 4);
    graphTableList.setEdge(7, 6, 1);
    graphTableList.setEdge(1, 7, 11);
    graphTableList.setEdge(1, 2, 8);
    graphTableList.setEdge(6, 5, 2);
    graphTableList.setEdge(5, 3, 14);
    graphTableList.setEdge(5, 4, 10);
    graphTableList.setEdge(7, 8, 7);
    graphTableList.setEdge(6, 8, 6);
    graphTableList.setEdge(2, 3, 7);
    graphTableList.setEdge(2, 5, 4);
    graphTableList.setEdge(3, 4, 9);

    //Testing
    cout << "The minimum length from start to destination is: ";
    auto begin = chrono::steady_clock::now();
    cout << graphPriorMatrix.dijkstra(start, destination) << endl;
    auto end = chrono::steady_clock::now();

    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - begin).count()
        << " microsseconds" << endl << endl;


    cout << "The minimum length from start to destination is: ";
    begin = chrono::steady_clock::now();
    cout << graphPriorList.dijkstra(start, destination) << endl;
    end = chrono::steady_clock::now();

    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - begin).count()
        << " microsseconds" << endl;

    begin = chrono::steady_clock::now();            
    DijkstraTable(&graphTableMatrix, array, start, destination);
    end = chrono::steady_clock::now();

    cout << endl << "The minimum length from start to destination is: ";
    cout << array[destination] << endl;

    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - begin).count()
        << " microsseconds" << endl;

    //Reseting the array to use it again
    for(int i = 0; i < 9; i++){
        array[i] = 0;
    }

    begin = chrono::steady_clock::now();            
    DijkstraTable(&graphTableList, array, start, destination);
    end = chrono::steady_clock::now();

    cout << endl << "The minimum length from start to destination is: ";
    cout << array[destination] << endl;

    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - begin).count()
        << " microsseconds" << endl;

    //Reseting the array to use it again
    for(int i = 0; i < 9; i++){
        array[i] = 0;
    }

    //Setting edges to make the graphs be dense
    graphPriorMatrix.addAresta(0, 7, 8);
    graphPriorMatrix.addAresta(0, 1, 4);
    graphPriorMatrix.addAresta(0, 8, 1);
    graphPriorMatrix.addAresta(1, 7, 11);
    graphPriorMatrix.addAresta(1, 2, 8);
    graphPriorMatrix.addAresta(1, 8, 5);
    graphPriorMatrix.addAresta(1, 6, 12);
    graphPriorMatrix.addAresta(2, 3, 7);
    graphPriorMatrix.addAresta(2, 5, 4);
    graphPriorMatrix.addAresta(2, 8, 2);
    graphPriorMatrix.addAresta(3, 4, 9);
    graphPriorMatrix.addAresta(5, 3, 14);
    graphPriorMatrix.addAresta(5, 4, 10);
    graphPriorMatrix.addAresta(6, 5, 2);
    graphPriorMatrix.addAresta(6, 8, 6);
    graphPriorMatrix.addAresta(6, 2, 1);
    graphPriorMatrix.addAresta(6, 3, 3);
    graphPriorMatrix.addAresta(7, 6, 1);
    graphPriorMatrix.addAresta(7, 5, 5);
    graphPriorMatrix.addAresta(7, 8, 7);
    graphPriorMatrix.addAresta(8, 6, 6);
    graphPriorMatrix.addAresta(8, 3, 7);
    graphPriorMatrix.addAresta(8, 5, 14);

    graphPriorList.addAresta(0, 7, 8);
    graphPriorList.addAresta(0, 1, 4);
    graphPriorList.addAresta(0, 8, 1);
    graphPriorList.addAresta(1, 7, 11);
    graphPriorList.addAresta(1, 2, 8);
    graphPriorList.addAresta(1, 8, 5);
    graphPriorList.addAresta(1, 6, 12);
    graphPriorList.addAresta(2, 3, 7);
    graphPriorList.addAresta(2, 5, 4);
    graphPriorList.addAresta(2, 8, 2);
    graphPriorList.addAresta(3, 4, 9);
    graphPriorList.addAresta(5, 3, 14);
    graphPriorList.addAresta(5, 4, 10);
    graphPriorList.addAresta(6, 5, 2);
    graphPriorList.addAresta(6, 8, 6);
    graphPriorList.addAresta(6, 2, 1);
    graphPriorList.addAresta(6, 3, 3);
    graphPriorList.addAresta(7, 6, 1);
    graphPriorList.addAresta(7, 5, 5);
    graphPriorList.addAresta(7, 8, 7);
    graphPriorList.addAresta(8, 6, 6);
    graphPriorList.addAresta(8, 3, 7);
    graphPriorList.addAresta(8, 5, 14);

    graphTableMatrix.setEdge(0, 7, 8);
    graphTableMatrix.setEdge(0, 1, 4);
    graphTableMatrix.setEdge(0, 8, 1);
    graphTableMatrix.setEdge(1, 7, 11);
    graphTableMatrix.setEdge(1, 2, 8);
    graphTableMatrix.setEdge(1, 8, 5);
    graphTableMatrix.setEdge(1, 6, 12);
    graphTableMatrix.setEdge(2, 3, 7);
    graphTableMatrix.setEdge(2, 5, 4);
    graphTableMatrix.setEdge(2, 8, 2);
    graphTableMatrix.setEdge(3, 4, 9);
    graphTableMatrix.setEdge(5, 3, 14);
    graphTableMatrix.setEdge(5, 4, 10);
    graphTableMatrix.setEdge(6, 5, 2);
    graphTableMatrix.setEdge(6, 8, 6);
    graphTableMatrix.setEdge(6, 2, 1);
    graphTableMatrix.setEdge(6, 3, 3);
    graphTableMatrix.setEdge(7, 6, 1);
    graphTableMatrix.setEdge(7, 5, 5);
    graphTableMatrix.setEdge(7, 8, 7);
    graphTableMatrix.setEdge(8, 6, 6);
    graphTableMatrix.setEdge(8, 3, 7);
    graphTableMatrix.setEdge(8, 5, 14);

    graphTableList.setEdge(0, 7, 8);
    graphTableList.setEdge(0, 1, 4);
    graphTableList.setEdge(0, 8, 1);
    graphTableList.setEdge(1, 7, 11);
    graphTableList.setEdge(1, 2, 8);
    graphTableList.setEdge(1, 8, 5);
    graphTableList.setEdge(1, 6, 12);
    graphTableList.setEdge(2, 3, 7);
    graphTableList.setEdge(2, 5, 4);
    graphTableList.setEdge(2, 8, 2);
    graphTableList.setEdge(3, 4, 9);
    graphTableList.setEdge(5, 3, 14);
    graphTableList.setEdge(5, 4, 10);
    graphTableList.setEdge(6, 5, 2);
    graphTableList.setEdge(6, 8, 6);
    graphTableList.setEdge(6, 2, 1);
    graphTableList.setEdge(6, 3, 3);
    graphTableList.setEdge(7, 6, 1);
    graphTableList.setEdge(7, 5, 5);
    graphTableList.setEdge(7, 8, 7);
    graphTableList.setEdge(8, 6, 6);
    graphTableList.setEdge(8, 3, 7);
    graphTableList.setEdge(8, 5, 14);

    //Testing with dense graph
    cout << endl << "The minimum length from start to destination is: ";
    begin = chrono::steady_clock::now();
    cout << graphPriorMatrix.dijkstra(start, destination) << endl;
    end = chrono::steady_clock::now();

    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - begin).count()
        << " microsseconds" << endl << endl;


    cout << "The minimum length from start to destination is: ";
    begin = chrono::steady_clock::now();
    cout << graphPriorList.dijkstra(start, destination) << endl;
    end = chrono::steady_clock::now();

    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - begin).count()
        << " microsseconds" << endl;

    begin = chrono::steady_clock::now();            
    DijkstraTable(&graphTableMatrix, array, start, destination);
    end = chrono::steady_clock::now();

    cout << endl << "The minimum length from start to destination is: ";
    cout << array[destination] << endl;

    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - begin).count()
        << " microsseconds" << endl;

    //Reseting the array to use it again
    for(int i = 0; i < 9; i++){
        array[i] = 0;
    }

    begin = chrono::steady_clock::now();            
    DijkstraTable(&graphTableList, array, start, destination);
    end = chrono::steady_clock::now();

    cout << endl << "The minimum length from start to destination is: ";
    cout << array[destination] << endl;

    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - begin).count()
        << " microsseconds" << endl;

    return 0;
}