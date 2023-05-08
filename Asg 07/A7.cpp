#include <iostream>
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

class ListNode {
    public:
        Edge* data;
        ListNode *next;

        ListNode(Edge*x){
            data = x;
            next = NULL;
        }

};

class List{
    public:
        ListNode *head, *tail;
        int len;

        List(){
            head = tail = NULL;
            len = 0;
        }

        int size(){
            return len;
        }

        void push_back(Edge* x) {

            ListNode *new_node = new ListNode(x);
            len++;
            if(tail == NULL){
                head = tail = new_node;
            }
            else{
                tail->next = new_node;
                tail = tail->next;
            }
        }

        void print(){

            ListNode *t = head;
            cout << "LL : ";
            while(t!=NULL){
                cout << t->data->dest << " ";
                t = t->next;
            }
            cout << endl;
        }
};

class Queue{

    public:
        int q[100];
        int f, r;

        Queue(){
            f = r = -1;
        }

        void add(int x){
            if(empty()){
                q[0] = x;
                f = r = 0;
            }
            q[++r] = x;
        }
        int remove(){
            if(empty())
                return 5;
            
            int d = q[f];
            if(f==r){
                f = r = -1;
                return d;
            }
            f++;
            return d;
        }
        bool empty(){
            return r >= 100 || f > r || (f==-1&&r==-1);
        }
};

class Stack{
    public:
        int s[100];
        int top;

        Stack(){
            top = -1;
        }

        void push(int x){
            s[++top] = x;
        }

        int pop(){
            if(empty()){
                return 100;
            }
            int d = s[top];
            top--;
            return d;
        }

        bool empty(){
            return top == -1;
        }
};

class Graph{

	int V;
	List *graph;
	
	public:
	
	Graph(int v){
		V = v;
		cout << "Graph of  " << V << " vertices has been created.\n";
		graph = new List[V];
	}
	
	void addEdge(int s,int d, int w=1){

        Edge *e = new Edge(d, w);
        graph[s].push_back(e);

        e = new Edge(s, w);
        graph[d].push_back(e);
	}
	
	void bfs(int src){
	
		bool visited[V] = {false};
        bfsUtil(visited,src);
    }
	
	void bfsUtil(bool visited [], int src) {

        Queue q;

        cout << "BFS : ";
        q.add(src);
        while (!q.empty()) {
    
            int current = q.remove();
            // cout << "F = " << q.f << " "
            //      << "R = " << q.r << endl;

            if (visited[current] == false) {
    
                visited[current] = true;
                cout << current << " ";
    
                // add neighbors
                for (int i = 0; i < graph[i].size();i++){
                    ListNode *temp = graph[i].head;
                    while(temp!=NULL){
                        q.add(temp->data->dest);
                        temp = temp->next;
                    }
                }
            }
        }
       cout << endl;
    }
    
    void dfs(int src) {
        bool visited[V] = {false};
        dfsUtil(visited,src);        
    }
    
    void dfsUtil(bool visited[], int src) {

        Stack s;
        s.push(src);
        cout << "DFS : ";
        while (!s.empty()) {

            int curr = s.pop();

            if (!visited[curr]) {
            
                cout << curr << " ";
                
                visited[curr] = true;
                // add neighbors
                for (int i = 0; i < graph[i].size();i++){
                    ListNode *temp = graph[i].head;
                    while(temp!=NULL){
                        if(!visited[temp->data->dest]){
                        s.push(temp->data->dest);
                        }
                        temp = temp->next;
                    }
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
	// cout << "Enter source : ";
	// cin >> src;
	g.bfs(0);
	g.dfs(0);

	return 0;
}
