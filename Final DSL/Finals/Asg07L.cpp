/*
Represent a given graph using adjacency matrix/list to 
perform DFS and using adjacency list to perform BFS. 
Use the map of the area around the college as the graph. Identify the prominent land marks 
as nodes and perform DFS and BFS on that
*/

#include<iostream>
using namespace std;
#define M 100

class Stack{
	int top;
	int stack[M];
	public:
	Stack(){
		top = -1;
	}
	bool isEmpty(){
		return top==-1;
	}
	bool isFull(){
		return top == M-1;
	}
	void push(int x){
		if(isFull()){
			cout << "StackFull\n";
		} else {
			stack[++top] = x;
		}
	}
	int pop(){
		if(isEmpty()){
			cout << "StackEmpty\n";
			return -1;
		}
		return stack[top--];
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
		return front == -1 && rear==-1;
	}
	bool isFull(){
		return rear==M-1;
	}
	void add(int x){
		if(isFull()){
			cout << "QueueFull\n";
		} else {
			if(isEmpty())
				front++;
			queue[++rear] = x;
		}
	}
	int remove(){
		int val = -1;
		if(isEmpty()){
			cout << "QueueEmpty\n";
		} else {
			val = queue[front];
			if(front == rear){
				front = rear = -1;
			} else {
				front++;
			}
		}
		return val;
	}
};

class Edge{
	public:
	int dest;
	
	Edge(int d){
		this->dest = d;
	}
};

class Node{
	public:
	
	Edge* edge;
	Node* next;
	
	Node(Edge*e){
		edge = e;
		next = NULL;
	}
};

class List{
	public:
	
	Node *head;
	Node *tail;
	string block;
	
	List(){
		head = tail = NULL;
	}
	
	void push_back(Edge*e){
		if(head == NULL){
			head = tail = new Node(e);
		} else {
			tail->next = new Node(e);
			tail = tail->next;
		}
	}
	void deleteLL(){
		Node * curr = head;
		while(curr != NULL){
			Node* temp = head;
			curr = curr->next;
			delete temp->edge;
			delete temp;
		}
		head = tail = NULL;
		block = "";
	}
};

class Graph{
	public:
	int v;
	List adjlist[M];
	void setBlocks();
	void setGraph();
	void clearGraph();
	void addEdge(int,int);
	
	void BFS();
	void DFS();
	void bfs(int, bool[]);
	void dfs(int, bool[]);
	
};

void Graph::clearGraph(){
	for(int i=0;i<v;i++)
		adjlist[i].deleteLL();
}

void Graph::setBlocks(){
	cout << "Enter block names : ";
	cin.ignore();
	for(int i=0; i<v; i++){
		cout << " Block " << i+1 << " : ";
		getline(cin, adjlist[i].block);		
	}
	cout << "Locations stored successfully.\n";
}

void Graph::setGraph(){
	cout << "Enter number of vertices : ";
	cin >> v;
	clearGraph();	
	setBlocks();

	
	bool add;
	for(int i=0; i<v; i++){
		for(int j=i+1; j<v; j++){
			cout << "Is there path between \"" << adjlist[i].block << "\" & \"" << adjlist[j].block << "\" ? ";
			cin >> add;
			if(add){
				addEdge(i,j);
			}
		}
	}
}

void Graph::addEdge(int i, int j){
	adjlist[i].push_back(new Edge(j));
	adjlist[j].push_back(new Edge(i));
}

void Graph::BFS(){
	int src;
	cout << "Enter source for BFS : ";
	cin >> src;
	src--;	
	cout << " BFS : ";
	bool vis[v] = {false};
	bfs(src,vis);
	
	for(int i=0; i<v;i++){
		if(!vis[i])
			bfs(i,vis);
	}
	cout << endl << endl;
}

void Graph::DFS(){
	int src;
	cout << "Enter source for DFS : ";
	cin >> src;	
	src--;
	cout << " DFS : ";
	bool vis[v] = {false};
	dfs(src,vis);
	
	for(int i=0; i<v;i++){
		if(!vis[i])
			dfs(i,vis);
	}
	cout << endl << endl;
}

void Graph::bfs(int src, bool vis[]){
	Queue q;
	q.add(src);
	
	while(!q.isEmpty()){
		
		int curr = q.remove();
		
		if(!vis[curr]){
			
			vis[curr] = true;
			cout << "\"" << adjlist[curr].block << "\"" << " ";
			
			Node* temp = adjlist[curr].head;
			while(temp != NULL){
				if(!vis[temp->edge->dest])
					q.add(temp->edge->dest);
				temp = temp->next;
			}
		}
	}
}

void Graph::dfs(int src, bool vis[]){
	Stack s;
	s.push(src);
	
	while(!s.isEmpty()){
		
		int curr = s.pop();
		
		if(!vis[curr]) {
			
			vis[curr]  = true;
			cout << "\"" << adjlist[curr].block << "\" ";
			
			Node * temp = adjlist[curr].head;
			while(temp != NULL){
				if(!vis[temp->edge->dest])
					s.push(temp->edge->dest);
				temp = temp->next;
			}
		}
	}
}

int main(){
	
	int ch;
	Graph g;

	while(true) {
	
	cout << "G R A P H\n"
		 << "  1-set system\n"
		 << "  2-bfs\n"
		 << "  3-dfs\n\n"
		 << " Enter your choice : ";
	
	cin >> ch;
	
	switch(ch) {
		
		case 0:
			cout << " T E R M I N A T I N G\n";
			return 0;
		case 1:
			g.setGraph();
			break;
		case 2:
			g.BFS();
			break;
		case 3:
			g.DFS();
			break;
		default:
			cout << "Try Again!!\n";
	}
	
	}
	
}


