/*
There are flight paths between cities. If there is a flight between city A and city B then there is an edge between the cities. The cost of the edge can be the time that flight take to reach city B from A, or the amount of fuel used for the journey Represent this as a graph. The node can be represented by airport name or name of the city Use adjacency list representation of the graph or use adjacency matrix representation of the graph
*/

#include<iostream>
using namespace std;
#define M 10

class Graph{
    int V;
    int mat[M][M];
    string cities[M];
    void setCities();
    void clearGraph();
    void addEdge(int, int);

public:
    Graph(int);
    void createGraph();
    void connectivity();
    void print();
};

Graph::Graph(int v){
    V = v;
    cout << "Graph of " << V << " vertices has been created.\n";

    setCities();
    clearGraph();
    createGraph();
}

void Graph::setCities(){
    cout << "Enter airport names.\n";
    for (int i = 0; i < V;i++){
        cout << "Airport " << i << " : ";
        cin >> cities[i];
    }
    cout << "Destinations stored successfully.\n";
}
void Graph::clearGraph(){
    for (int i = 0; i < V;i++){
        for (int j = 0; j < V;j++){
            mat[i][j] = 0;
        }
    }
}

void Graph::addEdge(int i,int j){
    cout << "Is there a flight between '" << cities[i] << "' and '" << cities[j] << "' ? ";
    char ch;
    cin >> ch;
    if(ch=='y' || ch=='Y') {
        cout << "Enter fuel requiered for transportation : ";
        cin >> mat[i][j];
        mat[j][i] = mat[i][j];
    }
}

void Graph::createGraph(){
    for (int i = 0; i < V - 1;i++){
        for (int j = i + 1; j < V;j++){
            addEdge(i, j);
        }
    }
}

void Graph::connectivity(){

    for (int i = 0; i < V;i++){
        int j;
        for (j = 0; j < V;j++){
            if(mat[i][j] != 0) {
                break;
            }
        }
        if(j==V){
            cout << "Graph is disconnected for city '" << cities[i] << "'\n";
            return;
        }
    }

    cout << "Graph is connected.\n";
}

void Graph::print(){
    cout << "i : \tCities : \n";
    for (int i = 0; i < V;i++){
        cout << i << " : \t" << cities[i] << endl;
    }
    cout << endl;

    for (int i = 0; i < V;i++){
        for (int j = 0; j < V;j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){

    Graph *g = new Graph(3);

    g->print();
    g->connectivity();
}