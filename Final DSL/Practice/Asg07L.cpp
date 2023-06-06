/*
Represent a given graph using adjacency matrix/list to perform DFS and using adjacency list to perform BFS. Use the map of the area around the college as the graph. Identify the prominent land marks as nodes and perform DFS and BFS on that
*/

// class stack, queue, edge, node, list, graph
#include<iostream>
using namespace std;
#define M 100
#define null NULL

class Stack{
    int top;
    int stack[M];

    public:
    Stack(){
        top = -1;
    }
    bool isEmpty(){
        return top == -1;
    }
    bool isFull(){
        return top == M - 1;
    }
    void push(int x) {
        if(isFull()){
            cout << "StackFull.\n";
        } else {
            stack[++top] = x;
        }
    }

    void pop(){
        if(isEmpty()){
            cout << "StackEmpty.\n";
        } else{
            top--;
        }
    }
    int peek(){
        if(isEmpty()){
            cout << "StackEmpty.\n";
            return -1;
        } else{
            return stack[top];
        }
    }
};

class Queue{
    int front;
    int rear;
    int queue[M];
    public:
    Queue(){
        front = rear = -1;
    }
    bool isEmpty(){
        return front == -1 && rear == -1;
    }
    bool isFull(){
        return rear == M - 1;
    }
    void add(int x) {
        if(isFull()){
            cout << "QueueFull.\n";
        } else {
            if(isEmpty()){
                front++;
            }
            queue[++rear] = x;
        }
    }
    int remove(){
        int val = -1;
        if(isEmpty()){
            cout << "QueueEmpty.\n";
        } else {
            val = queue[front];
            if(front==rear){
                front = rear = -1;
            } else {
                front++;
            }
        }
        return val;
    }
};

// class edge->node->list->graph

class Edge{
    public:
    int dest;
    Edge(int d){
        dest = d;
    }
};

class Node{
    public:
    Edge *edge;
    Node *next;
    Node(Edge*e){
        edge = e;
        next = null;
    }
};

class List{
    public:
    string title;
    Node *head, *tail;

    List(){
        head = tail = null;
    }

    void pushback(Edge*e){
        if(head==null){
            head = tail = new Node(e);
        } else {
            tail->next = new Node(e);
            tail = tail->next;
        }

    }
};

class Graph{
    int v;
    List adjList[M];

    void bfsUtil(int, bool[]);
    void dfsUtil(int, bool[]);

public:
    void setNodes();
    void createGraph();
    void addEdge(int, int);
    void BFS(int);
    void DFS(int);

    Graph(int v){
        this->v = v;
        setNodes();
    }
};

void Graph::setNodes(){
    cout << "Enter node identifiers : \n";
    for (int i = 0; i < v;i++){
        cout << "\t Node " << i << " : ";
        cin >> adjList[i].title;
    }
    cout << "Nodes stored successfully.\n";
}

void Graph::addEdge(int i,int j){
    Edge *e = new Edge(j);
    adjList[i].pushback(e);
    e = new Edge(i);
    adjList[j].pushback(e);
}

void Graph::createGraph(){
    bool isFlight;
    for (int i = 0; i < v;i++){
        for (int j = i + 1; j < v;j++){
            cout << "\tEdge b/w \"" << adjList[i].title << "\" & \"" << adjList[j].title << " ? ";
            cin >> isFlight;
            if(isFlight){
                addEdge(i, j);
            }
        }
    }
}

void Graph::BFS(int src) {
    cout << "Source = " << adjList[src].title << " \tBFS : ";
    bool visited[v] = {false};
    bfsUtil(src, visited);

    for (int i = 0; i < v;i++){
        if(!visited[i]){
            bfsUtil(i, visited);
        }
    }
    cout << endl;
}

void Graph::bfsUtil(int src,bool visited[]) {
    Queue q;
    q.add(src);

    while(!q.isEmpty()){

        int curr = q.remove();

        if(!visited[curr]) {

            cout << adjList[curr].title << " ";
            visited[curr] = true;

            Node *temp = adjList[curr].head;
            while(temp!=null){
                if(!visited[temp->edge->dest]) {
                    q.add(temp->edge->dest);
                }
                temp = temp->next;
            }
        }
    }
}

void Graph::DFS(int src){

    cout << "Source = " << adjList[src].title << " \tDFS : ";
    bool visited[v] = {false};
    dfsUtil(src, visited);

    for (int i = 0; i < v;i++){
        if(!visited[i]) {
            dfsUtil(i, visited);
        }
    }
    cout << endl;
}

void Graph::dfsUtil(int src, bool visited[]) {
    Stack s;
    s.push(src);

    while(!s.isEmpty()){

        int curr = s.peek();
        s.pop();

        if(!visited[curr]) {

            visited[curr] = true;
            cout << adjList[curr].title << " ";

            Node *temp = adjList[curr].head;
            while(temp!=null){
                if(!visited[temp->edge->dest]) {
                    s.push(temp->edge->dest);
                }
                temp = temp->next;
            }
        }
    }
}

int main(){
    int v;
    int ch,src,dest;
    cout << "Enter number of vertices : ";
    cin >> v;

    Graph g(v);

    while(true){
        cout << "   * G R A P H *\n"
             << "1-create a graph\n"
             << "2-add a edge\n"
             << "3-perform bfs\n"
             << "4-perform dfs\n"
             << "0-terminate\n"
             << "Enter your choice : ";

        cin >> ch;

        switch(ch){

            case 0:
                cout << " T E R M I N A T I N G\n";
                return 0;

            case 1:
                g.createGraph();
                break;
            case 2:
                cout << "Enter the source : ";
                cin >> src;
                cout << "Enter the destination : ";
                cin >> dest;
                g.addEdge(src, dest);
                break;
            case 3:
                // cout << "Enter the source : ";
                for (int i = 0; i < 6;i++){
                    // cout << "Source : " << i << ": \n\t";
                    g.BFS(i);
                }
                // g.BFS(src);
                break;
            case 4:
                // cout << "Enter the source : ";
                for (int i = 0; i < 6;i++){
                    // cout << "Source : " << i << ": \n\t";
                    g.DFS(i);
                }
                // cin >> src;
                // g.DFS(src);
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }
}