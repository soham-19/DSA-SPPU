/*
Represent a given graph using adjacency matrix/list to perform DFS and using adjacency list to perform BFS. Use the map of the area around the college as the graph. Identify the prominent land marks as nodes and perform DFS and BFS on that
*/
// stack // queue // list // edge //node //graph

#include<iostream>
using namespace std;
#define M 100

class Stack{
    int top;
    int s[M];
    public:
    Stack(){
        top = -1;
    }
    bool isFull(){
        return top == M - 1;
    }
    bool isEmpty(){
        return top == -1;
    }
    void push(int x){
        if(isFull()){
            cout << "In push.\nStack full.\n";
            return;
        }
        s[++top] = x;
    }

    int peek(){
        if(isEmpty()){
            cout << "In peek.\nStack Empty.\n";
            return -1;
        }
        return s[top];
    }
    int pop(){
        if(isEmpty()){
            cout << "In pop.\nStack Empty.\n";
            return -1;
        }
        return s[top--];
    }
};

class Queue{
    int f, r, q[M];
    public:
    Queue(){
        f = r = -1;
    }
    bool isEmpty(){
        return f == -1 && r == -1;
    }
    bool isFull(){
        return r == M - 1;
    }

    void add(int x){
        if(isFull()){
            cout << "Queue is full.\nadd\n";
        }
        if(isEmpty()){
            f++;
        }
        q[++r] = x;
    }

    int remove(){
        if(isEmpty()){
            cout << "Queue empty.\nremove\n";
        }
        if(f==r){
            int x = q[f];
            f = r = -1;
            return x;
        }
        int x = q[f];
        f++;
        return x;
    }
};

class Edge{
    public:
    int src, dest, wt;
    Edge(int s,int d,int w=1){
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
    Node *head, *tail;

    List(){
        head = tail = NULL;
    }

    void printL(){
        Node *t = head;
        while(t!=NULL){
            cout << " " << t->e->dest;
            t = t->next;
        }
        cout << endl;
    }

    void push_back(Edge*e){
        if(head==NULL)
            head = tail = new Node(e);
        else {
            tail->next = new Node(e);
            tail = tail->next;
        }
    }
};

class Graph{
    public:
    int V;
    List edges[M];

    Graph(int v){
        V = v;
        cout << "Graph of " << V << " vertices created.\n";
        create();
    }
    void create(){
        for (int i = 0; i < V - 1;i++){
            for (int j = i + 1; j < V; j++)
            {
                cout << "Edge b/w " << i << " & " << j << " ? ";
                bool is;
                cin >> is;
                if(is){
                    addEdge(i, j);
                }
            }
        }
    }
    void addEdge(int i,int j){
        edges[i].push_back(new Edge(i, j));
        edges[j].push_back(new Edge(j,i));
    }

    void BFS(int src){
        bool vis[] = {false};
        cout << "BFS :";
        bfs(src, vis);
        for (int i = 0; i < V;i++){
            if(!vis[i])
                bfs(i, vis);
        }
        cout << ".\n";
    }

    void bfs(int src, bool vis[]){

        Queue q;
        q.add(src);

        while(!q.isEmpty()){
            int curr = q.remove();

            if(!vis[curr]) {

                cout << " " << curr;
                vis[curr] = true;

                Node *t = edges[curr].head;
                while(t!=NULL){
                    if(!vis[t->e->dest])
                        q.add(t->e->dest);
                    t = t->next;
                }
            }
        }
    }

    void DFS(int src){
        cout << "DFS :";
        bool vis[V] = {false};
        dfs(src, vis);
        for (int v = 0; v < V;v++){
            if(!vis[v])
                dfs(v, vis);
        }
            cout << ".\n";
    }

    void dfs(int src,bool vis[]){

        Stack s;
        s.push(src);

        while(!s.isEmpty()){
            int curr = s.pop();

            if(!vis[curr]) {

                cout << " " << curr;
                vis[curr] = true;

                Node *t = edges[curr].head;
                while(t!=NULL){

                    if(!vis[t->e->dest]){
                        s.push(t->e->dest);
                    }
                    t = t->next;
                }
            }
        }
    }
};

int main(){
    Graph g(7);
    for (int i = 0; i < g.V;i++){
        cout << i << " ";
        
        g.edges[i].printL();
    }
        g.BFS(0);
    g.DFS(0);
}
