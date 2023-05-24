/*
Represent a given graph using adjacency matrix/list to perform DFS and using adjacency list to perform BFS. Use the map of the area around the college as the graph. Identify the prominent land marks as nodes and perform DFS and BFS on that
*/

#include<iostream>
using namespace std;
#define M 100

// stack
class Stack{
    int s[M];
    int top;

    public:
    Stack(){
        top = -1;
    }

    bool isFull(){
        return top >= M - 1;
    }
    bool isEmpty(){
            return top == -1;
    }

    void push(int x){
        if(isFull()){
            cout << "Stack Full.\n";
        } else {
            s[++top] = x;
        }
    }

    int peek(){
        if(isEmpty()){
            cout << "Stack empty peek.\n";
            return -1;
        }

        return s[top];
    }

    void pop(){
        if(isEmpty()){
            cout << "Stack empty pop.\n";
            return;
        }
        --top;
    }
};
//queue

class Queue{

    int front, rear;
    int q[M];

    public:
    Queue(){
        front = rear = -1;
    }

    bool isFull(){
        return rear >= M - 1;
    }

    bool isEmpty(){
        return front == -1;
    }

    void add(int x) {
        if(isFull()) {
            cout << "Queue is full.\n";
            return;
        }

        if(isEmpty()){
            front++;
        }

        q[++rear] = x;
    }

    int remove(){
        if(isEmpty()) {
            cout << "Queue is empty.\n";
            return -1;
        }

        else if(front == rear) {
            int x = q[front];
            front = rear = -1;
            return x;
        }

        return q[front++];
    }
};

// graph
class Graph{
    public:
        int mat[M][M];
        int V;

        Graph(int v) {
            cout << "Graph of " << v << " vertices has been initialized.\n";
            V = v;
            create();
        }

        void create();
        void addEdge(int, int);
        void BFS(int);
        void DFS(int);
        void bfsTraversal(int,bool[]);
        void dfsTraversal(int,bool[]);
};

void Graph::addEdge(int i,int j) {
    mat[i][j] = mat[j][i] = 1;
}

void Graph::create(){
    for (int i = 0; i < V - 1;i++){
        for (int j = i + 1; j < V;j++){
            cout << "Is there edge b/w " << i << " & " << j << " : ";
            bool is;
            cin >> is;
            if(is)
                addEdge(i, j);
        }
    }
}

void Graph::BFS(int src){

    bool vis[V] = {false};
    cout << "BFS :";

    bfsTraversal(src, vis);

    for (int i = 0; i < V;i++){
        if(!vis[i])
            bfsTraversal(i, vis);
    }
    cout << ".\n";
}

void Graph::bfsTraversal(int src, bool vis[]) {

    Queue q;

    q.add(src);

    while(!q.isEmpty()) {

        int curr = q.remove();

        if(!vis[curr]) {
            cout << " " << curr;
            vis[curr] = true;

            for (int i = 0; i < V;i++){

                if(!vis[i] && mat[curr][i] == 1){
                    q.add(i);
                }
            }
        }
    }
}

void Graph::DFS(int src){

    bool vis[V] = {false};
    cout << "DFS :";

    dfsTraversal(src, vis);

    for (int i = 0; i < V;i++){
        if(!vis[i])
            dfsTraversal(i, vis);
    }
    cout << ".\n";
}

void Graph::dfsTraversal(int src, bool vis[]){

    Stack s;
    s.push(src);

    while(!s.isEmpty()){
        int curr = s.peek();
        s.pop();

        if(!vis[curr]) {

            vis[curr] = true;
            cout << " " << curr;

            for (int i = 0; i < V;i++){
                if(mat[curr][i]==1&&!vis[i] )
                    s.push(i);
            }
        }
    }
}

int main(){

    Graph graph(7);
    
    graph.BFS(0);
    graph.DFS(0);
}