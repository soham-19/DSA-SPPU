 /*
There are flight paths between cities. If there is a flight between city A and city B then there is an edge between the cities. The cost of the edge can be the time that flight take to reach city B from A, or the amount of fuel used for the journey Represent this as a graph. The node can be represented by airport name or name of the city Use adjacency list representation of the graph or use adjacency matrix representation of the graph
*/

/*
	setsys        		.
	resetsys            .
	add airport         .
	update airport       
	add flight          .
	remove flight       .
	check flight         .
	check connectivity   .
	print airport        .
	print system         .
	
*/

#include<iostream>
using namespace std;
#define M 10

class Graph{
	
	void setAirports();
	
	public:
	int v;
	string airports[M];
	float fuel[M][M];
	float time [M][M];
	
	Graph(){
		resetSystem();
		setAirports();
	}
	
	void resetSystem();
	void setSystem();
	void displayAirports();
	void addAirport();
	void updateAirport(int);
	void addFlight(int,int);
	void removeFlight(int,int);
	void checkFlight(int,int);
	void checkConnectivity();
	void printAirport(int);
	void printSystem();
	
	
};

void Graph::resetSystem(){
	for(int i=0;i<M;i++){
		for(int j=0;j<M;j++){
			fuel[i][j] = time[i][j] = 0.0f;
		}
	}
}

void Graph::setAirports(){
	cout << "How many airports should be in system initially :  ";
	cin >> v;
	cout << "Enter Airport titles : \n";
	for(int i=0; i<v; i++){
		cout << "Airport " << i+1 << " : ";
		cin >> airports[i];
	}
	cout << "All data stored successfully.\n";
}

void Graph::setSystem(){
	resetSystem();
	bool isFlight;
	for(int i=0; i<v; i++){
		for(int j=i+1; j<v; j++){
			cout << "Is there flight b/w \"" << airports[i] << "\" & \"" << airports[j] << "\" ? ";
			cin >> isFlight;
			if(isFlight)
				addFlight(i,j);
		}
	}
}

void Graph::displayAirports(){
	cout << "\t";
	for(int i=0; i<v; i++){
		cout << i+1 << " : " << airports[i];
	}
	cout << endl;
}

void Graph::addAirport(){
	if(v==M-1){
		cout << "Maximum Capacity Reached.\n";
		return;
	}
	cout << "Enter title of new airport : ";
	cin >> airports[v];
	cout << "Airport added successfully.\n";
	v++;
}

void Graph::updateAirport(int i){
	bool isFlight;
	for(int j=0; j<v;j++){
		if(i==j)
			continue;
		cout << "Is there flight b/w \"" << airports[i] << "\" & \"" << airports[j] << "\" ? ";
		cin >> isFlight;
		if(isFlight)
			addFlight(i,j);
		else 
			removeFlight(i,j);	
	}
	
}

void Graph::addFlight(int i, int j){
	cout << "Enter fuel required to fly : ";
	cin >> fuel[i][j];
	cout << "Enter time required to fly : ";
	cin >> time[i][j];
	
	time[j][i] = time[i][j];
	fuel[j][i] = fuel[i][j];
}

void Graph::removeFlight(int i, int j){
	fuel[i][j] = fuel[j][i] = time[i][j] = time[j][i] = 0.0f;
}

void Graph::checkFlight(int i,int j){
	if(fuel[i][j] != 0){
		cout << "Yes Available.\n";
		return;
	}
	cout << "Not Available.\n";
}

void Graph::checkConnectivity(){
	bool flag = false;
	for(int i=0;i<v;i++){
		int j;
		for(j=0;j<v;j++){
			if(fuel[i][j] != 0)
				break;
		}
		if(j==v){
			flag = true;
			cout << "Airport \"" << airports[i] << "\" is disconnected.\n";
		}
	}
	if(flag)
		cout << "Whole System is connected.\n";
}

void Graph::printAirport(int i){
	cout << airports[i] << " : \n";
	for(int j=0; j<v; j++){
		if(fuel[i][j] != 0){
			cout << "\t" << airports[j] << " [" << fuel[i][j] << " , " << time[i][j] << "]" << endl;
		}
	}
}

void Graph::printSystem(){
	for(int i=0;i<v;i++){
		cout << i+1 << ". ";
		printAirport(i);
		cout << "----------------------------\n";
	}
}

int main(){
	int ch,s,d;
	
	Graph g;
	
	while(true){
		cout << "\t* F L I G H T   M A NA G E ME N T   S Y S T E M*\n"
			 << "1-reset the system\n"
			 << "2-set the system\n"
			 << "3-add an airport\n"
			 << "4-update an airport\n"
			 << "5-add a flight\n"
			 << "6-remove a flight\n"
			 << "7-check a flight\n"
			 << "8-display an airport\n"
			 << "9-display the system\n"
			 << "10-check connectivity\n\n"
			 << "Enter your choice : ";
		cin >> ch;
		
		switch(ch){
			
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
				g.displayAirports();
				cout << "Select Airport : ";
				cin >> s;
				g.updateAirport(s);
				break;
			case 5:
				g.displayAirports();
				cout << "Select Sorce Airport : ";
				cin >> s;
				cout << "Select Destination Airport : ";
				cin >> d;
				g.addFlight(s,d);
				break;
			case 6:
				g.displayAirports();
				cout << "Select Sorce Airport : ";
				cin >> s;
				cout << "Select Destination Airport : ";
				cin >> d;
				g.removeFlight(s,d);
				break;
			case 7:
				g.displayAirports();
				cout << "Select Sorce Airport : ";
				cin >> s;
				cout << "Select Destination Airport : ";
				cin >> d;
				g.checkFlight(s,d);
				break;
			case 8:
				g.displayAirports();
				cout << "Select Airport : ";
				cin >> s;
				g.printAirport(s);
				break;
			case 9:
				g.printSystem();
				break;
			case 10:
				g.checkConnectivity();
				break;
			deafult:
				cout << "Try Again!!\n";
			
				
		}
	}
}
