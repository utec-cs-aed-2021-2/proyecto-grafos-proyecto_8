//
// Created by Administrador on 12/17/2021.
//

#ifndef AED_1_FLOYD_WARSHALL_H
#define AED_1_FLOYD_WARSHALL_H
#include "../graph.h"
#include "../DirectedGraph.h"
#include <vector>
#include <queue>

#include <string>

#define INF 99999

template<typename TV,typename TE>
class Floyd_Warshall{
public:
    DirectedGraph<TV, TE> Graph;
    TV id_start;
    TV id_finish;

    //Iniciar un Prim ...(1)
    Floyd_Warshall(DirectedGraph<TV, TE> *grafo, TV init_, TV finish_){
        this->Graph = *grafo;
        this->id_start = init_;
        this->id_finish = finish_;
    }

    DirectedGraph<TV,TE> apply() {
        auto result = new DirectedGraph<TV, TE>();

        unordered_map<TV,string> value_ids;
        unordered_map<Vertex<TV, TE>*, string> ids;

        for(auto& temp: Graph.vertexes)//Para entrada con valor del nodo
            value_ids[temp.second->data] = temp.first;

        //Creando las matrices de distancia y recorrido
        int matriz_distance[Graph.num_vertexes()][Graph.num_vertexes()];
        int matriz_recorrido[Graph.num_vertexes()][Graph.num_vertexes()];

        for(int i=0;i<Graph.num_vertexes();i++){
            for(int j=0;j<Graph.num_vertexes();j++){
                if(i==j){
                    matriz_distance[i][j] = 0;
                    matriz_recorrido[i][j] = 0;
                }else{
                    for(auto& temp: Graph.vertexes[to_string(i+1)]->edges){
                        if(temp->vertexes[1]->data == Graph.vertexes[to_string(j+1)]->data){
                            matriz_distance[i][j] = temp->weight;
                            break;
                        }
                        else
                            matriz_distance[i][j] = INF;
                    }
                    matriz_recorrido[i][j] = j+1;
                }
            }
        }

        for(int k=0;k<Graph.num_vertexes();k++){
            for(int i=0;i<Graph.num_vertexes();i++){
                for(int j=0;j<Graph.num_vertexes();j++){
                    if(matriz_distance[i][k] + matriz_distance[k][j] < matriz_distance[i][j]){
                        matriz_distance[i][j] = matriz_distance[i][k] + matriz_distance[k][j];
                        matriz_recorrido[i][j] = k+1;
                    }
                }
            }
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //Armando el grafo dirigido de salida en base a las matrices.
        auto vx = value_ids[id_start];
        auto vy = value_ids[id_finish];
        int total_recorrido = matriz_distance[stoi(vx)-1][stoi(vy)-1];
        if(total_recorrido== INF)
            throw("No existe camino entre estos dos nodos");

        stack<string> nodos_ids;
        nodos_ids.push(vy);//insertamos al stack el nodo de llegada
        int aux_1 = stoi(vy)-1;
        while(1){
            string aux = to_string(matriz_recorrido[stoi(vx)-1][aux_1]);
            if(stoi(aux)==aux_1+1)
                break;
            nodos_ids.push(aux);
            aux_1 = stoi(aux)-1;
        }

        result->insertVertex(value_ids[id_start],id_start);
        auto a = value_ids[id_start];
        while(!nodos_ids.empty()){
            string b = nodos_ids.top();
            result->insertVertex(b,Graph.vertexes[a]->data);
            result->createEdge(a,b,matriz_distance[atoi(a.c_str())-1][atoi(b.c_str())-1]);
            a = b;
            nodos_ids.pop();

        }
        /* Imprimir matrices
        cout<<endl;

        for(int i=0; i<Graph.num_vertexes();i++){
            for(int j=0;j<Graph.num_vertexes();j++){
                if(matriz_distance[i][j] == INF)
                    cout<<"INF"<<" ";
                else
                    cout<<matriz_distance[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        for(int i=0; i<Graph.num_vertexes();i++){
            for(int j=0;j<Graph.num_vertexes();j++){
                if(matriz_recorrido[i][j]==INF)
                    cout<<"INF"<<" ";
                else
                    cout<<matriz_recorrido[i][j]<<" ";
            }
            cout<<endl;
        }
        */
        return *result;
    }

};

#endif //AED_1_FLOYD_WARSHALL_H
