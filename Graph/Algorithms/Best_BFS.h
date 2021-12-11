//
// Created by Lucasino20 on 7/12/2021.
//

#ifndef PROYECTO_GRAFOS_PROYECTO_8_BEST_BFS_H
#define PROYECTO_GRAFOS_PROYECTO_8_BEST_BFS_H


#include "graph.h"
#include <queue>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;


template<typename TV , typename TE>
struct Heuristica{
    TE distancia;
    Vertex<TV , TE> * vertice;
    Vertex<TV , TE> * padres;

    explicit Heuristica(Vertex<TV , TE> * vertice){
        this->vertice = vertice;
        distancia = 0;
        padres = nullptr;
        /*    Heuristica(Vertex<TV , TE> * vertice): vertice(vertice) , distancia(0) , padres(nullptr){}*/
    }

};

template<typename TV , typename TE>
struct Heuristica_menor{
    bool operator()(Heuristica<TV ,TE> * first , Heuristica<TV , TE>* second){
        return first->distancia > second->distancia;
    }
};

template<typename TV , typename TE>
Vertex<TV , TE> * find_d(Edge<TV , TE>* edge , Vertex<TV , TE>* temporal){
  if(edge->vertexes[0]->data == temporal->data){
    return edge->vertexes[1];
  }
  return edge->vertexes[0];
}




template<class TV , class TE>
class Best_BFS {

public:
    Graph<TV, TE> *graph;
    string inicio;
    string final;

    Best_BFS( Graph<TV , TE>* graph ,  string inicio  ,  string final )
    : graph(graph) , inicio(inicio) , final(final){}

    Heuristica<TV , TE> *verificacion (Vertex<TV , TE> * vertice1 , vector<Heuristica<TV , TE> * > final_temporal){
        for(Heuristica<TV , TE> * temp : final_temporal){
            if(temp->vertice == vertice1){
                return temp;
            }
        }
        return nullptr;
    }

    vector<TV> apply();

};

template<typename TV, typename TE>
vector<TV> Best_BFS<TV, TE>::apply() {


    map<Vertex<TV , TE>* , bool > visitados;
    vector<Heuristica<TV , TE> *> preresultado;

    priority_queue<Heuristica<TV , TE> *  , vector< Heuristica<TV , TE> *> , Heuristica_menor<TV ,TE> > pQueue;

    Vertex<TV , TE> * inicio_vertex = graph->vertexes[inicio];
    Vertex<TV , TE> * final_vertex = graph->vertexes[final];


    // Inicializar la cola de prioridad con el nodo de inicio.
    pQueue.push(new Heuristica<TV , TE>(inicio_vertex));
    visitados[inicio_vertex] = true;


    // Realizar el algoritmo de busqueda de la ruta perfecta hasta que la cola de prioridad quede vacia
    while (!pQueue.empty()){
        Heuristica<TV , TE> * temp = pQueue.top();
        preresultado.push_back(temp);

        pQueue.pop();

        // Condicion para hallar el nodo final
        if(temp->vertice == final_vertex){
            Heuristica<TV , TE> * temp2 = temp;
            vector<TV> resultado;


            while(temp2 != nullptr){
                resultado.push_back(temp2->vertice->data);
                temp2 = verificacion(temp2->padres , preresultado);
            }

            reverse(resultado.begin() , resultado.end());
            return resultado;
        }

        // Elegir el nodo de menor distacia de entre todos
        for (Edge<TV , TE> * arista : temp->vertice->edges) {


            Vertex<TV , TE> * temp_edge =  find_d(arista , temp->vertice);

            //Verificar si el nodo ya estuvo a los visitados y en la cola  , si no ingresarlo a la cola
            auto it = visitados.find(temp_edge);
            if(it == visitados.end()){
                visitados[temp_edge] = true;
                auto * temp_final = new Heuristica<TV ,TE>(temp_edge);
                temp_final->distancia = arista->weight;
                temp_final->padres = temp->vertice;

                pQueue.push(temp_final);
            }

        }
    }

    return {};
}


#endif //PROYECTO_GRAFOS_PROYECTO_8_BEST_BFS_H
