/* A dictionary stores keywords and its meanings. 
Provide facility for adding new keywords, 
					 deleting keywords, 
					 updating keywords of any entry. 
Provide a facility to display whole data sorted in ascending/descending order. 
also find how many maximum comparisions may require for finding any keyword. 
Use BST for implementation.*/


#include<iostream>
using namespace std;
#define M 50

class Node{
	public:
		Node* left;
		string keyword;
		string meaning;
		Node* right;
		
		Node(string word){
			this->keyword = word;
			cout << "Enter meaning of \"" << word << "\" : ";
			
			cin >> this->meaning;
			left = right = NULL;
		}
};

class Stack{
	int top;
	Node* stack[M];
	
	public:
	Stack(){
		top = -1;
	}
	bool isEmpty(){
		return top == -1;
	}
	bool isFull(){
		return top == M-1;
	}
	void push(Node*x){
		if(isFull()){
			cout << "StackFull\n";
		} else {
			stack[++top] = x;
		}	
	}
	Node* pop(){
		if(isEmpty()){
			cout << "StackEmpty.\n";
			return NULL;
		} else {
			return stack[top--];
		}
		
	}
};

class Dict{
	public:
		Node* root;
		Dict(){
			root = NULL;
		}
		
		void preOrder();
		void inOrder();
		void postOrder();
		void ascending();
		void descending();
		Node* search(string,bool);
		void update(string);
		void insert(string);
		Node* remove(Node*,string);
		Node* InOrderSuccessor(Node*);
		
};

void Dict::insert(string x){
	if(root == NULL){
		root = new Node(x);
		return;
	}
	
	Node* temp = root;
	
	while(temp != NULL){
		
		if(x < temp->keyword){
			if(temp->left == NULL){
				temp->left = new Node(x);
				return;
			}
			temp = temp->left;
		}
		else if(temp->keyword < x){
			if(temp->right == NULL){
				temp->right = new Node(x);
				return;
			}
			temp = temp->right;
		} else {
			cout << "Already Present.\n";
			return;
		}
	}
}

Node* Dict::InOrderSuccessor(Node*t){
	t = t->right;
	while(t->left != NULL){
		t = t->left;
	}
	return t;
}

Node* Dict::remove(Node* node, string x) {
	if(node == NULL)
		return node;
	
	if(x < node->keyword)
		node->left = remove(node->left, x);
	else if(node->keyword < x)
		node->right = remove(node->right, x);
	else {
		if(node->left == NULL && node->right == NULL){
			delete node;
			return NULL;           
		}
		else if(node->left == NULL){
			Node* temp = node->right;
			delete node;
			return temp;
		} else if(node->right == NULL){
			Node* temp = node->left;
			delete node;
			return temp;
		} else {
			Node* IS = InOrderSuccessor(node);
			node->keyword = IS->keyword;
			node->meaning = IS->meaning;
			node->right = remove(node->right, IS->keyword);
		}
	}
	return node;
}

Node* Dict::search( string key, bool flag){
	int probe = 0;
	Node* temp = root;
	while(temp!=NULL){
		probe++;
		if(key < temp->keyword)
			temp = temp->left;
		else if(temp->keyword < key)
			temp = temp->right;
		else {
			if(flag)
				cout << "\"" << key << "\" found with probe = " << probe << endl;
			return temp;
		}
	}
	if(flag)
		cout << "\"" << key << "\" not found with probe = " << probe << endl;
	return temp;
}

void Dict::update(string key){
	Node* node = search(key,false);
	if(node){
		string x;
		cout << "Enter new meaning : ";
		cin.ignore();
		getline(cin, x);
		
		cout << "Before Updation : " << node->keyword << " : " << node->meaning << endl;
		node->meaning  = x;
		cout << "After Updation : " << node->keyword << " : " << node->meaning << endl;
	} else {
		bool add;
		cout << "Value not found.\nPress 1 to add : ";
		cin >> add;
		if(add){
			insert(key);
		}
	}
}

void Dict::preOrder(){
	cout << "Pre-Order :\t";
	if(root == NULL){
		cout << "empty tree\n";
		return;
	}
	Stack s;
	Node* temp = root;
	while(true){
		while(temp != NULL){
			cout << temp->keyword << " ";
			s.push(temp);
			temp = temp->left;
		}
		if(s.isEmpty()){
			cout << endl;
			return;
		}
		temp = s.pop();
		temp = temp->right;
	}
}

void Dict::inOrder(){
	cout << "In-Order :\t";
	if(root == NULL){
		cout << "empty tree\n";
		return;
	}
	Stack s;
	Node* temp = root;
	while(true){
		while(temp != NULL){
			s.push(temp);
			temp = temp->left;
		}
		if(s.isEmpty()){
			cout << endl;
			return;
		}		
		temp = s.pop();
		cout << temp->keyword << " ";
		temp = temp->right;
	}
}

void Dict::postOrder(){
	cout << "Post-Order :\t";
	if(root == NULL){
		cout << "empty tree\n";
		return;
	}
	
	Stack s1, s2;
	s1.push(root);
	while(!s1.isEmpty()){
		Node* curr = s1.pop();
		s2.push(curr);
		
		if(curr->left != NULL)
			s1.push(curr->left);
	
		if(curr->right != NULL)
			s1.push(curr->right);
	}
	
	while(!s2.isEmpty()){
		cout << s2.pop()->keyword << " ";
	}
	cout << endl;
}

void Dict::ascending(){
	cout << "Ascending Order Dictionary :\n";
	if(root == NULL){
		cout << "empty tree\n";
		return;
	}
	Stack s;
	Node* temp = root;
	while(true){
		while(temp != NULL){
			s.push(temp);
			temp = temp->left;
		}
		
		if(s.isEmpty()){
			cout << endl;
			return;
		}
		
		temp = s.pop();
		cout << "\t * " <<  temp->keyword << " : " << temp->meaning << endl;
		temp = temp->right;
	}
}

void Dict::descending(){
	cout << "Descending Order Dictionary :\n";
	if(root == NULL){
		cout << "empty tree\n";
		return;
	}
	Stack s;
	Node* temp = root;
	while(true){
		while(temp != NULL){
			s.push(temp);
			temp = temp->right;
		}
		
		if(s.isEmpty()){
			cout << endl;
			return;
		}
		
		temp = s.pop();
		cout << "\t * " <<  temp->keyword << " : " << temp->meaning << endl;
		temp = temp->left;
	}
}

int main(){
	
	Dict d;
	string x;
	int ch;
	
	while(true){
		
		cout << "\t* B S T   D I C T I O N A R Y\n"
			 << "1-insert\n"
			 << "2-update\n"
			 << "3-search\n"
			 << "4-delete\n"
			 << "5-print ascending\n"
			 << "6-print descending\n"
			 << "7-travers the dictionary\n"
			 << "0-terminate\n\n"
			 <<"Enter your choice : ";
		cin >> ch;
		
		switch(ch){
			case 0 : 
				cout << "T E R M I N A T I N G\n";
				return 0;
			case 1:
				cout << "Enter word to be inserted : ";
				cin.ignore();
				getline(cin, x);
				d.insert(x);
				break;
			case 2:
				cout << "Enter word to be update : ";
				cin.ignore();
				getline(cin, x);
				d.update(x);
				break;	
			case 3:
				cout << "Enter word to be searched : ";
				cin.ignore();
				getline(cin, x);
				d.search(x,true);
				break;
			case 4:
				cout << "Enter word to be deleted : ";
				cin.ignore();
				getline(cin, x);
				d.root = d.remove(d.root,x);
				break;
			case 5:
				d.ascending();
				break;
			case 6:
				d.descending();
				break;
			case 7:
				d.preOrder();
				d.inOrder();
				d.postOrder();
			default:
				cout << "Let's Try Again\n";
		}
		
	}
	
}