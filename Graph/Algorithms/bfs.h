#ifndef AED_1_BFS_H
#define AED_1_BFS_H

#include <unordered_map>
#include <queue>
#include "../graph.h"
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"


template<typename T , typename V>
class BFS{
public:
    Graph<T, V> *graph;
    string start_id;
    BFS(Graph<T, V> *graph, string vertex) {
        this->graph = graph;
        this->start_id = vertex;
    }
    vector<Vertex<T , V>*> apply();
};

template<typename T, typename V>
vector<Vertex<T, V> *> BFS<T, V>::apply() {
    if(!this->graph->isConnected()){
        throw("BFS no aplica");
    }

    vector<Vertex<T, V> *> resultado;

    unordered_map<Vertex<T, V>* , bool> visitados;

    auto it = this->graph->vertexes.begin();
    while (it != this->graph->vertexes.end()) {
        visitados[it->second] = false;
        it++;
    }

    std::list<Vertex<T, V> *> cola;
    visitados[this->graph->vertexes[this->start_id]] = true;

    cola.push_back(this->graph->vertexes[this->start_id]);


    while(!cola.empty()){
        Vertex<T , V>* temp = cola.front();

        resultado.push_back(temp);

        cola.pop_back();

        for(auto it = temp->edges.begin() ; it != temp->edges.end() ; ++it){
            if(!visitados[(*it)->vertexes[0]]){
                visitados[(*it)->vertexes[0]] = true;
                cola.push_back((*it)->vertexes[0]);
            }

            if(!visitados[(*it)->vertexes[1]]){
                visitados[(*it)->vertexes[1]] = true;
                cola.push_back((*it)->vertexes[1]);
            }
        }
    }

    return resultado;
}

#endif //AED_1_BFS_H
