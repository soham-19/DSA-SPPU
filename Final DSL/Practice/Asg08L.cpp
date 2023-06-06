/*
There are flight paths between cities. If there is a flight between city A and city B then there is an edge between the cities. The cost of the edge can be the time that flight take to reach city B from A, or the amount of fuel used for the journey Represent this as a graph. The node can be represented by airport name or name of the city Use adjacency list representation of the graph or use adjacency matrix representation of the graph
*/
// class edge-> class list -> class graph
#include<iostream>
using namespace std;
#define null NULL
#define M 25

class Edge{
    public:
        int dest;
        float fuel;
        float time;

        Edge(int d, float f, float t){
            dest = d;
            fuel = f;
            time = t;
        }
};
class Node{
    public:
        Edge *e;
        Node *next;

        Node(Edge*e){
            this->e = e;
            next = null;
        }
};

class List{
    public:
        Node *head, *tail;
        string city;
        int len;

        List(){
            head = tail = null;
            len = 0;
        }

        ~List(){
            deleteLL();
        }

        void pushback(Edge *);
        bool remove(int);
        bool search(int);
        void deleteLL();
};

void List::pushback(Edge*e){
    if(head==null){
        head = tail = new Node(e);
    } else {
        tail->next = new Node(e);
        tail = tail->next;
    }
    len++;
}

bool List::remove(int key) {
    Node *prev = null, *curr = head;
    while(curr!=null) {
        if(curr->e->dest==key){
            if(prev == null) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            len--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

bool List::search(int key) {
    Node *temp = head;
    while(temp!=null) {
        if(temp->e->dest==key) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void List::deleteLL(){
    Node *temp = head;
    while(temp!=null){
        Node *curr = temp;
        temp = temp->next;
        delete curr->e;
        delete curr;
    }
    head = tail = null;
    len = 0;
}
class Graph{

    int v;
    List adjList[M];

    void setCities();

    public:

    Graph(int v) {
        this->v = v;
        setCities();
    }

    ~Graph(){
        resetSystem();
    }

    void displayCities();               //1
    void resetSystem();                 
    void setSystem();                   //1
    void addAirport();                  //1
    void updateRoutes(int);             //1
    void addFlight(int, int);           //1
    void resetFlight(int, int);         //1
    void checkAvailibility(int, int);   //1
    void checkConnectivity();           //1
    void printAirport(int);             //1
    void printSystem();                 //1

    bool hasPath(int src, int des, bool vis[]){
        if(src == des){
            return true;
        }
        vis[src] = true;

        Node *node = adjList[src].head;
        
        while(node != NULL){
            if(!vis[node->e->dest] && hasPath(node->e->dest,des,vis))
                return true;
            node = node->next;
        }
        return false;
    }

};

void Graph::setCities() {
    cout << "Enter city names : \n";
    for (int i = 0; i < v;i++){
        cout << "\tCity " << i + 1 << " : ";
        cin >> adjList[i].city;
    }
    cout << v << " cities stored successfully.\n";
}

void Graph::displayCities(){
    for (int i = 0; i < v;i++){
        cout << i + 1 << ":" << adjList[i].city << "\t";
    }
    cout << endl;
}

void Graph::resetSystem(){
    for (int i = 0; i < M;i++){
        adjList[i].deleteLL();
    }
}
void Graph::setSystem(){
    resetSystem();
    bool isFlight;
    for (int i = 0; i < v - 1;i++){
        for (int j = i + 1; j < v;j++){

            cout << "Flight b/w \"" << adjList[i].city << "\" & \"" << adjList[j].city << "\" ? ";
            cin >> isFlight;

            if(isFlight) {
                addFlight(i, j);
            }
        }
    }
}

void Graph::addAirport(){
    if(v==M-1) {
        cout << "Maximum Capacity Reached.\n";
        return;
    }
    cout << "Enter name of airport to be added : ";
    cin >> adjList[v].city;
    cout << "Airport added successfully.\n";
    v++;    
}

void Graph::updateRoutes(int src) {
    adjList[src].deleteLL();
    bool isFlight;
    for (int i = 0; i < v;i++) {
        if(i==src)
            continue;
        
        cout << "Flight b/w \"" << adjList[src].city << "\" & \"" << adjList[i].city << "\" ? ";
        cin >> isFlight;

        if(isFlight)
            addFlight(src, i);
        else 
            resetFlight(src, i);
    }    
}

void Graph::addFlight(int src, int dest) {

    float fuel, time;
    cout << "Enter fuel required to fly : ";
    cin >> fuel;
    cout << "Enter time required to fly : ";
    cin >> time;

    Edge *e = new Edge(dest, fuel, time);
    adjList[src].pushback(e);

    e = new Edge(src, fuel, time);
    adjList[dest].pushback(e);
}

void Graph::resetFlight(int src, int dest){

    if(!adjList[src].remove(dest)){
        cout << "Flight did not exist.\n";
        return;
    }
    adjList[dest].remove(src);
}

void Graph::checkAvailibility(int i, int j) {
    if(adjList[i].search(j)){
        cout << "Flight is available b/w these airports.\n";
    } else {
        cout << "No flight found b/w these airports.\n";
    }
}

void Graph::checkConnectivity(){
    int count = 0;
    for (int i = 0; i < v;i++) {
        if (adjList[i].len==0){
            cout << "Graph is disconnected for \"" << adjList[i].city << "\"\n";
            count++;            
        }
    }
    if(count==0){
        cout << "Graph is connected.\n";
    }
}

void Graph::printAirport(int airport) {

    cout << "Airport \"" << adjList[airport].city <<"\" : "<< endl;
    int flight = 1;
    Node *temp = adjList[airport].head;

    while(temp!=null){
        int to = temp->e->dest;
        cout << "\t" << flight++ << ". " << adjList[to].city << " [" << temp->e->fuel << "ltr ," << temp->e->time << "hr]\n";
        temp = temp->next;
    }
}

void Graph::printSystem() {
    for (int i = 0; i < v;i++) {
        printAirport(i);
        cout << "-----------------------------------\n";
    }
}

int main(){

    int v, ch, x, s, d;
    bool vis[5] = {false};
    bool b;
    cout << "Enter number of airports in the flight-management system : ";
    cin >> v;

    Graph g(v);

    while(true) {

        cout << "\t     * F L I G H T   M A N A G E M E N T  S Y S T E M\n"
             << "\t1-set the system\n"
             << "\t2-reset the system\n"
             << "\t3-add an airport\n"
             << "\t4-update an airport\n"
             << "\t5-add a flight\n"
             << "\t6-remove a flight\n"
             << "\t7-check availability of a flight\n"
             << "\t8-display an airport\n"
             << "\t9-display system\n"
             << "\t10-check connectivity\n"
             << "\t0-terminate\n"
             <<"\n\t\tEnter your choice :";
        cin >> ch;

        switch(ch) {

            case 0:
                cout << "T E R M I N A T I N G\n";
                return 0;
            
            case 1:
                g.setSystem();
                break;
            case 2:
                g.resetSystem();
                break;
            case 3:
                g.addAirport();
                break;
            case 4:
                g.displayCities();
                cout << "Enter airport value : ";
                cin >> x;
                g.updateRoutes(x-1);
                break;
            case 5:
                g.displayCities();
                cout << "Enter source airport value : ";
                cin >> s;
                cout << "Enter source airport value : ";
                cin >> d;
                g.addFlight(s-1, d-1);
                break;
            case 6:
                g.displayCities();
                cout << "Enter source airport value : ";
                cin >> s;
                cout << "Enter source airport value : ";
                cin >> d;
        
                b = g.hasPath(s-1, d-1,vis);
                if(b){
                cout << "\nPath Exists\n";
                } else {
                cout << "\nNo path\n";
                }
                break;
            case 7:
                g.displayCities();
                cout << "Enter source airport value : ";
                cin >> s;
                cout << "Enter source airport value : ";
                cin >> d;
                g.checkAvailibility(s-1, d-1);
                break;
            case 8:
                g.displayCities();
                cout << "Enter airport value : ";
                cin >> x;
                g.printAirport(x-1);
                break;
            case 9:
                g.printSystem();
                break;
            case 10:
                g.checkConnectivity();
                break;
            default:
                cout << "\tInvalid choice!!\n\n";
        }
    }
}