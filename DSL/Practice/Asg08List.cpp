/*
There are flight paths between cities. If there is a flight between city A and city B then there is an edge between the cities. The cost of the edge can be the time that flight take to reach city B from A, or the amount of fuel used for the journey Represent this as a graph. The node can be represented by airport name or name of the city Use adjacency list representation of the graph or use adjacency matrix representation of the graph
*/

#include<iostream>
using namespace std;
#define M 25

class Edge{
    public:

    int src;
    int dest;
    int wt;


    Edge(int s, int d, int w=1){
        src = s;
        dest = d;
        wt = w;
    }
};

class Node{
    public:

    Edge *e;
    Node *next;

    Node(Edge*e){
        this->e = e;
        next = NULL;
    }
};

class List{
    public:

    Node *head;
    Node *tail;
    string city;
    int len;

    List(){
        head = NULL;
        tail = NULL;
        len = 0;
    }

    void push_back(Edge*e){

        if(head == NULL){
            head = tail = new Node(e);
            len++;
            return;
        }

        tail->next = new Node(e);
        tail = tail->next;
        len++;
    }

    int size(){
        return len;
    }

};

class Graph{
    int V;
    List edges[M];

    void setCities();

public:
    Graph(int);
    void createGraph();
    void addEdge(int, int,int);
    void print();
    void addV();
    void addNeighbours();
    void checkConnectivity();
};

Graph::Graph(int v){
    V = v;
    cout << "\t\t\tGraph of size " << V << " has been created.\n";
    setCities();
}


void Graph::setCities(){
    cout << "\t\t\tEnter airport names : \n";
    for (int i = 0; i < V;i++){
        cout << "\t\t\tCity " << i + 1 << " : ";
        cin >> edges[i].city;
    }

    cout << "\t\t\tAirports created successfully.\n";
}

void Graph::createGraph(){
    for (int i = 0; i < V - 1;i++){
        for (int j = i + 1; j < V;j++){

            cout << "\t\t\tIs there flight b/w '" << edges[i].city<< "' & '" << edges[j].city << " : ";
            int ch;
            cin >> ch;

            if(ch==1){
                cout << "\t\t\tEnter fuel required to fly : ";
                int wt;
                cin >> wt;
                addEdge(i, j,wt);
            }
        }
    }
}

void Graph::addEdge(int i,int j,int wt){
    Edge *e = new Edge(i, j, wt);
    edges[i].push_back(e);
    e = new Edge(j, i, wt);
    edges[j].push_back(e);
}

void Graph::print(){

    cout << "\t\t\t Graph is : \n";
    for (int i = 0; i < V;i++){
        cout << "\t\t\t" << edges[i].city << "\t:\t";
        Node *temp = edges[i].head;
            while(temp != NULL){
                cout << edges[temp->e->dest].city << " -> ";
                temp = temp->next;
            }
            cout << "NULL\n";
    }
}

void Graph::addV(){
    cout << "\t\t\tEnter name of new airpoirt : ";
    cin >> edges[V].city;
    cout << "\t\t\tAirport Added.\n";
    V++;
}

void Graph::addNeighbours(){
    addV();
    for (int i = 0; i < V-1;i++){

        cout << "\t\t\tIs there flight b/w '" << edges[V-1].city << "' & '" << edges[i].city << " : ";
            int ch;
            cin >> ch;

            if(ch==1){
                cout << "\t\t\tEnter fuel required to fly : ";
                int wt;
                cin >> wt;
                addEdge(V-1,i,wt);
            }
        }
}

void Graph::checkConnectivity(){
    for (int i = 0; i < V;i++){
            if(edges[i].len==0){
                cout << edges[i].city << " is disnonnected.\n";
                return;
            }
        }
        cout << "Graph is connected.\n";

    cout << "\t\t\tGraph is connected.\n";
}
int main(){

    int ch;
    Graph *g = NULL;

    while(true){


    cout << "*** Graph using Addjacency Matrix ***\n";
    cout << "1-initialize \n"
         << "2-create whole graph\n"
         << "3-add a vertex\n"
         << "4-add an bidirectional edge\n"
         << "5-add a vertex and its connections\n"
         << "6-check connectivity\n"
         << "7-print graph\n"
         << "0-terminate program\n";

    cout << "Enter your choice : ";

    cin >> ch;

    switch(ch){

        case 0:
            cout << "\t\t\tT E R M I N A T I N G\n";
            return 0;

        case 1:
            delete g;
            cout << "\t\t\tEnter number of Airports : ";
            cin >> ch;
            g = new Graph(ch);
            break;

        case 2:
            if(g==NULL)
                break;
            g->createGraph();
            break;

        case 3:
            if(g==NULL)
                break;
            cout << "\t\t\tLet's add a disconnected new vertex to the graph.\n";
            g->addV();
            break;

        case 4:
            if(g==NULL)
                break;
            int src, dest, wt;
            cout << "\t\t\tEnter src : ";
            cin >> src;
            cout << "\t\t\tEnter dest : ";
            cin >> dest;
            cout << "\t\t\tEnter fuel : ";
            cin >> wt;
            if(src!=dest)
                g->addEdge(src, dest, wt);
            break;

        case 5:
            if(g==NULL)
                break;
            g->addNeighbours();
            break;

        case 6:
            if(g==NULL)
                break;
            g->checkConnectivity();
            break;

        case 7:
            if(g==NULL)
                break;
            g->print();
            break;

        default:
            cout << "\t\t\tBad choice.\n";
    }
    }
}