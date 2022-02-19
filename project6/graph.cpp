/*  Os objetivos deste programa é testar a eficiência de grafos em 3 situações:
    1 - grafo implementado com matriz de adjacência ou lista de adjacência;
    2 - algoritmo de Djikstra utilizando fila de prioridade ou tabela de distância de vértices;
    3 - usar grafos esparsos e densos
*/  
#include <iostream>

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
    E List(){

    };

};

template <typename E>
class LList: public List{
    E LList(){

    };

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
                //mark[i] = UNVISITED; //Tem escrito assim no livro mas não compila
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
                //mark[i] = UNVISITED ////Tem escrito assim no livro mas não compila
            }
            vertex = (List<Edge>**) new List<Edge>*[numVertex];
            for(i = 0; i < numVertex; i++)
                vertex[i] = new LList<Edge>();
        }

        int n() {return numVertex;}
        int e() {return numEdge;}

        int first(int v){
            if(vertex[v] -> lenght() == 0){
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
                    vertex[i] -> currPos() < vertex[i] -> lenght();
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
                vertex[i] -> currPos() < vertex[i] -> lenght();
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


//Class graph with list adjacency and algorithm off Dijsktra:
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
class GraphLDijsktra: public GraphM{
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


    return 0;
}