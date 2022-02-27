/*  Os objetivos deste programa é testar a eficiência de grafos em 3 situações:
    1 - grafo implementado com matriz de adjacência ou lista de adjacência;
    2 - algoritmo de Djikstra utilizando fila de prioridade ou tabela de distância de vértices;
    3 - usar grafos esparsos e densos
*/  
#include <iostream>
#define VISITED 1
#define UNVISITED 0
#define INFINITY 5000 //Este valor representa uma distancia infinita entre 2 vértices, pois, 
                      //de início o Algoritmo de Dijkstra não sabe a distancia entre os vértices
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

//Function to find shortest path between two vertices.
//It's usable in the two graphs implementations.
void DijkstraList(Graph* G, int* D, int start, int destination){
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


// Assert: If "val" is false, print a message and terminate
// the program
void Assert(bool val, string s) {
    if (!val) { // Assertion failed -- close the program
        cout << "Assertion Failed: " << s << endl;
        exit(-1);
    }
}


// Swap two elements in a generic array
template<typename E>
    inline void swap(E A[], int i, int j) {
        E temp = A[i];
        A[i] = A[j];
        A[j] = temp;
}


class DijkElem {
    public:
        int vertex, distance;
        DijkElem() { vertex = -1; distance = -1; }
        DijkElem(int v, int d) { vertex = v; distance = d; }
};


template <typename D> class DDComp{
    public:
        bool prior(D a, D b){
            if (a>b){return true;}
            return false;
        }
};


// Heap class
template <typename E, typename DDComp> class heap {
    private:
        E* Heap;
        // Pointer to the heap array
        int maxsize;
        // Maximum size of the heap
        int n;
        // Number of elements now in the heap
        // Helper function to put element in its correct place
        void siftdown(int pos) {
            while (!isLeaf(pos)) { // Stop if pos is a leaf
                int j = leftchild(pos); int rc = rightchild(pos);
                cout << "heap rc: "<<Heap[rc]<<", heap j: "<<Heap[j] << endl;
                if ((rc < n) && DDComp::prior(Heap[rc], Heap[j]))
                    j = rc;
                // Set j to greater child’s value
                if (DDComp::prior(Heap[pos], Heap[j])) return; // Done
                swap(Heap, pos, j);
                pos = j;
                // Move down
            }
        }
    public:
        heap(E* h, int num, int max)
        // Constructor
            { Heap = h; n = num; maxsize = max; buildHeap(); }
        int size() const
        // Return current heap size
            { return n; }
        bool isLeaf(int pos) const // True if pos is a leaf
            { return (pos >= n/2) && (pos < n); }
        int leftchild(int pos) const
            { return 2*pos + 1; }
        // Return leftchild position
        int rightchild(int pos) const
            { return 2*pos + 2; }
        // Return rightchild position
        int parent(int pos) const // Return parent position
            { return (pos-1)/2; }
        void buildHeap()
        // Heapify contents of Heap
            { for (int i=n/2-1; i>=0; i--) siftdown(i); }
        // Insert "it" into the heap
        void insert(const E& it) {
            Assert(n < maxsize, "Heap is full");
            int curr = n++;
            Heap[curr] = it;
            // Start at end of heap
            // Now sift up until curr’s parent > curr
            while ((curr!=0) &&
                        (DDComp::prior(Heap[curr], Heap[parent(curr)]))) {
                swap(Heap, curr, parent(curr));
                curr = parent(curr);
                }
        }
        // Remove first value
        E removefirst() {
            Assert (n > 0, "Heap is empty");
            swap(Heap, 0, --n);
            // Swap first with last value
            if (n != 0) siftdown(0); // Siftdown new root val
            return Heap[n];
            // Return deleted value
        }
        // Remove and return element at specified position
        E remove(int pos) {
            Assert((pos >= 0) && (pos < n), "Bad position");
            if (pos == (n-1)) n--; // Last element, no work to do
            else
            {
                swap(Heap, pos, --n);
                // Swap with last value
                while ((pos != 0) &&
                           (DDComp::prior(Heap[pos], Heap[parent(pos)]))) {
                    swap(Heap, pos, parent(pos)); // Push up large key
                    pos = parent(pos);
                }
                if (n != 0) siftdown(pos);
            // Push down small key
            }
            return Heap[n];
        }
};


// Dijkstra’s shortest paths algorithm with priority queue
void DijkstraListAdj(Graph* G, int* D, int s, int destination) {
    int i, v, w;
    // v is current vertex
    DijkElem temp;
    DijkElem E[G->e()];
    // Heap array with lots of space
    temp.distance = 0; temp.vertex = s;
    E[0] = temp;
    // Initialize heap array
    heap<DijkElem, DDComp> H(E, 1, G->e()); // Create heap
    // vector<int> H;
    // for (int j=0; j<G->e(); ++j){H[0]=1;}
    // make_heap(H.begin(), H.end());
    for (int i=0; i<G->n(); i++)
        // Initialize
        D[i] = INFINITY;
    D[0] = 0;
    for (i=0; i<G->n(); i++) {
    // Now, get distances
        do {
        if (H.size() == 0) return; // Nothing to remove
        temp = H.removefirst();
        v = temp.vertex;
        } while (G->getMark(v) == VISITED);
        G->setMark(v, VISITED);
        if (D[v] == INFINITY) return;
        // Unreachable vertices
        for (w=G->first(v); w<G->n(); w = G->next(v,w))
            if (D[w] > (D[v] + G->weight(v, w))) { // Update D
                D[w] = D[v] + G->weight(v, w);
                temp.distance = D[w]; temp.vertex = w;
                H.insert(temp);
                // Insert new distance in heap
            }
    }
}


int main(){
    cout << "ola" << endl;
    //GraphM grafoM(4);
    GraphL grafoL(9);
    
    grafoL.setEdge(0, 7, 8);
    grafoL.setEdge(0, 1, 4);
    grafoL.setEdge(7, 6, 1);
    grafoL.setEdge(1, 7, 11);
    grafoL.setEdge(1, 2, 8);
    grafoL.setEdge(6, 5, 2);
    grafoL.setEdge(5, 3, 14);
    grafoL.setEdge(5, 4, 10);
    grafoL.setEdge(7, 8, 7);
    grafoL.setEdge(6, 8, 6);
    grafoL.setEdge(2, 3, 7);
    grafoL.setEdge(2, 5, 4);
    grafoL.setEdge(3, 4, 9);

    int array[9], start = 0, destination = 4;
    
    DijkstraListAdj(&grafoL, array, start, destination);
    cout << endl;
    for(int i = 0; i<9; i++){
        cout << "Distance of vertex " << i << " to start vertex is: " << array[i] << endl;
    }

    cout << endl << "The minimum length from start to destination is: " << array[destination] << endl;
    //cout << "final"<<endl;
    // return 0;
    // int opt = 1;
    // while (opt!=0){
    //     cout<<"1 - Test graph with matrix of adjacency."<<endl;
    //     cout<<"2 - Test graph with list of adjacency."<<endl;
    //     cout<<"3 - Test graph with matrix of adjacency and algorithm of Dijsktra."<<endl;
    //     cout<<"4 - Test graph with list of adjacency and algorithm of Dijsktra."<<endl;
    //     cout<<"5 - Test with graph sparse."<<endl;
    //     cout<<"6 - Test with graph dense."<<endl;
    //     cout<<"0 - Exit."<<endl;
    //     cout << "Digit one option: ";
    //     cin >> opt;
    //     if (opt==1){
    //         return 1;
    //     }
    // }


    return 0;
}