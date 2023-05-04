#include <iostream>
#include<list>
#include<queue>
#include<stack>
using namespace std;

class Edge{
		public:
	int dest;
	int wt;
	

	
	Edge(int d, int w=1){
		dest = d;
		wt = w;
	}

};

class Graph{

	int V;
	list<Edge> *graph;
	
	public:
	
	Graph(int v){
		V = v;
		cout << "Graph of  " << V << " vertices has been created.\n";
		graph = new list<Edge>[V];
	}
	
	void addEdge(int s,int d, int w=1){
		
		Edge edg(d,w);
		graph[s].push_back(edg);
		
		Edge edg2(s,w);
		graph[d].push_back(edg2);
	}
	
	void bfs(int src){
	
		bool visited[V] = {false};
	
		for (int i = 0; i < V; i++) {
		
            if(!visited[i])
                bfsUtil(visited,src);
        }
	}
	
	void bfsUtil(bool visited [], int src) {
        
        queue<int> q;
        
        cout << "BFS : ";
        q.push(src);
        while (!q.empty()) {
    
            int current = q.front();
            q.pop();
            
            if (visited[current] == false) {
    
                visited[current] = true;
                cout << current << " ";
    
                // add neighbors
                list<Edge>::iterator it;
                for(it = graph[current].begin(); it != graph[current].end(); it++){
                
                	q.push((*it).dest);
                }
            }
        }
       cout << endl;
    }
    
    void dfs(int src) {
        bool visited[V] = {false};
        
        for (int i = 0; i < V; i++) {
            if(!visited[i])
                dfsUtil(visited,src);
        }
        
    }
    
    void dfsUtil(bool visited[], int src) {

        stack<int> s;
        s.push(src);
        cout << "DFS : ";
        while (!s.empty()) {

            int curr = s.top();
            s.pop();

            if (!visited[curr]) {
            
                cout << curr << " ";
                
                visited[curr] = true;
                list<Edge>::iterator it;
                for (it = graph[curr].begin(); it != graph[curr].end(); it++) {
                    s.push((*it).dest);
                }
            }
        }
        cout << endl;
    }

};

int main(){

	int V = 6;
	Graph g(4);
	
	g.addEdge(0,1);
	g.addEdge(0,2);
	g.addEdge(1,3);
	g.addEdge(2,3);
	
	int src;
	cout << "Enter source : ";
	cin >> src;
	g.bfs(src);
	g.dfs(src);

	
	return 0;
}
