//
// Created by Administrador on 11/18/2021.
//

#ifndef AED_1_DIRECTEDGRAPH_H
#define AED_1_DIRECTEDGRAPH_H

#include <string>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include "graph.h"
#include "Algorithms/dfs.h"

using namespace std;

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{
public:
    DirectedGraph() = default;
    bool insertVertex(string id, TV vertex) override;
    bool createEdge(string id1, string id2, TE w) override;
    bool deleteVertex(string id) override;
    bool deleteEdge(string id1, string id2) override;
    TE &operator()(string start, string end) override;
    float density() override;
    bool isDense(float threshold = 0.5) override;
    bool isConnected() override;
    bool isStronglyConnected() throw() override;
    bool empty() override;
    void clear() override;
    void displayVertex(string id) override;
    bool findById(string id) override;
    void display() override;
    int num_vertexes() override;
    int num_edges() override;
    int dijkstra(string from, string to) override;
};

template<typename TV, typename TE>
int DirectedGraph<TV,TE>::dijkstra(string from, string to) {
    if(findById(from) and findById(to)){
        unordered_map<Vertex<TV,TE>*,int> visited;
        int cost = 0;int less;

        auto route = this->vertexes.at(from);
        visited.insert({route,0});Vertex<TV,TE>* aux;
        cout<<route->data<<"-> ";

        while (aux->data != this->vertexes.at(to)->data){
            less = 999;
            for(auto x: route->edges){
                if(cost+x->weight < less and visited.find(x->vertexes[1]) == visited.end()){
                    aux = x->vertexes[1];less = cost + x->weight;
                } else{
                    cout<<"Upps, sin caminos"<<endl;
                    return 0;
                }
            }
            cout<<aux->data<<"-> ";route = aux;cost = less;
            visited.insert({route,0});
        }
        cout<<endl;return cost;
    } else{
        throw("No existe el vertice");
    }
}

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::insertVertex(string id, TV vertex){
    auto it = this->vertexes.find(id);//iterator buscador
    if(it!=this->vertexes.end())//Determinando si se repite el nuevo vertice
        return false;

    auto* NewVertex = new Vertex<TV,TE>;//Creación del nuevo vértice.
    NewVertex->data=vertex;

    //pair<string,Vertex<TV,TE>> nuevo (id, NewVertex);
    //this->vertexes.insert(nuevo);

    this->vertexes[id]=NewVertex;
    //this->num_vertex++;

    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::createEdge(string id1, string id2, TE w){
    //Si no existen los vértices
    if(this->vertexes.find(id1)==this->vertexes.end() || this->vertexes.find(id2)==this->vertexes.end())
        return false;

    //Si se inserta la misma arista con el mismo orden de vertices
    for(auto& temp1: this->vertexes[id1]->edges){
        if((temp1->vertexes[0]==this->vertexes[id1] && temp1->vertexes[1]==this->vertexes[id2]))
            return false;
    }

    auto* NewEdge = new Edge<TV,TE>;
    NewEdge->weight=w;
    //Asignando en la clase Edge los dos vértices pertenecientes
    NewEdge->vertexes[0] = this->vertexes[id1];
    NewEdge->vertexes[1] = this->vertexes[id2];
    //Asignando en el primer vertice la arista
    this->vertexes[id1]->edges.push_front(NewEdge);
    //this->num_edge++;

    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::deleteVertex(string id){
    if(this->vertexes.find(id)==this->vertexes.end())
        return false;

    for(auto & temp_vert: this->vertexes){//Buscndo la lista de vertices
        for(auto & temp_edge: temp_vert.second->edges){//De cada vertices revisamos sus aristas
            if(temp_edge->vertexes[0]==this->vertexes[id]){//Cada arista tiene dos vertices, comprobamos si el primero es lo que necesitamos eliminar
                temp_vert.second->edges.remove(temp_edge);//Removemos la arista de la lista de aristas de cada vertice
                temp_edge = nullptr;
                delete temp_edge;
                break;
            }
            if(temp_edge->vertexes[1] == this->vertexes[id]){
                temp_vert.second->edges.remove(temp_edge);
                temp_edge = nullptr;
                delete temp_edge;
                break;
            }
        }
    }

    this->vertexes[id]->edges.clear();
    delete this->vertexes[id];
    this->vertexes.erase(id);
    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::deleteEdge(string id1, string id2){
    //si los vertices no existen
    if(this->vertexes.find(id1)==this->vertexes.end() || this->vertexes.find(id2)==this->vertexes.end())
        return false;

    for(auto& temp_edge: this->vertexes[id1]->edges){
        //Si la arista existe en direccion id1->id2
        if(temp_edge->vertexes[0]==this->vertexes[id1] && temp_edge->vertexes[1]==this->vertexes[id2]){
            this->vertexes[id1]->edges.remove(temp_edge);
            this->vertexes[id2]->edges.remove(temp_edge);
        }
        break;
    }
    return true;
}

template<typename TV, typename TE>
TE &DirectedGraph<TV,TE>::operator()(string start, string end){
    //si los vertices no existen
    if(this->vertexes.find(start)==this->vertexes.end() || this->vertexes.find(end)==this->vertexes.end())
        throw("Uno o dos vértices no existe");

    //Validando la conexión en cualquier orden de los vertices
    for(auto& temp_edge: this->vertexes[start]->edges){
        if(temp_edge->vertexes[0]==this->vertexes[start] and temp_edge->vertexes[1]==this->vertexes[end])
            return temp_edge->weight;
    }

    throw("No existe conexión alguna entre los vértices");
}

template<typename TV, typename TE>
float DirectedGraph<TV,TE>::density(){
    float result=0;
    result = (float)(this->num_edges())/(this->num_vertexes()*(this->num_vertexes()-1));
    return result;
}

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::isDense(float threshold) {
    if(density()<threshold)
        return true;
    else
        return false;
}


template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::isConnected(){
    if(empty())
        throw("Grafo vacío");
    else{
        Dfs<TV,TE> dfs(this, this->vertexes.begin()->first);
        auto vector = dfs.apply();
        if(this->vertexes.size() == vector.size()){
            return true;
        }
    }
    return false;
}

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::isStronglyConnected() throw(){
    for(auto & temp:this->vertexes){
        Dfs<TV,TE> dfs(this,temp.first);
        auto vector= dfs.apply();
        if(vector.size() != this->vertexes.size()){
            return false;
        }
    }
    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::empty(){
    if(num_vertexes()==0)
        return true;
    else
        return false;
}

template<typename TV, typename TE>
void DirectedGraph<TV,TE>::clear() {
    while(!this->vertexes.empty()){
        auto i = *this->vertexes.begin();
        deleteVertex(i.first);
    }
}

template<typename TV, typename TE>
void DirectedGraph<TV,TE>::displayVertex(string id){
    if(this->vertexes.find(id)==this->vertexes.end())
        throw("No existe el vertice");
    else
        cout<<"Id("<<id<<"): "<<this->vertexes[id]->data<<endl;
}

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::findById(string id) {
    if(this->vertexes.find(id)!=this->vertexes.end())
        return true;
    else
        return false;
}

template<typename TV, typename TE>
void DirectedGraph<TV,TE>::display() {
    if(empty())
        throw("Grafo vacío");
    else{
        for(auto & temp:this->vertexes){
            cout<<"Id: "<<temp.first<<" - Value: "<<temp.second->data<<endl;
            cout<<"Edges: "<<endl;
            for(auto const& temp1: temp.second->edges){
                cout<<"   {"<<temp1->vertexes[0]->data<<", "<<temp1->vertexes[1]->data<<"}  Peso: "<<temp1->weight<<endl;
            }
            cout<<endl;
        }
    }

}

template<typename TV, typename TE>
int DirectedGraph<TV,TE>::num_vertexes(){
    this->num_vertex = this->vertexes.size();
    return this->num_vertex;
}

template<typename TV, typename TE>
int DirectedGraph<TV,TE>::num_edges(){
    this->num_edge = 0;
    for(auto & temp_vert: this->vertexes){
        this->num_edge += temp_vert.second->edges.size();
    }
    return this->num_edge;
}

#endif //AED_1_DIRECTEDGRAPH_H
