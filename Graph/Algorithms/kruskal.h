#ifndef AED_1_KRUSKAL_H
#define AED_1_KRUSKAL_H

#include "../UndirectedGraph.h"
#include <vector>
#include <queue>
#include <unordered_set>

template <typename T>
class DisjoinSetTree{
private:
    struct Node{
        T data;
        int parent;
        int rank;
    };
    //vector<Node*> nodes;
    Node **nodes;
    int count;
public:
    DisjoinSetTree(vector<T> data){
        this->nodes = new Node*[data.size()];
        this->count = data.size();
        for(int i=0;i<data.size();i++){
            MakeSet(i, data[i]);
        }
    }

    void MakeSet(int x, T data){
        Node* node = new Node();
        node->data=data;
        node->rank = 0;
        node->parent = x;
        this->nodes[x] = node;
    }

    int Find(int x){
        if(x<0 || x>=this->count)throw("Error");
        if(this->nodes[x]->parent ==x) return x;
        else Find(this->nodes[x]->parent);
    }

    void Union(int x, int y){
        int xRoot = Find(x);
        int yRoot = Find(y);
        if(xRoot == yRoot){
            return;
        }
        auto rankx = nodes[xRoot]->rank;
        auto ranky = nodes[yRoot]->rank;
        if(rankx < ranky)
            this->nodes[xRoot]->parent = yRoot;
        else if(rankx > ranky)
            this->nodes[yRoot]->parent = xRoot;
        else{
            this->nodes[yRoot]->parent =xRoot;
            this->nodes[xRoot]->rank++;
        }
    }
    int sets(){
        int ns=0;
        for(int i=0;i<this->count;i++){
            if(this->nodes[i]->parent == i)
                ns++;
        }
        return ns;
    }

};


template<typename TV,typename TE>
class Kruskal{
public:
    UnDirectedGraph<TV, TE> Graph;

    Kruskal(UnDirectedGraph<TV, TE> *grafo){
        this->Graph = *grafo;
    }

    UnDirectedGraph<TV, TE> apply() {
        auto result = new UnDirectedGraph<TV,TE>();


        auto edge_compare = [](Edge<TV, TE>* e1, Edge<TV, TE>* e2) {return e1->weight > e2->weight;};//lambda para ordenar las aristas
        priority_queue<Edge<TV, TE>*, vector<Edge<TV, TE>*>, decltype(edge_compare)> Available_edges(edge_compare);//Ordenamos las aristas del grafo

        unordered_map<Vertex<TV, TE>*, int> ids_int;//Estructura para almacenar id's en tipo int con respecto a su vértice
        unordered_map<Vertex<TV, TE>*, string> ids_string;//Estructura para almacenar id's en tipo string con respecto a su vértice
        vector<Vertex<TV, TE>*> vecVertex;//Vector de vértices

        //Agregando vertices a vecVertex;
        for(auto& temp: Graph.vertexes) {
            vecVertex.push_back(temp.second);
        }

        int k=0;
        //Ordnenando las arista de menor a mayor.
        for(auto& temp_vert: Graph.vertexes){
            ids_int[temp_vert.second] = k;//llenamos la estructura ids_int
            ids_string[temp_vert.second] = temp_vert.first;//llenamos la estructura ids_string
            for(auto& temp_edge:temp_vert.second->edges){//Agregamos las aristas
                Available_edges.push(temp_edge);
            }
            k++;
        }

        //1. Creamos un DisjoinSetTree en donde se hará MakeSet a todos los vértices
        auto *ds = new DisjoinSetTree<Vertex<TV, TE> *>(vecVertex);

        //2. Recorremos todos los vértices disponibles
        while(!Available_edges.empty()){
            //2.1. Escogemos la arista de menor peso
            auto edge_choose = Available_edges.top();
            //2.2. Lo eliminamos de las aristas disponibles
            Available_edges.pop();
            //2.3 Verificamos si ambos vértices de la arista son de diferentes conjuntos
            if(ds->Find(ids_int[edge_choose->vertexes[0]]) != ds->Find(ids_int[edge_choose->vertexes[1]])){
                //2.3.1. Creamos los vértices para el nuevo grafo
                result->insertVertex(ids_string[edge_choose->vertexes[0]], edge_choose->vertexes[0]->data);
                result->insertVertex(ids_string[edge_choose->vertexes[1]], edge_choose->vertexes[1]->data);
                //2.3.2. Insertamos uan arista entre ellos
                result->createEdge(ids_string[edge_choose->vertexes[0]], ids_string[edge_choose->vertexes[1]],edge_choose->weight);

                //2.3.3 Unimos en un solo conjunto a los dos vértices.
                ds->Union(ds->Find(ids_int[edge_choose->vertexes[0]]), ds->Find(ids_int[edge_choose->vertexes[1]]));
            }
        }

        return *result;
    }

};

#endif //AED_1_KRUSKAL_H
