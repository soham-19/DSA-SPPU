#include <iostream>
#include <stack>
#include <list>
using namespace std;
#define M 20
class Edge
{

public:
    int src;
    int dest;
    int wt;

    Edge(int s, int d, int w = 1)
    {
        src = s;
        dest = d;
        wt = w;
    }
};

class Graph
{

public:
    list<Edge*> edges[M];
    int V;
    string cities[M];

    Graph(int v)
    {
        V = v;
        cout << "Graph of " << V << " cities has been created.\n";
        setCities();
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

        if (isFlight)
        {

            Edge *e = new Edge(i, j);
            edges[i].push_back(e);

            e = new Edge(j, i);
            edges[j].push_back(e);
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
            cout << i << " : ";
            for (auto it = edges[i].begin(); it !=
                                             edges[i].end();
                 ++it)
                cout << ' ' << (*it)->dest;
        cout << endl;
        }
    }

    bool connectivity(){

        for (int i = 0; i < V;i++){
            if(edges[i].size()==0){
                cout << i << endl;
                return true;
            }
        }
        return false;
    }

    bool hasPath(int src,int dest){

        stack<int> s;
        s.push(src);
        bool visited[V];

        while(!s.empty()){

            int curr = s.top();
            s.pop();

            if(curr == dest)
                return true;

            if(!visited[curr]){

                visited[curr] = true;
                for (auto it = edges[curr].begin(); it != edges[curr].end();it++){

                    s.push((*it)->dest);
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

    if(g.connectivity())
        cout << "\nnot-connected-graph\n";
    else
        cout << "\nconnected-graph\n";

    if(g.hasPath(2,4))
        cout << "\npath exists\n";
    else
        cout << "\npath does not exist\n";

    if(g.hasPath(2,0))
        cout << "\npath exists\n";
    else
        cout << "\npath does not exist\n";
    
    return 0;
}