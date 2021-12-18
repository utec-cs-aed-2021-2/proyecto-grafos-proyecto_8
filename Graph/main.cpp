#include <iostream>
#include <unordered_map>
#include <forward_list>
#include <vector>
#include <list>
#include "UndirectedGraph.h"
#include "DirectedGraph.h"
#include <fstream>
#include <string>
#include "dist/json/json.h"
#include "dist/jsoncpp.cpp"

#include "Algorithms/bfs.h"
#include "Algorithms/dfs.h"
#include "Algorithms/kruskal.h"
#include "Algorithms/prim.h"
#include "Algorithms/Best_BFS.h"
#include "Algorithms/Bellman_Ford.h"
#include "Algorithms/floyd_warshall.h"
using namespace std;



template <typename TV, typename TE>
DirectedGraph<TV, TE>* openDirectedGraph(string source,bool enableTest = false) {
    string line;vector<string> nodes_for_tests;string obj;
    DirectedGraph<TV, TE>* about_ = new DirectedGraph<TV,TE>();ifstream myfile(source, ifstream::in);
    if (myfile.is_open()) {
        while (getline(myfile, line)) { obj += line; }myfile.close();
    } else { throw("Error al abrir archivo, verifique ubicacion.");}
    const std::string rawJson = obj;const auto rawJsonLength = static_cast<int>(rawJson.length());
    constexpr bool shouldUseOldWay = false;JSONCPP_STRING err;
    Json::Value root;Json::Value root_1, root_2, aux;
    if (shouldUseOldWay) {
        Json::Reader reader;
        reader.parse(rawJson, root);
    }
    else {
        Json::CharReaderBuilder builder;
        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root, &err)) {
            std::cout << "error" << std::endl;throw("Error al abrir archivo, verifique caracteristicas.");
        }
        root_1 = root["nodes"];
        for (auto const &id: root_1.getMemberNames()) {
            nodes_for_tests.push_back(id);about_->insertVertex(id, root_1[id].asInt());
        }
        root_2 = root["connections"];
        for (auto const &id: root_2.getMemberNames()) {
            aux = root_2[id];for (auto const &id_: aux.getMemberNames()) {about_->createEdge(id, id_, aux[id_].asInt());}
        }


    }



    if(enableTest){
        cout<<"->"<<source<<endl;
        cout<<"\t:___DIJKSTRA__: "<<*nodes_for_tests.begin()<<" to "<<*--nodes_for_tests.end()<<endl;
        cout<<"\t\t";about_->dijkstra(*nodes_for_tests.begin(), *--nodes_for_tests.end());

        cout<<"\t:___BELLMAN FORD___:"<<endl;
        Bellman_Ford<char,int> bellmanFord = Bellman_Ford<char,int>(about_, *nodes_for_tests.begin());
        pair<unordered_map<string,int>,unordered_map<string, string>> result = bellmanFord.apply();
        cout<<"\t\t";cout << "Distances: \n";
        for (auto& key: result.first) {
            cout<<"\t\t\t";cout << key.first << ": " << key.second << std::endl;
        }
        cout<<"\t\t";cout << "Parents: \n";
        for (auto& key: result.second) {
            cout<<"\t\t\t";cout << key.first << ": " << key.second << std::endl;
        }

        cout<<"\t___BEST BFS___: "<<endl;
        Best_BFS<char,int> bestBfs = Best_BFS<char,int>(about_,*nodes_for_tests.begin(), *--nodes_for_tests.end());
        vector<int> result_2 = bestBfs.apply();
        cout<<"\t\t";for(auto x:result_2){cout<<x<<"->";}cout<<endl;

        cout<<"\t:___DFS___:"<<endl;
        Dfs<char,int> dfs = Dfs<char,int>(about_, *--nodes_for_tests.end());
        vector<Vertex<char, int>*> result_3 = dfs.apply();
        cout<<"\t\t";for(auto x:result_3){cout<<x->data<<" -> ";}cout<<endl;

        cout<<"\t:___BFS___:"<<endl;
        BFS<char,int> bfs = BFS<TV,TE>(about_, *nodes_for_tests.begin());
        vector<Vertex<char, int>*> result_4 = dfs.apply();
        cout<<"\t\t";for(auto x:result_4){cout<<x->data<<"->";}cout<<endl;

        cout<<"\t:___FLOYD WARSHALL___:"<<endl;
        Floyd_Warshall<char, int> floydWarshall(about_, *nodes_for_tests.begin(), *--nodes_for_tests.end());
        vector<Vertex<char, int>*> result_5 = floydWarshall.apply();
        cout<<"\t\t";for(auto x:result_5){cout<<x->data<<"->";}cout<<endl;


    }
    return about_;
}


template <typename TV, typename TE>
UnDirectedGraph<TV, TE>* openUnDirectedGraph(string source,bool enableTest = false) {
    string line;vector<string> nodes_for_tests;
    string obj;
    UnDirectedGraph<TV, TE> *about_ = new UnDirectedGraph<TV,TE>();
    ifstream myfile(source, ifstream::in);
    if (myfile.is_open()) {
        while (getline(myfile, line)) { obj += line; }myfile.close();
    } else { throw("Error al abrir archivo, verifique ubicacion."); }
    const std::string rawJson = obj;const auto rawJsonLength = static_cast<int>(rawJson.length());
    constexpr bool shouldUseOldWay = false;JSONCPP_STRING err;Json::Value root;Json::Value root_1, root_2, aux;
    if (shouldUseOldWay){
        Json::Reader reader;reader.parse(rawJson, root);
    }
    else {
        Json::CharReaderBuilder builder;
        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root, &err)) {
            std::cout << "error" << std::endl;
            throw("Error al abrir archivo, verifique caracteristicas.");
        }
        root_1 = root["nodes"];
        for (auto const &id: root_1.getMemberNames()) {
            nodes_for_tests.push_back(id);about_->insertVertex(id, root_1[id].asInt());
        }
        root_2 = root["connections"];
        for (auto const &id: root_2.getMemberNames()) {
            aux = root_2[id];
            for (auto const &id_: aux.getMemberNames()) {
                about_->createEdge(id, id_, aux[id_].asInt());
            }
        }
    }

    if(enableTest){
        cout<<"->"<<source<<endl;
        cout<<"\t:___DIJKSTRA___: "<<*nodes_for_tests.begin()<<" to "<<*--nodes_for_tests.end()<<endl;
        cout<<"\t\t";about_->dijkstra(*nodes_for_tests.begin(), *--nodes_for_tests.end());

        cout<<"\t:___KRUSKAL___: "<<endl;
        Kruskal<char, int> kruskal(about_);
        UnDirectedGraph<TV,TE> result = kruskal.apply();
        result.display();

        cout<<"\t:___PRIM___:"<<endl;
        Prim<char, int> prim(about_, *nodes_for_tests.begin());
        UnDirectedGraph<TV,TE> result_1 = prim.apply();
        result_1.display();

        cout<<"\t___BEST BFS___: "<<endl;
        Best_BFS<char,int> bestBfs = Best_BFS<char,int>(about_,*nodes_for_tests.begin(), *--nodes_for_tests.end());
        vector<int> result_2 = bestBfs.apply();
        cout<<"\t\t";for(auto x:result_2){cout<<x<<"->";}cout<<endl;

        cout<<"\t:___DFS___:"<<endl;
        Dfs<char,int> dfs = Dfs<char,int>(about_, *nodes_for_tests.begin());
        vector<Vertex<char, int>*> result_3 = dfs.apply();
        cout<<"\t\t";for(auto x:result_3){cout<<x->data<<"->";}cout<<endl;

        cout<<"\t:___BFS___:"<<endl;
        BFS<char,int> bfs = BFS<TV,TE>(about_, *--nodes_for_tests.end());
        vector<Vertex<char, int>*> result_4 = dfs.apply();
        cout<<"\t\t";for(auto x:result_4){cout<<x->data<<"->";}cout<<endl;
    }
    return about_;
}


void loadingFromJsonFile(string path){
    openUnDirectedGraph<char, int>(path + "G1UD.json", true);
    openDirectedGraph<char,int>(path + "G2D.json", true);
    openDirectedGraph<char, int>(path + "G3D.json", true);
    openUnDirectedGraph<char, int>(path + "G4UD.json", true);
    openUnDirectedGraph<char, int>(path + "G5D.json", true);
    openDirectedGraph<char, int>(path + "G6D.json", true);
    openUnDirectedGraph<char, int>(path + "G7UD.json", true);
    openUnDirectedGraph<char, int>(path + "G8UD.json", true);
    openDirectedGraph<char, int>(path + "G9D.json", true);
}
int main() {
    //Especifica la ruta de los archivos JSON
    string path = "C:/Users/Administrador/CLionProjects/AED_1/";
    loadingFromJsonFile(path);

    return 0;
}
