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

    //Iniciar un Prim ...(1)
    Kruskal(UnDirectedGraph<TV, TE> *grafo){
        this->Graph = *grafo;
    }

    UnDirectedGraph<TV, TE> apply() {
        auto result = new UnDirectedGraph<TV,TE>();
        //1. Ordenar las aristas
        auto edge_compare = [](Edge<TV, TE>* e1, Edge<TV, TE>* e2) {return e1->weight > e2->weight;};
        priority_queue<Edge<TV, TE>*, vector<Edge<TV, TE>*>, decltype(edge_compare)> Available_edges(edge_compare);

        unordered_map<Vertex<TV, TE>*, int> ids_int;
        unordered_map<Vertex<TV, TE>*, string> ids_string;
        vector<Vertex<TV, TE>*> vecVertex;

        //Agregando vertices a vecVertex;
        for(auto& temp: Graph.vertexes) {
            vecVertex.push_back(temp.second);
        }
        int k=0;
        //Ordnenando las arista de menor a mayor.
        for(auto& temp_vert: Graph.vertexes){
            ids_int[temp_vert.second] = k;
            ids_string[temp_vert.second] = temp_vert.first;
            for(auto& temp_edge:temp_vert.second->edges){
                Available_edges.push(temp_edge);
            }
            k++;
        }

        auto *ds = new DisjoinSetTree<Vertex<TV, TE> *>(vecVertex);//Conjunto de vertices con makeset

        while(!Available_edges.empty()){
            auto edge_choose = Available_edges.top();
            Available_edges.pop();
            if(ds->Find(ids_int[edge_choose->vertexes[0]]) != ds->Find(ids_int[edge_choose->vertexes[1]])){
                result->insertVertex(ids_string[edge_choose->vertexes[0]], edge_choose->vertexes[0]->data);
                result->insertVertex(ids_string[edge_choose->vertexes[1]], edge_choose->vertexes[1]->data);
                result->createEdge(ids_string[edge_choose->vertexes[0]], ids_string[edge_choose->vertexes[1]],edge_choose->weight);

                ds->Union(ds->Find(ids_int[edge_choose->vertexes[0]]), ds->Find(ids_int[edge_choose->vertexes[1]]));
            }
        }

        return *result;
    }

};

#endif //AED_1_KRUSKAL_H
