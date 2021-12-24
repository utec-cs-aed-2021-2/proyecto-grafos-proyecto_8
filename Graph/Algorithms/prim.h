#ifndef AED_1_PRIM_H
#define AED_1_PRIM_H

#include "../UndirectedGraph.h"
#include <queue>
#include <unordered_set>

//Prim<char, int> prim(&graph, "A");....(1)
//UndirectedGraph<char, int> result = prim.apply();....(2)

template<typename TV,typename TE>
class Prim{
public:
    UnDirectedGraph<TV,TE> Graph;
    TV id_start;

    //Iniciar un Prim ...(1)
    Prim(UnDirectedGraph<TV,TE> *grafo, TV id_){
        this->Graph = *grafo;
        id_start= id_;
    }

    UnDirectedGraph<TV,TE> apply(){
        auto result = new UnDirectedGraph<TV,TE>();

        auto edge_compare = [](Edge<TV, TE>* e1, Edge<TV, TE>* e2) {return e1->weight > e2->weight;};//lambda para ordenar las aristas
        priority_queue<Edge<TV, TE>*, vector<Edge<TV, TE>*>, decltype(edge_compare)> Available_edges(edge_compare);//Ordenamos las aristas adyacentes de un vértice

        unordered_set<Vertex<TV, TE>*> visited;//Estructura en donde serán ingresados los vértices visitados
        auto is_visited = [&visited](Vertex<TV, TE>* vx) { return visited.find(vx) != end(visited); };//Lambda para saber si un nodo ya ha sido visitado

        unordered_map<TV,string> value_ids; //Estructura que almacena el valor del vértice y el id de este;
        unordered_map<Vertex<TV, TE>*, string> ids;//Estructura para conseguir el indice de un vertice

        for(auto& temp: Graph.vertexes)//Llenamos la estructura value_ids
            value_ids[temp.second->data] = temp.first;

        for(auto& temp_vert: Graph.vertexes)//llenamos la estructura ids
            ids[temp_vert.second] = temp_vert.first;

        //1. Elegimos el vertice
        auto vx = Graph.vertexes[value_ids[id_start]];

        //2. Agregamos el vértice en visitados y agregamos los aristas
        visited.insert(vx);

        //3. Agregamos todas las aristas adyacentes del vértice al priority queue
        for(auto &temp_edge: vx->edges){
            Available_edges.push(temp_edge);
        }

        //4. Recorremos las "aristas disponibles" mientras no esté vacío
        while(!Available_edges.empty()){
            //4.1. Tomar el top()(la arista con menor peso)
            auto edge_choose = Available_edges.top();
            //4.2. Remover la arista elegida de los "disponibles"
            Available_edges.pop();
            //4.3 Verificar si el vértice adyacente no ha sido visitado
            auto vert_ad = edge_choose->vertexes[1];//vertice adyacente
            //cout<<vert_ad->data<<endl;
            if(!is_visited(vert_ad)){
                //4.3.1. Agregar vertice adjacente a visitados
                visited.insert(vert_ad);
                //4.3.2. Agrego la arista en el grafo
                result->insertVertex(ids[vert_ad],vert_ad->data);
                result->insertVertex(ids[edge_choose->vertexes[0]],edge_choose->vertexes[0]->data);
                result->createEdge(ids[vert_ad], ids[edge_choose->vertexes[0]],edge_choose->weight);
                //4.3.3. Agregamos las aristas disponibles adyacentes del vértice adyacente
                for(auto& temp_adj: vert_ad->edges){
                    Available_edges.push(temp_adj);
                }
            }
        }
        return *result;
    }

};

#endif //AED_1_PRIM_H
