/*
Beginning with an empty binary search tree, Construct binary search tree by inserting the values in the order given After constructing a binary tree

i Insert new node, 
i. Find number of nodes in longest path from root, 
iii. Minimum data value found in the tree, 
iv Change a tree so that the roles of the left and right pointers are swapped at every node, 
v Search a value
*/

#include<iostream>
using namespace std;
#define M 100

class Node{
	public:
		int val;
		Node* left, * right;
		Node(int x){
			val = x;
			left = right = NULL;
		}
};

class Stack{
	int top;
	Node* stack[M];
	public:
	Stack(){top=-1;}
	
	bool isEmpty(){return top==-1;}
	bool isFull(){return top==M-1;}
	
	void push(Node* x){
		if(isFull()){
			cout << "StackFull\n";
		} else {
			stack[++top] = x;
		}
	}
	Node* pop(){
		if(isEmpty()){
			cout << "StackEmpty\n";
			return NULL;
		}
		return stack[top--];
	}
};

class BST{
	public:
	Node* root;
	BST(){
		root = NULL;
	}
	
	void insert(int);
	int height(Node*);
	void maxPath(Node*);
	void minMax();
	Node* mirror(Node*);
	void search(int);
	void inOrder();
	void preOrder();
	void postOrder();	
};

void BST::insert(int x){
	if(root==NULL){
		root = new Node(x);
		return;
	}
	Node* temp = root;
	while(temp != NULL){
		
		if(x<temp->val){
			if(temp->left == NULL){
				temp->left = new Node(x);
				return;
			}
			temp = temp->left;
		} else if(temp->val < x){
			if(temp->right == NULL){
				temp->right = new Node(x);
				return;
			}
			temp = temp->right;
		} else {
			cout << "Duplicates are not allowed\n";
			return;
		}
	}
}

int BST::height(Node*t){
	if(!t)
		return 0;
	return max(height(t->left),height(t->right))+1;
}

void BST::maxPath(Node* t){
	if(t == NULL){
		cout << "NULL" << endl;
		return;
	}
	cout << t->val << "->";
	if(height(t->left)>=height(t->right)){
		maxPath(t->left);		
	} else {
		maxPath(t->right);
	}
}

void BST::minMax(){
	Node*t = root;
	while(t->left != NULL)
		t = t->left;
	cout << "Minimum = " << t->val << endl;
	t = root;
	while(t->right != NULL)
		t = t->right;
	cout << "Maximum = " << t->val << endl << endl;
}

Node* BST::mirror(Node* t){
	if(t != NULL)
		return t;
	Node* L = mirror(t->left);
	Node* R = mirror(t->right);
	t->left = R;
	t->right = L;
	return t;
}

void BST::search(int x){
	int probe = 0;
	Node* temp = root;
	while(temp){
		++probe;
		if(x<temp->val)
			temp =temp->left;
		else if(temp->val < x)
			temp = temp->right;
		else {
			cout << x << " found with probe = " << probe << endl;
			return;
		}
	}
	cout << x << " not found with probe = " << ++probe << endl;
}

void BST::preOrder(){
	cout << "Pre Order :\t";
	Stack s;
	Node* temp = root;
	
	while(true){
		while(temp!=NULL){
			s.push(temp);
			cout << temp->val << " " ;
			temp = temp->left;			
		}
		if(s.isEmpty()){
			cout << endl << endl;
			return;
		}
		temp = s.pop();
		temp = temp->right;
	}
}

void BST::inOrder(){
	cout << "In Order :\t";
	Stack s;
	Node* temp = root;
	
	while(true){
		while(temp!=NULL){
			s.push(temp);
			temp = temp->left;			
		}
		if(s.isEmpty()){
			cout << endl << endl;
			return;
		}
		temp = s.pop();
		cout << temp->val << " " ;
		temp = temp->right;
	}
}



void BST::postOrder(){
	cout << "Post Order :\t";
	Stack s1, s2;
	s1.push(root);
	while(!s1.isEmpty()){
		
		Node* curr = s1.pop();
		s2.push(curr);
		
		if(curr->left)
			s1.push(curr->left);
		if(curr->right)
			s1.push(curr->right);
	}
	while(!s2.isEmpty()){
		cout << s2.pop()->val << " ";
	}
	cout << endl << endl ;
}

int main(){
	BST b;
	
	int x, ch;
	
	while(true){
		cout << "	* B S T *\n"
			 << "1-insert\n"
			 << "2-search\n"
			 << "3-find minimum and maximum\n"
			 << "4-mirror\n"
			 << "5-maximum path\n"
			 << "6-traverse\n\n"
			 << "Enter your choice : ";
		cin >> ch;
		
		switch(ch){
			
			case 0:
				cout << " T E R M I N A T I N G\n";
				return 0;
			case 1:
				cout << "How many entries do you want to add ? ";
				cin >> ch;
				for(int i=0; i<ch; i++){
					cout << "  Enter element : ";
					cin >> x;
					b.insert(x);
				}
				break;
			case 2:
				cout << "Enter element to be searched : ";
				cin >> x;
				b.search(x);
				break;
			case 3:
				b.minMax();
				break;
			case 4:
				cout << "Before Mirroring : ";
				b.inOrder();
				b.root = b.mirror(b.root);
				cout << "After Mirroring : ";
				b.inOrder();
				break;
			case 5:
				cout << "Nodes in longest path from root = " << b.height(b.root) << endl;
				cout << "Path is : " ;
				b.maxPath(b.root);
				break;
			case 6:
				b.preOrder();
				b.inOrder();
				b.postOrder();
				break;
			default:
				cout << "Invalid choice!\n";			
		}
	}
}