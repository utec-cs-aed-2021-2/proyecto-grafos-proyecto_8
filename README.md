[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=6293280&assignment_repo_type=AssignmentRepo)
# Algoritmos y Estructura de Datos
## Proyecto sobre Grafos
--------

## Integrantes
- Brhandon Gutierrez
- Isaac Vera
- Aaron Santamaria

----

El proyecto del curso consiste en implementar una estructura de datos de grafo y un file parser. La estructura debe soportar los métodos y algoritmos descritos a continuacion:  


## Graph data structure

* El grafo debe ser dinámico (inserciones. eliminaciones, búsquedas, ...)
* Se debe implementar los dos tipos de grafos: dirigidos y no-dirigidos.
* No considerar loops ni multi-arista. 


### Methods:
```cpp
bool insertVertex(string id, V data); // Creates a new vertex in the graph with some data and an ID

bool createEdge(string start, string end, E data); // Creates a new edge in the graph with some data

bool deleteVertex(string id); // Deletes a vertex in the graph

bool deleteEdge(string start, string end); // Deletes an edge in the graph, it is not possible to search by the edge value, since it can be repeated

E &operator()(string start, string end); // Gets the value of the edge from the start and end vertexes

float density() const; // Calculates the density of the graph

bool isDense(float threshold = 0.5) const; // Calculates the density of the graph, and determine if it is dense dependening on a threshold value

bool isConnected(); // Detect if the graph is connected

bool isStronglyConnected() throw(); // Detect if the graph is strongly connected (only for directed graphs)

bool empty(); // If the graph is empty

void clear(); // Clears the graph
```

### Algorithms:
```cpp
//Given the graph
UndirectedGraph<char, int> graph;

//1-Kruskal - Generates a MST graph using the Kruskal approach (only for undirected graphs)
Kruskal<char, int> kruskal(&graph);
UndirectedGraph<char, int> result = kruskal.apply();//return a tree

//2-Prim Generates a MST graph using the Prim approach (only for undirected graphs)
Prim<char, int> prim(&graph, "A");
UndirectedGraph<char, int> result = prim.apply();//return a tree

//3- A *
AStar<char, int> astar(&graph, "A", "Z", vector<int> heuristics);
UndirectedGraph<char, int> result = astar.apply();

//4- Bellman Ford
Bellman_Ford<char, int> bellman_ford = Bellman_Ford(&graph, "A");
pair<unordered_map<string, int>, unordered_map<string, string>> result = bellman_ford.apply();

//5- Best BFS
Best_BFS<char, int> best_bfs = Best_BFS(&graph, "A" , "Z");
vector<int> result = Best_BFS.apply();

//6- BFS
BFS<string, int> bfs = BFS(&graph, "A" );
vector<Vertex <string , int> *> result = BFS.apply();

//7- DFS
Dfs<string, int> dfs = Dfs(&graph, "A" );
vector<Vertex <string , int> *> result = Dfs.apply();

//8- Dijkstra - Find the minimum path between two nodes.
template<typename TV, typename TE>
int UnDirectedGraph<TV,TE>::dijkstra(string from, string to);


```


## JSON file parser
* Construye un grafo a partir de una archivo JSON de aereopuertos del mundo. 


### Methods:
```cpp
// NOTE: each derived class has its own readJSON method
template <typename TV, typename TE>
DirectedGraph<TV, TE> openDirectedGraph(string source); // Adds the parsed data into the specified directed graph

template <typename TV, typename TE>
UnDirectedGraph<TV, TE> openUnDirectedGraph(string source); // Adds the parsed data into the specified undirected graph
```
### Additional considerations:
* This projects needs an additional library, because there's no native support for JSON in C++.
* This projects uses: https://github.com/open-source-parsers/jsoncpp
* These additional files: "dist/json/json.h" and "dist/jsoncpp.cpp" are from the library.
* Download the zip library
* Place on desktop
* Execute the file amalgamate.py contained in the library with Administrator privileges.
* The last step will create dist folder in the library. Select and copy in the same folder as main.cpp
* That's all!

## [Git Karma Guidelines](http://karma-runner.github.io/5.2/dev/git-commit-msg.html)

```
<type>(<scope>): <subject>

<body>
```

### Allowed ```<type>``` values

* feat (new feature for the user, not a new feature for build script)
* fix (bug fix for the user, not a fix to a build script)
* docs (changes to the documentation)
* style (formatting, missing semi colons, etc)
* refactor (refactoring production code, eg. renaming a variable)
* test (adding missing tests, refactoring tests)
* chore (updating grunt tasks etc)

### Allowed ```<scope>``` values

* graph
* directedGraph
* undirectedGraph
* parser
* main
* tester


> **PD:** Puntos extras sobre Evaluación Continua si se implementa una GUI.


> **PD1:** Para esta primera entrega hace falta la implementacón de "kruskal", la cual nos comprometemos a hacerlo en un máximo de una semana.
