#include <iostream>

#include <iostream>
#include <unordered_map>
#include <forward_list>
#include <vector>
#include <list>
#include "Graph/UndirectedGraph.h"
#include "Graph/DirectedGraph.h"
#include <fstream>
#include <string>
#include "dist/json/json.h"
#include "dist/jsoncpp.cpp"
using namespace std;


template <typename TV, typename TE>
DirectedGraph<TV, TE> openDirectedGraph(string source) {
    string line;
    string obj;
    DirectedGraph<TV, TE> about_;
    ifstream myfile(source, ifstream::in);
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
            std::cout << "error" << std::endl;
            throw("Error al abrir archivo, verifique caracteristicas.");
        }

        root_1 = root["nodes"];
        for (auto const &id: root_1.getMemberNames()) {
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
    return about_;
}

template <typename TV, typename TE>
UnDirectedGraph<TV, TE> openUnDirectedGraph(string source) {
    string line;
    string obj;
    UnDirectedGraph<TV, TE> about_;
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
    } else {
        Json::CharReaderBuilder builder;
        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root, &err)) {
            std::cout << "error" << std::endl;
            throw("Error al abrir archivo, verifique caracteristicas.");
        }

        root_1 = root["nodes"];
        for (auto const &id: root_1.getMemberNames()) {
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
    return about_;
}

void loadingFromJsonFile(){
    openDirectedGraph<char,int>("C:/Users/Administrador/CLionProjects/AED_1/G2D.json");
    openUnDirectedGraph<char, int>("C:/Users/Administrador/CLionProjects/AED_1/G1UD.json");
    openDirectedGraph<char, int>("C:/Users/Administrador/CLionProjects/AED_1/G3D.json");
    openUnDirectedGraph<char, int>("C:/Users/Administrador/CLionProjects/AED_1/G4UD.json");
    openDirectedGraph<char, int>("C:/Users/Administrador/CLionProjects/AED_1/G5D.json");
    openDirectedGraph<char, int>("C:/Users/Administrador/CLionProjects/AED_1/G6D.json");
    openUnDirectedGraph<char, int>("C:/Users/Administrador/CLionProjects/AED_1/G7UD.json");
    openUnDirectedGraph<char, int>("C:/Users/Administrador/CLionProjects/AED_1/G8UD.json");
    openDirectedGraph<char, int>("C:/Users/Administrador/CLionProjects/AED_1/G9D.json");
    
}

int main() {
    

    loadingFromJsonFile();

    dg.display();
    cout<<"------"<<endl;
    udg.display();

    return 0;
}
