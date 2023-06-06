/*
There are flight paths between cities. If there is a flight between city A and city B then there is an edge between the cities. The cost of the edge can be the time that flight take to reach city B from A, or the amount of fuel used for the journey Represent this as a graph. The node can be represented by airport name or name of the city Use adjacency list representation of the graph or use adjacency matrix representation of the graph
*/
#include<iostream>
using namespace std;
#define M 25

class Graph{
    private:
        int v;
        string cities[M];
        float time[M][M];
        float fuel[M][M];
        void setCities();

    public:
        Graph(int v){
            this->v = v;
            setCities();
            resetSystem();
        }

        void displayCities();
        void resetSystem();
        void setSystem();
        void addAirport();
        void updateRoutes(int);
        void addFlight(int, int);
        void resetFlight(int, int);
        void checkAvailibility(int, int);
        void checkConnectivity();
        void printAirport(int);
        void printSystem();
};

void Graph::setCities() {
    cout << "Enter city names : \n";
    for (int i = 0; i < v;i++){
        cout << "\tCity " << i + 1 << " : ";
        cin >> cities[i];
    }
    cout << v << " cities stored successfully.\n";
}

void Graph::displayCities() {
    for (int i = 0; i < v;i++){
        cout << i+1 << ":" << cities[i] << "\t";
    }
    cout << endl;
}

void Graph::resetSystem(){
    for (int i = 0; i < M;i++){
        for (int j = 0; j < M;j++){
            fuel[i][j] = time[i][j] = 0;
        }
    }
}

void Graph::setSystem(){
    bool isFlight;
    for (int i = 0; i < v;i++){
        for (int j = i + 1; j < v;j++){
            cout << "Flight b/w \"" << cities[i] << "\" & \"" << cities[j] << "\" ? ";
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
    cin >> cities[v];
    cout << "Airport added successfully.\n";
    v++;
}

void Graph::updateRoutes(int src) {
    bool isFlight;

    for (int i = 0; i < v;i++) {
        if(i==src)
            continue;
        
        cout << "Flight b/w \"" << cities[src] << "\" & \"" << cities[i] << "\" ? ";
        cin >> isFlight;

        if(isFlight)
            addFlight(src, i);
        else 
            resetFlight(src, i);
    }
}

void Graph::addFlight(int src, int dest) {
    cout << "Enter fuel required to fly : ";
    cin >> fuel[src][dest];
    fuel[dest][src] = fuel[src][dest];

    cout << "Enter time required to fly : ";
    cin >> time[src][dest];
    time[dest][src] = time[src][dest];
}

void Graph::resetFlight(int src,int dest){
    fuel[src][dest] = fuel[dest][src] = time[src][dest] = time[dest][src] = 0;
}

void Graph::checkAvailibility(int i, int j) {
    if(fuel[i][j] != 0){
        cout << "Flight is available b/w these airports.\n";
    } else {
        cout << "No flight found b/w these airports.\n";
    }
}

void Graph::checkConnectivity(){
    int count = 0;
    for (int i = 0; i < v;i++) {
        int j;
        for (j = 0; j < v;j++){
            if(fuel[i][j] !=0)
                break;
        }
        if(j==v) {
            cout << "Graph is disconnected for \"" << cities[i] << "\"\n";
            count++;
        }
    }
    if(count==0){
        cout << "Graph is connected.\n";
    }
}

void Graph::printAirport(int airport) {
    cout << "Airport \"" << cities[airport] <<"\" : "<< endl;
    for (int i = 0,flight=1; i < v;i++) {
        if(fuel[airport][i]!=0) {
            cout << "\t" << flight++ << ". " << cities[i] << " [" << fuel[i][airport] <<"ltr , " << time[i][airport] << "hr]\n";
        }
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
                g.resetFlight(s-1, d-1);
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