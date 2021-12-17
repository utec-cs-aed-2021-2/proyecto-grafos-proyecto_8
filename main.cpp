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
using namespace std;



template <typename TV, typename TE>
DirectedGraph<TV, TE> openDirectedGraph(string source,bool enableTest = false) {
    string line;vector<string> nodes_for_tests;string obj;
    DirectedGraph<TV, TE> about_;ifstream myfile(source, ifstream::in);
    if (myfile.is_open()) {
        while (getline(myfile, line)) { obj += line; }
        myfile.close();
    } else { throw("Error al abrir archivo, verifique ubicacion.");}


    const std::string rawJson = obj;
    const auto rawJsonLength = static_cast<int>(rawJson.length());
    constexpr bool shouldUseOldWay = false;
    JSONCPP_STRING err;
    Json::Value root;
    Json::Value root_1, root_2, aux;

    if (shouldUseOldWay) {
        Json::Reader reader;
        reader.parse(rawJson, root);
    } else {
        Json::CharReaderBuilder builder;

        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root, &err)) {
            std::cout << "error" << std::endl;throw("Error al abrir archivo, verifique caracteristicas.");
        }

        root_1 = root["nodes"];
        for (auto const &id: root_1.getMemberNames()) {
            nodes_for_tests.push_back(id);
            about_.insertVertex(id, root_1[id].asInt());
        }

        root_2 = root["connections"];
        for (auto const &id: root_2.getMemberNames()) {
            aux = root_2[id];for (auto const &id_: aux.getMemberNames()) {about_.createEdge(id, id_, aux[id_].asInt());}
        }


    }

    if(enableTest){
        cout<<"->"<<source<<endl;
        cout<<"\t Dijkstra: "<<*nodes_for_tests.begin()<<" to "<<*--nodes_for_tests.end()<<endl;
        about_.dijkstra(*nodes_for_tests.begin(), *--nodes_for_tests.end());
    }
    return about_;
}
template <typename TV, typename TE>
UnDirectedGraph<TV, TE> openUnDirectedGraph(string source,bool enableTest = false) {
    string line;vector<string> nodes_for_tests;
    string obj;UnDirectedGraph<TV, TE> about_;
    ifstream myfile(source, ifstream::in);
    if (myfile.is_open()) {
        while (getline(myfile, line)) { obj += line; }
        myfile.close();
    } else { throw("Error al abrir archivo, verifique ubicacion."); }


    const std::string rawJson = obj;
    const auto rawJsonLength = static_cast<int>(rawJson.length());
    constexpr bool shouldUseOldWay = false;
    JSONCPP_STRING err;
    Json::Value root;
    Json::Value root_1, root_2, aux;

    if (shouldUseOldWay) {
        Json::Reader reader;
        reader.parse(rawJson, root);
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
            nodes_for_tests.push_back(id);
            about_.insertVertex(id, root_1[id].asInt());
        }

        root_2 = root["connections"];
        for (auto const &id: root_2.getMemberNames()) {
            aux = root_2[id];
            for (auto const &id_: aux.getMemberNames()) {
                about_.createEdge(id, id_, aux[id_].asInt());
            }
        }
    }

    if(enableTest){
        cout<<"->"<<source<<endl;
        cout<<"\t Dijkstra: "<<*nodes_for_tests.begin()<<" to "<<*--nodes_for_tests.end()<<endl;
        about_.dijkstra(*nodes_for_tests.begin(), *--nodes_for_tests.end());
    }
    return about_;
}
void loadingFromJsonFile(){
    openDirectedGraph<char,int>("C:/Users/Administrador/CLionProjects/AED_1/G2D.json", true);
    openUnDirectedGraph<char, int>("C:/Users/Administrador/CLionProjects/AED_1/G1UD.json", true);
    openUnDirectedGraph<char, int>("C:/Users/Administrador/CLionProjects/AED_1/G4UD.json", true);
    openDirectedGraph<char, int>("C:/Users/Administrador/CLionProjects/AED_1/G6D.json", true);
    openUnDirectedGraph<char, int>("C:/Users/Administrador/CLionProjects/AED_1/G7UD.json", true);
    openDirectedGraph<char, int>("C:/Users/Administrador/CLionProjects/AED_1/G9D.json", true);
}
int main() {
    loadingFromJsonFile();

    return 0;
}
