//
// Created by isaac on 17/12/2021.
//

#ifndef MAIN_CPP_FLOYD_WARSHALL_H
#define MAIN_CPP_FLOYD_WARSHALL_H

#include "graph.h"
#include "DirectedGraph.h"
#include <vector>
#include <queue>

#include <string>

#define INF 9999

template<typename TV,typename TE>
class Floyd_Warshall{
public:
    DirectedGraph<TV, TE> Graph;
    string id_start;
    string id_finish;

    //Iniciar un Prim ...(1)
    Floyd_Warshall(DirectedGraph<TV, TE> *grafo, string init_, string finish_){
        this->Graph = *grafo;
        this->id_start = init_;
        this->id_finish = finish_;
    }

    void apply() {
        auto result = new DirectedGraph<TV, TE>();

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




        /*
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
        }*/

    }

};

#endif //MAIN_CPP_FLOYD_WARSHALL_H
