/*
There are flight paths between cities. If there is a flight between city A and city B then there is an edge between the cities. The cost of the edge can be the time that flight take to reach city B from A, or the amount of fuel used for the journey Represent this as a graph. The node can be represented by airport name or name of the city Use adjacency list representation of the graph or use adjacency matrix representation of the graph
*/

// Adjacency List

// Edge class Node class List class Graph class

#include<iostream>
#define M 20
using namespace std;

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

    public:
    int V;
    List edges[M];
    string cities[M];

    Graph(int v){
        V = v;
        cout << "Graph of " << V << " cities has been created.\n";
        setCities();
    }

    void setCities(){
        for (int i = 0; i < V;i++){
            cout << "Enter name of " << i + 1 << "th city : ";
            cin >> cities[i];
        }
        cout << "Data stored successfully\n";
    }

    void add(int i, int j){
        char ch;
        cout << "Is there availablity of flight b/w " << cities[i] << " & " << cities[j] << " ? ";
        cin >> ch;

        if(ch=='y' || ch=='Y') {

            edges[i].push_back(new Edge(i,j));
            edges[j].push_back(new Edge(j,i));
        }
    }

    void createAGraph(){

        for (int i = 0; i < V-1; i++){
            for (int j = i+1; j < V;j++){
                add(i, j);
            }
        }
    }

    void printGraph(){
        cout << "Graph is : \n";
        for (int i = 0; i < V;i++){

            cout << cities[i] << "\t:\t";
            Node *temp = edges[i].head;
            while(temp != NULL){
                cout << cities[temp->e->dest] << " -> ";
                temp = temp->next;
            }
            cout << "NULL\n";
        }
    }

    void checkConnectivity(){
        for (int i = 0; i < V;i++){
            if(edges[i].len==0){
                cout << cities[i] << " is disnonnected.\n";
                return;
            }
        }
        cout << "Graph is connected.\n";
    }
};


int main(){

    int v;
    cout << "Enter the size of Map : ";
    cin >> v;


    Graph *g = new Graph(v);
    g->createAGraph();

    while(true){

        cout << "       * AirPort System *\n\n";
        cout << "1-add new airport\n";
        cout << "3-display\n";
        cout << "4-check connecitivity\n";
        cout << "5-exit\n";

        cout << "Select your option : ";

        int ch;
        cin >> ch;

        switch(ch){
            case 1:
                break;

            case 3:
                g->printGraph();
                break;

            case 4:
                g->checkConnectivity();
                break;
            case 5:
                cout << "T E R M I N A T I N G\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}