#ifndef DFS_H
#define DFS_H

#include "graph.h"
#include <queue>
#include <vector>
#include <stack>

template<typename TV,typename TE>
class Dfs{
public:
    Graph<TV,TE>* graph;
    string id_start;

    Dfs(Graph<TV,TE> *grafo, string id_){
        this->graph = grafo;
        id_start= id_;
    }

    bool existAtVisited(const deque<Vertex<TV, TE>*> visited, Vertex<TV,TE>* it){
        for (int i = 0; i < visited.size(); ++i) {
            if(visited[i]->data == it->data){
                return true;
            }
        }
        return false;
    }

    vector<Vertex<TV, TE>*> apply() {
        vector<Vertex<TV,TE>*> result;
        unordered_map<Vertex<TV,TE>*,bool> visited;
        auto it = this->graph->vertexes.begin();
        while (it != this->graph->vertexes.end()){
            visited[it->second] = false;
            it++;
        }
        stack<Vertex<TV,TE>*> stack;

        stack.push(this->graph->vertexes[this->id_start]);

        while(!stack.empty()){
            Vertex<TV,TE>* vert = stack.top();
            stack.pop();

            if(!visited[vert]){
                result.push_back(vert);
                visited[vert] = true;
            }

            for(auto it = vert->edges.begin(); it != vert->edges.end();++it){
                if(!visited[(*it)->vertexes[1]]){
                    stack.push((*it)->vertexes[1]);
                }
                if(!visited[(*it)->vertexes[0]]){
                    stack.push((*it)->vertexes[0]);
                }
            }
        }
        return result;
    }
};


#endif