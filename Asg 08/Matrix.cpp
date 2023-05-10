/*
There are flight paths between cities. If there is a flight between city A and city B then there is an edge between the cities. The cost of the edge can be the time that flight takes to reach city B from A, or the amount of fuel used for the journey. Represent this as a graph. The node can be represented by the airport name of the city. Use representation of the graph. Check whether thr graph is connected or not. Justify the storage representation used.
*/

#include <iostream>
#include <stack>
using namespace std;

#define M 20

class Graph
{
public:
    float adj_mat[M][M];
    int V;
    string cities[M];

    Graph(int V)
    {

        this->V = V;
        clearGraph();
        cout << "Graph of " << V << " cities has been created.\n";
        setCities();
    }

    void clearGraph()
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                adj_mat[i][j] = 0;
            }
        }
    }

    void setCities()
    {
        for (int i = 0; i < V; i++)
        {
            cout << "Enter name of city " << i + 1 << " : ";
            cin >> cities[i];
        }
    }

    void add(int i, int j)
    {
        cout << "Is there any flight b/w " << cities[i] << " & " << cities[j] << "? ";
        bool isFlight;
        cin >> isFlight;

        if (!isFlight)
        {
            adj_mat[i][j] = adj_mat[j][i] = 0;
        }
        else
        {
            cout << "Enter fuel requied to fly : ";
            cin >> adj_mat[i][j];
            adj_mat[j][i] = adj_mat[i][j];
        }
    }

    void createAGraph()
    {

        for (int i = 0; i < V - 1; i++)
        {
            for (int j = i + 1; j < V; j++)
            {
                add(i, j);
            }
        }
    }

    void printGraph()
    {

        cout << "\nCities : ";

        for (int i = 0; i < V; i++)
            cout << i + 1 << ":" << cities[i] << "\n";
        cout << endl;

        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
                cout << adj_mat[i][j] << "\t";
            cout << endl;
        }
        cout << endl;
    }

    bool connectivity()
    {

        for (int i = 0; i < V; i++)
        {

            int j;
            for (j = 0; j < V; j++)
            {

                if (adj_mat[i][j] != 0)
                    break;
            }
            if (j == V)
                return true;
        }

        return false;
    }

    bool isPath(int src, int dest)
    {
        bool visited[M];
        for (int i = 0; i < V; i++)
            visited[i] = false;

        stack<int> s;
        s.push(src);
        visited[src] = true;

        while (!s.empty())
        {
            int curr = s.top();
            s.pop();

            if (curr == dest){
                return true;
            }

            for (int i = 0; i < V; i++)
            {
                if (adj_mat[curr][i] != 0 && !visited[i])
                {
                    s.push(i);
                    visited[i] = true;

                }
            }
        }

        return false;
    }
};

int main()
{

    Graph g(5);
    g.createAGraph();
    g.printGraph();

    if (g.connectivity())
        cout << "not connected\n";
    else
        cout << "connected\n";


    if(g.isPath(1,3)){
        cout << "\npath exists\n";
    } else{
        cout << "\npath doesn't exist\n";
    }

    if(g.isPath(1,4)){
        cout << "\npath exists\n";
    } else{
        cout << "\npath doesn't exist\n";
    }
    return 0;
}