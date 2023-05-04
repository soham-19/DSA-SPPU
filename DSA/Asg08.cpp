/*
There are flight paths between cities. If there is a flight between city A and city B then there is an edge between the cities. The cost of the edge can be the time that flight takes to reach city B from A, or the amount of fuel used for the journey. Represent this as a graph. The node can be represented by the airport name of the city. Use representation of the graph. Check whether thr graph is connected or not. Justify the storage representation used.
*/

#include <iostream>
using namespace std;

string cities[] = {"Mumbai", "Bangluru", "Delhi", "Hydrabad", "Jammu"};
class Graph
{
public:
	int V;
	float matrix[20][20];

	Graph()
	{
		V = 5;
		cout << "Graph is created of size " << V << "*" << V << endl;

		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < V; j++)
			{
				matrix[i][j] = 0;
			}
		}
	}

	void createGraph()
	{

		for (int i = 0; i < V; i++)
		{

			for (int j = i + 1; j < V; j++)
			{

				cout << "Is there a flight between " << cities[i] << " and " << cities[j] << " ? ";
				bool isFlight;
				cin >> isFlight;

				if (isFlight)
				{
					float fuel;
					cout << "Enter fuel required : ";
					cin >> fuel;

					matrix[i][j] = fuel;
					matrix[j][i] = fuel;
				}
				else
				{
					matrix[i][j] = 0;
					matrix[j][i] = 0;
				}
				cout << "\n";
			}
		}
	}

	void display()
	{

		cout << "\n\n";
		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < V; j++)
			{
				cout << matrix[i][j] << "\t";
			}
			cout << endl;
		}
	}

	bool isConnected()
	{
		bool is = false;
		for (int i = 0; i < V; i++)
		{
			bool row = true;
			for (int j = i + 1; j < V; j++)
			{
				row = row && (matrix[i][j] == 0);
			}
			is = row;
		}
		return is;
	}
};

int main()
{

	Graph g;
	g.createGraph();
	g.display();
	bool connect = g.isConnected();

	if (!connect)
		cout << "Connected\n";
	else
		cout << "Not connected\n";
}
