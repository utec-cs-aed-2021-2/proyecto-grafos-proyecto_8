#ifndef AED_1_PRIM_H
#define AED_1_PRIM_H

#include "../UndirectedGraph.h"
#include <queue>
#include <unordered_set>

template<typename TV,typename TE>
class Prim{
public:
    UnDirectedGraph<TV,TE> Graph;
    string id_start;
    Prim(UnDirectedGraph<TV,TE> *grafo, string id_){
        this->Graph = *grafo;
        id_start= id_;
    }

    UnDirectedGraph<TV,TE> apply(){
        auto result = new UnDirectedGraph<TV,TE>();
        auto edge_compare = [](Edge<TV, TE>* e1, Edge<TV, TE>* e2) {return e1->weight > e2->weight;};
        priority_queue<Edge<TV, TE>*, vector<Edge<TV, TE>*>, decltype(edge_compare)> Available_edges(edge_compare);
        unordered_map<Vertex<TV, TE>*, string> ids;
        unordered_set<Vertex<TV, TE>*> visited;
        //lambda
        auto is_visited = [&visited](Vertex<TV, TE>* vx) { return visited.find(vx) != end(visited); };

        for(auto& temp_vert: Graph.vertexes)
            ids[temp_vert.second] = temp_vert.first;

        //1. Elegimos el vertice
        auto vx = Graph.vertexes[id_start];

        //2. Agregamos el vértice en visitados y agregamos los aristas
        visited.insert(vx);

        for(auto &temp_edge: vx->edges){
            Available_edges.push(temp_edge);
        }

        //3. Recorrer las "aristas disponibles" mientras no esté vacío
        while(!Available_edges.empty()){
            //3.1. Tomar el top()(la arista con menor peso)
            auto edge_choose = Available_edges.top();
            //3.2. Remover la arista elegida de los "disponibles"
            Available_edges.pop();
            //3.3 Verificar si el vértice adyacente no ha sido visitado
            auto vert_ad = edge_choose->vertexes[1];//vertice adyacente
            //cout<<vert_ad->data<<endl;
            if(!is_visited(vert_ad)){
                //3.3.1. Agregar vertice adjacente a visitados
                visited.insert(vert_ad);
                //3.3.2. Agrego la arista en el grafo
                result->insertVertex(ids[vert_ad],vert_ad->data);
                result->insertVertex(ids[edge_choose->vertexes[0]],edge_choose->vertexes[0]->data);
                result->createEdge(ids[vert_ad], ids[edge_choose->vertexes[0]],edge_choose->weight);
                //3.3.3. Agregamos las aristas disponibles adyacentes del vértice adyacente
                for(auto& temp_adj: vert_ad->edges){
                    Available_edges.push(temp_adj);
                }
            }
        }
        return *result;
    }
};

#endif //AED_1_PRIM_H
