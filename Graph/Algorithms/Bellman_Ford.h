#ifndef PROYECTO_GRAFOS_PROYECTO_8_BELLMAN_FORD_H
#define PROYECTO_GRAFOS_PROYECTO_8_BELLMAN_FORD_H

#include <string>
#include "../graph.h"
#include "../DirectedGraph.h"

template<typename TV , typename TE>
class Bellman_Ford {
public:
    DirectedGraph<TV , TE>* graph;string origen;
    Bellman_Ford(DirectedGraph<TV , TE>* _graph , string _origen){
        this->graph = _graph;this->origen = _origen;
    }
    pair<unordered_map<string , int > , unordered_map<string , string>> apply();
};

template<typename TV, typename TE>
pair<unordered_map<string, int>, unordered_map<string, string>> Bellman_Ford<TV, TE>::apply() {


    unordered_map<string , int> distancia;
    unordered_map<Vertex<TV , TE>* , string> vert;
    unordered_map<string , string> predecesor;

    //inicializamos el grafo.Ponemos distancias a INFINITO menos el nodo origen
    //que tiene distancia 0

    for (auto  &vertex : graph->vertexes ){
        distancia[vertex.first] = INT_MAX; // INT_MAX usado para dar un valor tipo infinito a cada distancia
        vert[vertex.second] = vertex.first;
    }

    distancia[origen] = 0;

    //Almacenando las aristas del grafo
    vector<Edge<TV , TE> * > aristas;
    for (auto &vertex : graph->vertexes) {
        if(vertex.second != nullptr){
            for(auto &arista : vertex.second->edges){
                bool done = false;
                for (int i = 0; i < aristas.size(); ++i) {
                    if(aristas[i] == arista){done = true;break;}
                }
                if(!done){aristas.push_back(arista);}
            }
        }

    }

    // Aplicando el algoritmo

    for(int i = 0 ; i < graph->num_vertexes() - 1 ; ++i){
        for(auto arista : aristas){
            if(distancia[vert[arista->vertexes[0]]] != INT_MAX){
                int actuliza_distancia = distancia[vert[arista->vertexes[0]]] + arista->weight;
                // Verificar si la distacia hacia un nodo es menor para actualizar
                if(distancia[vert[arista->vertexes[1]]] > actuliza_distancia){
                    distancia[vert[arista->vertexes[1]]] = actuliza_distancia;
                    predecesor[vert[arista->vertexes[1]]] = vert[arista->vertexes[0]];
                }

            }
        }
    }




    return make_pair(distancia , predecesor);




}


#endif //PROYECTO_GRAFOS_PROYECTO_8_BELLMAN_FORD_H