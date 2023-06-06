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
			return;
		}
		stack[++top] = x;
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
	int front,rear;
	int queue[M];
	public:
	Queue(){
		front = rear = -1;
	}
	bool isEmpty(){
		return front==-1;
	}
	bool isFull(){
		return rear == M-1;
	}
	void add(int x){
		if(isFull()){
			cout << "QueueFull\n";
			return;
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
			} else{
				front++;
			}	
		}
		return val;
	}
};

class Graph{
	private:
		int v;
		string blocks[M];
		bool mat[M][M];
		void clear();
		void addPath(int,int);
		void printBlocks();
		void setBlocks();
	public:
		void setGraph();
		void BFS();
		void DFS();
		void bfs(int, bool[]);
		void dfs(int, bool[]);	
};

void Graph::clear(){
	for(int i=0; i<M; i++){
		for(int j=0; j<M; j++){
			mat[i][j] = false;
		}
	}
}

void Graph::setBlocks(){
	cout << "Enter block names :\n";
	for(int i=0; i<v; i++){
		cout << "Block " << i+1 << " : "; 
		cin>> blocks[i];
	}
	cout << "Locations stored successfully\n";
}

void Graph::addPath(int src, int dest){
	mat[src][dest] = mat[dest][src] = true;
}

void Graph::setGraph(){
	cout << "Enter numbers of vertices : ";
		cin >> v;
		clear();
		setBlocks();	
		for(int i=0; i<v; i++){
			bool isPath;
			for(int j=i+1; j<v;j++){
				cout << "Is there path b/w \"" << blocks[i] << "\" & \"" << blocks[j] << "\" ? ";
				cin >> isPath;
				if(isPath)
					addPath(i,j);
			}
		}
}

void Graph::printBlocks(){
	for(int i=0; i<v; i++){
		cout<< i+1 << " : " << blocks[i] << "\t";
	}
	cout << endl;
}

void Graph::BFS(){
	int src;
	printBlocks();
	cout << "Enter source for traversal : ";
	cin >> src;
	src--;	
	bool visited[v] = {false};
	cout << "BFS : ";
	bfs(src,visited);
	for(int i=0; i<v; i++){
		if(!visited[i]){
			bfs(i,visited);
		}
	}
	cout << endl << endl;
}

void Graph::bfs(int src, bool visited[]){
	Queue q;
	q.add(src);
	
	while(!q.isEmpty()){
		
		int curr = q.remove();
		
		if(!visited[curr]){
			
			visited[curr] = true;
			cout << blocks[curr] << "  ";
			
			for(int i=0; i<v; i++){
				if(!visited[i] && mat[curr][i])
					q.add(i);
			}
		}
	}	
}

void Graph::DFS(){
	int src;
	printBlocks();
	cout << "Enter source for traversal : ";
	cin >> src;
	src--;
	bool visited[v] = {false};
	cout << "DFS : ";
	dfs(src,visited);
	for(int i=0; i<v; i++){
		if(!visited[i]){
			dfs(i,visited);
		}
	}
	cout << endl << endl;
	
}

void Graph::dfs(int src, bool visited[]){

	Stack s;
	s.push(src);

	while(!s.isEmpty()){
		
		int curr = s.pop();
		
		if(!visited[curr]){
			
			visited[curr] = true;
			cout << blocks[curr] << "  ";
			
			for(int i=v-1; i>=0; i--){
				if(!visited[i] && mat[curr][i])
					s.push(i);
			}
		}
	}
} 

int main(){
	int ch;
	
	Graph g;
	
	while(true){
		cout << "	G R A P H   T R A V E R S A L S\n"
		     << "  1 - set the graph\n"
			 << "  2 - perform bfs\n"
			 << "  3 - preform dfs\n\n"
			 << "Enter your choice : ";
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
				cout << "Try Again\n";
		}
	}
}

