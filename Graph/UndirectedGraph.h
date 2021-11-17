#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"
#include <string>
#include <deque>
#include <unordered_set>

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{
public:
    UnDirectedGraph() = default;
    bool insertVertex(string id, TV vertex) override;
    bool createEdge(string id1, string id2, TE w) override;
    bool deleteVertex(string id) override;
    bool deleteEdge(string id1, string id2) override;
    TE &operator()(string start, string end) override;
    float density() override;
    bool isDense(float threshold = 0.5) override;
    bool isConnected() override;
    bool isStronglyConnected() override;
    bool empty() override;
    void clear() override;
    void displayVertex(string id) override;
    bool findById(string id) override;
    void display() override;
    vector<Vertex<TV, TE>*> dfs(string id) override;
    int num_vertexes() override;
    int num_edges() override;
};

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::insertVertex(string id, TV vertex){
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
vector<Vertex<TV, TE>*> UnDirectedGraph<TV,TE>::dfs(string id){
    deque<Vertex<TV, TE>*> ans;
    deque<Vertex<TV, TE>*> visited;
    vector<Vertex<TV, TE>*> result;

    auto temp = this->vertexes.at(id);
    ans.push_back(this->vertexes.at(id));
    result.push_back(this->vertexes.at(id));
    while (!ans.empty()){
        //Obtener los EDGES ordenador menor a mayor

        bool counter = false;
        int cuentame = 0;

        //Iterar los EDGES ORDENADOR verificando si estan en visitados
        for (auto it = begin(temp->edges); it != end(temp->edges); it++) {
            // Acumular resultado
            for (int i = 0; i < result.size(); ++i) {
                if(result[i]->data == temp->data){break;}
                if(i == result.size()-1 and result[i]->data != temp->data){result.push_back(temp);}
            }

            if(((*it)->vertexes[0]->data == temp->data) ?  existAtVisited(visited, (*it)->vertexes[1]):existAtVisited(visited, (*it)->vertexes[0])){
                //Si esta en visitados
                cuentame+=1;
                if((*it)->vertexes[0]->data == temp->data){
                    visited.push_back((*it)->vertexes[0]);
                } else {
                    visited.push_back((*it)->vertexes[1]);
                }

            } else{
                cuentame = 0;

                // Si no esta agregamos y cambiamos el temp
                if((*it)->vertexes[0]->data == temp->data){
                    ans.push_back(temp);
                    visited.push_back(temp);
                    temp = (*it)->vertexes[1];
                    break;
                } else {
                    if(temp->edges.size() == 1){counter = true;break;}
                    ans.push_back(temp);
                    visited.push_back(temp);
                    temp = (*it)->vertexes[0];
                    break;
                }
            }

        }

        // Si todos estan en visitados eliminamos de ans y cambiamos el temp
        if(counter or cuentame == temp->edges.size()){
            ans.pop_front();
            temp = ans.back();
            counter = false;
            cuentame=0;
        }


    }


    return result;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::createEdge(string id1, string id2, TE w){
    //Si no existen los vértices
    if(this->vertexes.find(id1)==this->vertexes.end() || this->vertexes.find(id2)==this->vertexes.end())
        return false;

    //Si se inserta la misma arista pero con los vértices invertidos o mimo vértices
    for(auto& temp1: this->vertexes[id1]->edges){
        if((temp1->vertexes[0]==this->vertexes[id1] && temp1->vertexes[1]==this->vertexes[id2]) ||
           (temp1->vertexes[0]==this->vertexes[id2] && temp1->vertexes[1]==this->vertexes[id1]))
            return false;
    }

    auto* NewEdge_1 = new Edge<TV,TE>;
    NewEdge_1->weight=w;
    //Asignando en la clase Edge los dos vértices pertenecientes
    NewEdge_1->vertexes[0] = this->vertexes[id1];
    NewEdge_1->vertexes[1] = this->vertexes[id2];
    //Asignando en la clase Vertex las aristas a las cuales pertenece

    auto* NewEdge_2 = new Edge<TV,TE>;
    NewEdge_2->weight=w;
    //Asignando en la clase Edge los dos vértices pertenecientes
    NewEdge_2->vertexes[0] = this->vertexes[id2];
    NewEdge_2->vertexes[1] = this->vertexes[id1];

    this->vertexes[id1]->edges.push_front(NewEdge_1);
    this->vertexes[id2]->edges.push_front(NewEdge_2);
    //this->num_edge++;

    return true;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::deleteVertex(string id){
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
bool UnDirectedGraph<TV,TE>::deleteEdge(string id1, string id2){
    if(this->vertexes.find(id1)==this->vertexes.end() || this->vertexes.find(id2)==this->vertexes.end())
        return false;

    for(auto temp_edge: this->vertexes[id1]->edges){
        if((temp_edge->vertexes[0]==this->vertexes[id1] && temp_edge->vertexes[1]==this->vertexes[id2]) ||
           (temp_edge->vertexes[0]==this->vertexes[id2] && temp_edge->vertexes[1]==this->vertexes[id1])){
            this->vertexes[id1]->edges.remove(temp_edge);
            this->vertexes[id2]->edges.remove(temp_edge);
        }
        break;
    }
    return true;
}

template<typename TV, typename TE>
TE &UnDirectedGraph<TV,TE>::operator()(string start, string end){
    //si los vertices no existen
    if(this->vertexes.find(start)==this->vertexes.end() || this->vertexes.find(end)==this->vertexes.end())
        throw("Uno o dos vértices no existe");

    //Validando la conexión en cualquier orden de los vertices
    for(auto temp_edge: this->vertexes[start]->edges){
        if((temp_edge->vertexes[0]==this->vertexes[start] and temp_edge->vertexes[1]==this->vertexes[end])||
           (temp_edge->vertexes[0]==this->vertexes[end] and temp_edge->vertexes[1]==this->vertexes[start]))
            return temp_edge->weight;
    }

    throw("No existe conexión alguna entre los vértices");
}

template<typename TV, typename TE>
float UnDirectedGraph<TV,TE>::density(){
    float result=0;
    result = (float)(2*this->num_edges())/(this->num_vertexes()*(this->num_vertexes()-1));
    return result;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::isDense(float threshold) {
    if(density()<threshold)
        return true;
    else
        return false;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::isConnected(){
    if(empty())
        throw("Grafo vacío");
    else{

        if(this->vertexes.size() == dfs(this->vertexes.begin()->first).size()){
            return true;
        }
    }
    return false;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::isStronglyConnected(){
    if(empty())
        throw("Grafo vacío");
    else{
        for(auto & temp:this->vertexes){
            if(temp.second->edges.size() != this->vertexes.size()-1){
                return false;
            }
        }
    }
    return true;
    
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::empty(){
    if(num_vertexes()==0)
        return true;
    else
        return false;
}

template<typename TV, typename TE>
void UnDirectedGraph<TV,TE>::clear() {
    while(!this->vertexes.empty()){
        auto i = *this->vertexes.begin();
        deleteVertex(i.first);
    }
}

template<typename TV, typename TE>
void UnDirectedGraph<TV,TE>::displayVertex(string id){
    if(this->vertexes.find(id)==this->vertexes.end())
        throw("No existe el vertice");
    else
        cout<<"Id("<<id<<"): "<<this->vertexes[id]->data<<endl;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::findById(string id) {
    if(this->vertexes.find(id)!=this->vertexes.end())
        return true;
    else
        return false;
}

template<typename TV, typename TE>
void UnDirectedGraph<TV,TE>::display() {
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
int UnDirectedGraph<TV,TE>::num_vertexes(){
    this->num_vertex = this->vertexes.size();
    return this->num_vertex;
}

template<typename TV, typename TE>
int UnDirectedGraph<TV,TE>::num_edges(){
    this->num_edge = 0;
    for(auto & temp_vert: this->vertexes){
        this->num_edge += temp_vert.second->edges.size();
    }
    this->num_edge/=2;
    return this->num_edge;
}

#endif
