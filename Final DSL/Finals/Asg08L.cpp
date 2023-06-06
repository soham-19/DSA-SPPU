 /*
There are flight paths between cities. 
If there is a flight between city A and city B then there is an edge between the cities. 
The cost of the edge can be the time that flight take to reach city B from A, 
or the amount of fuel used for the journey Represent this as a graph. 
The node can be represented by airport name or name of the city 
Use adjacency list representation of the graph or use adjacency matrix representation of the graph
*/

/*
class Edge->Node->List->Graph

setsystem
resetsystem
add airport
update airport
add flight
remove flight
search a flight
print airport
print system
*/

#include<iostream>
using namespace std;
#define M 100
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
		Edge* edge;
		Node* next;
		
		Node(Edge* e){
			edge = e;
			next = NULL;
		}
		
		~Node(){
			delete edge;
		}
};

class List{
	public:
		Node* head;
		Node* tail;
		string airport_name;
		
		List(){
			head = tail = NULL;			
		}
		
		~List(){
			deleteLL();
		}
		
		void push_back(Edge*);
		bool remove(int);
		bool search(int);
		void deleteLL();
};

void List::push_back(Edge* e){
	if(head == NULL){
		head = tail = new Node(e);
	} else {
		tail->next = new Node(e);
		tail = tail->next;
	}
}

bool List::remove(int i){
	Node* curr = head;
	Node* prev = NULL;
	
	while(curr != NULL){
		if(curr->edge->dest == i){
			if(prev == NULL){
				head = curr->next;
			} else {
				prev->next = curr->next;
			}
			delete curr;
			return true;
		}
		prev = curr;
		curr = curr->next;		
	}
	return false;
}

bool List::search(int i){
	Node* curr = head;
	while(curr != NULL){
		if(curr->edge->dest == i){
			return true;
		}
		curr = curr->next;
	}
	return false;	
}

void List::deleteLL(){
	Node* curr = head;
	Node* temp;
	while(curr != NULL){
		temp = curr;
		curr = curr->next;
		delete temp;
	}
	head = tail = NULL;
}

class Graph{
		void setAirports();
	public:
		int v;
		List adjList[M];
		
		Graph(){
			setAirports();			
		}
			
		void printAirports();
		void setSystem();
		void resetSystem();
		void addAirport();
		void updateAirport();
		void addFlight(int,int);
		void removeFlight(int, int);
		void searchFlight(int,int);
		void displayAirport(int);
		void displaySystem();
		void connectivity();
		bool hasPath(int source, int destination) {
        bool visited[M] = { false };
        return hasPathUtil(source, destination, visited);
		}
		bool hasPathUtil(int source, int destination, bool visited[]) {
        visited[source] = true;

        if (source == destination) {
            cout << adjList[source].airport_name << " ";
            return true;
        }

        Node* temp = adjList[source].head;
        while (temp != NULL) {
            int adjacentAirport = temp->edge->dest;

            if (!visited[adjacentAirport]) {
                if (hasPathUtil(adjacentAirport, destination, visited)) {
                    cout << adjList[source].airport_name << " ";
                    return true;
                }
            }

            temp = temp->next;
        }

        return false;
    	}
};

void Graph::setAirports(){
	cout << "Enter initial number of Airports : ";
	cin >> v;
	cout << "Enter names of airports :\n";
	cin.ignore();
	for(int i=0; i<v; i++){
		cout << "Airport " << i+1 << " : ";
		getline(cin, adjList[i].airport_name);		
	}
	cout << "Airports created successfully.\n";	
}

void Graph::printAirports(){
	cout << endl << "\t";
	for(int i=0; i<v; i++){
		cout << i+1 << " " << adjList[i].airport_name << "\t";
	}
	cout << endl << endl;
}

void Graph::setSystem(){
	resetSystem();
	bool isFlight;
	for(int i=0; i<v; i++){
		for(int j=i+1; j<v; j++){
			cout << "Is flight available b/w \"" << adjList[i].airport_name << "\" & \"" << adjList[j].airport_name << "\" ? ";
			cin >> isFlight;
			if(isFlight)
				addFlight(i,j);
		}
	}
	cout << "System set successfully.\n\n";
}

void Graph::resetSystem(){
	for(int i=0; i<v; i++){
		adjList[i].deleteLL();
	}
}

void Graph::addAirport(){
	cin.ignore();
	cout << "Enter name of airport to be added : ";
	getline(cin, adjList[v].airport_name);
	cout << "Airport created successfully.\n\n";
	v++;
} 

void Graph::updateAirport(){
	int i;
	printAirports();
	cout << "Enter airport to be updated : ";
	cin >> i;
	adjList[i].deleteLL();
	bool isFlight;
	for(int j=0; j<v; j++){
		if(i==j)
			continue;
		
		cout << "Is flight available b/w \"" << adjList[i].airport_name << "\" & \"" << adjList[j].airport_name << "\" ? ";
		cin >> isFlight;
		if(isFlight)
			addFlight(i,j);
	}
}

void Graph::addFlight(int i, int j){
	float fuel, time;
	cout << "Enter fuel required to fly ";
	cin >> fuel;
	cout << "Enter time required to fly ";
	cin >> time;
	
	adjList[i].push_back(new Edge(j,fuel,time));
	adjList[j].push_back(new Edge(i,fuel,time));
}

void Graph::removeFlight(int i, int j){
	
	if(adjList[i].remove(j)){
		cout << "Flight \"" << adjList[i].airport_name << "\"<->\"" << adjList[i].airport_name << " removed.\n";
		adjList[j].remove(i);	
	} else {
		cout << "Flight \"" << adjList[i].airport_name << "\"<->\"" << adjList[i].airport_name << " does not exist.\n";
	}	
}

void Graph::searchFlight(int i, int j){
	
	if(adjList[i].search(j)){
		cout << "Flight \"" << adjList[i].airport_name << "\"<->\"" << adjList[i].airport_name << " found.\n";
		adjList[j].remove(j);	
	} else {
		cout << "Flight \"" << adjList[i].airport_name << "\"<->\"" << adjList[i].airport_name << " does not exist.\n";
	}	
}

void Graph::displayAirport(int i){
	cout << "Airport \"" << adjList[i].airport_name << "\"\n" ;
	Node* temp = adjList[i].head;
	while(temp != NULL){
		int j = temp->edge->dest;
		cout << "\t" << adjList[j].airport_name << " [" << temp->edge->fuel << "kltr," << temp->edge->time << "hr]\n";
		temp = temp->next;
	}
	cout << "-----------------------------\n";
}

void Graph::displaySystem(){
	for(int i=0;i <v; i++){
		displayAirport(i);
	}
}

void Graph::connectivity(){
	bool connected = false;
	for(int i=0; i<v; i++){
		if(adjList[i].head == NULL){
			cout << "\"" << adjList[i].airport_name << "\" is disconnected.\n";
			connected = true;
		}
	}
	if(connected){
		cout << "All airports are connected.\n";
	}
	cout << endl;
}

int main(){
	Graph g;
	
	int s,d,ch;
	
	while(true){
		
		cout << "* F L I G H T   S Y S T E M *\n"
			 << "  01. Set the System\n"
			 << "  02. Reset the System\n"
			 << "  03. Add an airport\n"
			 << "  04. Update Routes for an airport\n"
			 << "  05. Add a flight\n"
			 << "  06. Remove a flight\n"
			 << "  07. Search a flight\n"
			 << "  08. Display an airport\n"
			 << "  09. Display the system\n"
			 << "  10. Check Connectivity\n\n"
			 << " Enter your choice : ";
		cin >> ch;
		
		switch(ch){
			case 0:
				cout << "Terminating\n";
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
				g.updateAirport();
				break;
			case 5:
				g.printAirports();
				cout << "Enter source : ";
				cin >> s;
				cout << "Enter Destination : ";
				cin >> d;
				g.addFlight(s-1,d-1);
				break;
			case 6:
				g.printAirports();
				cout << "Enter source : ";
				cin >> s;
				cout << "Enter Destination : ";
				cin >> d;
				g.hasPath(s-1,d-1);
				break;
			case 7:
				g.printAirports();
				cout << "Enter source : ";
				cin >> s;
				cout << "Enter Destination : ";
				cin >> d;
				g.searchFlight(s-1,d-1);
				break;
			case 8:
				g.printAirports();
				cout << "Enter the airport : ";
				cin >> s;
				g.displayAirport(s-1);
				break;
			case 9:
				g.displaySystem();
				break;
			case 10:
				g.connectivity();
				break;
			default:
				cout << "  Invalid choice!!\n";				
		}
	}
}