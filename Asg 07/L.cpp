/*
Represent a given graph using adjacency matrix/list to perform DFS and using adjacency list to perform BFS. Use the map of the area around the college as the graph. Identify the prominent land marks as nodes and perform DFS and BFS on that
*/
#include<iostream>
#include<queue>
using namespace std;
#define MAX_SIZE 100

// ---------------------- Stack ----------------------
class Stack {
private:
    int top;
    int arr[MAX_SIZE];

public:
    Stack() {
        top = -1;
    }

    bool isEmpty() {
        return (top == -1);
    }

    bool isFull() {
        return (top == MAX_SIZE - 1);
    }

    void push(int value) {
        if (isFull()) {
            cout << "Stack is full. Cannot push." << std::endl;
            return;
        }

        arr[++top] = value;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack is empty. Cannot pop." << std::endl;
            return -1;
        }

        return arr[top--];
    }

    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty. Cannot peek." << std::endl;
            return -1;
        }

        return arr[top];
    }
};

// ---------------------- Stack ----------------------
// ---------------------- Queue ----------------------
class Queue {
private:
    int front;
    int rear;
    int arr[MAX_SIZE];

public:
    Queue() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() {
        return (front == -1 && rear == -1);
    }

    bool isFull() {
        return (rear == MAX_SIZE - 1);
    }

    void add(int value) {
        if (isFull()) {
            cout << "Queue is full. Cannot enqueue." << std::endl;
            return;
        }

        if (isEmpty()) {
            front = 0;
        }

        arr[++rear] = value;
    }

    int remove() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue." << endl;
            return -1;
        }

        int val = arr[front];
        
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front++;
        }

        return val;
    }
};
// ---------------------- Queue ----------------------

class Graph{
    int V;
    int mat[MAX_SIZE][MAX_SIZE];

    public:
    Graph(int v){
        cout << "Graph has been created.\n";
        V = v;
        for (int i = 0; i < v;i++){
            for (int j = 0; j < v;j++)
                mat[i][j] = 0;
        }
        createGraph();
    }
    void p(){
        for (int i = 0; i < V;i++){
            for (int j = 0; j < V;j++){
                cout << mat[i][j] <<  " ";
            }
            cout << endl;
        }
    }

    void createGraph();
    void addEdge(int, int);
    void bfsUtil(int,bool[]);
    void dfsUtil(int,bool[]);
    void DFS(int);
    void BFS(int);
};
void Graph::addEdge(int i,int j){
        cout << "Is there path from " << i << " to " << j << " ? ";
        char ch;
        cin >> ch;
        if(ch=='y' || ch=='Y'){
            mat[i][j] = mat[j][i] = 1;
        }
}

void Graph::createGraph(){
    for (int i = 0; i < V - 1;i++){
        for (int j = i + 1; j < V;j++){
            addEdge(i, j);
        }
    }
    cout << "All data stored.\n";
}
void Graph::BFS(int src){
    bool visited[V] = {false};
    cout << "BFS : ";
    bfsUtil(src, visited);
    for (int i = 0; i < V;i++){
        if(!visited[i])
            bfsUtil(i, visited);
    }
    cout << endl;
}
void Graph::bfsUtil(int src, bool visited[]) {

    Queue q;

    q.add(src);
    while (!q.isEmpty()) {

        int curr = q.remove();

        if(visited[curr] == false) {

            visited[curr] = true;
            cout << curr << " ";

            for (int v = 0; v < V; v++) {
                if (mat[curr][v]==1 && !visited[v]) {
                    q.add(v);
                }
            }
        }

    }
}

void Graph::DFS(int src){
    cout << "DFS : ";
    bool visited[V] = {false};
    dfsUtil(src,visited);
    for (int i = 0; i < V;i++){
        if(!visited[i])
            dfsUtil(i,visited);
    }
    cout << endl;
}

void Graph::dfsUtil(int i, bool visited[]) {

    Stack s;
    // Start with the first vertex
    s.push(i);
    while (!s.isEmpty()) {
        int curr = s.pop();

        if (!visited[curr]) {
            visited[curr] = true;

            cout << curr << " ";

            // Push unvisited adjacent vertices onto the stack
            for (int v = 0; v <V; v++) {
                if (mat[curr][v] == 1 && !visited[v]) {
                    s.push(v);
                }
            }
        }
    }

}
int main(){

    int v;
    cout << "Enter number of vertices : ";
    cin >> v;
    Graph *g = new Graph(v);

    cout << "Enter source for BFS : ";
    cin >> v;
    g->BFS(v);
    cout << "Enter source for DFS : ";
    cin >> v;
    g->DFS(v);

}