/*Construct an expression tree from the given prefix expression eg. +--a*bc/def
 and traverse it using post order traversal
(non recursive ) and then delete the entire tree*/

#include<iostream>
using namespace std;
#define M 100

int len(string s){
	int i;
	for(i=0; s[i] != '\0'; i++){}
	return i;
}

bool isOperator(char ch){
	return ch=='+' || ch=='-' || ch=='*' || ch=='/';
}

bool isAlpha(char ch){
	return (ch>='a' && ch<='z')||(ch>='A' && ch<='Z');
}

class Node{
	public:
	Node* left;
	char ch;
	Node* right;
	
	Node(char ch){
		this->ch = ch;
		left = right = NULL;
	}
};

class Stack{
	public:
		int top;
		Node* stack[M];
		
		Stack(){
			top = -1;
		}
		bool isEmpty(){
			return top == -1;
		}
		void push(Node* n){
			if(top==M-1){
				cout << "StackFull\n";
			}
			stack[++top] = n;			
		}
		Node* pop(){
			if(isEmpty()){
				cout << "StackEmpty\n";
				return NULL;
			}
			return stack[top--];
		}
		
	
};
class ETree{
	public:
	Node* root;
	
	ETree(){
		root = NULL;
	}
	
	void build(string prefix) {
		Stack s;
		int n = len(prefix);
		
		for(int i=n-1; i>=0; i--){
			
		    Node* curr = new Node(prefix[i]);
			if(isOperator(prefix[i])){
				curr->left = s.pop();
				curr->right = s.pop();
			}
			s.push(curr);
		}
		
		Node* top = s.pop();
		if(!isOperator(top->ch)){
			cout << "Invalid input.\n";
			root = NULL;
			return;
		}
		root = top;
		cout << "Expression Tree Built successfully.\n";
	}
	
	void postOrder(){
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
		cout << "postOrder : \t";
		while(!s2.isEmpty()){
			cout << s2.pop()->ch;
		}
		cout << endl;
	}
	
	Node* clear(Node* n){
		if(n==NULL)
			return NULL;
		clear(n->left);
		clear(n->right);
		cout << "Deleted " << n->ch << endl;
		delete n;
	}
	void in(Node*t){
		if(t!=NULL){
			in(t->left);
			cout << t->ch;
			in(t->right);
		}
	}
	
	int evaluate(Node* node){
		if(node == NULL)
			return 0;
		
		if(node->left == NULL && node->right == NULL){
			
			if(isAlpha(node->ch)){
				cout << "leaf\n";
				cout << "Enter value of " << node->ch << " : ";
				int x;
				cin >> x;
				return x;
			}
			return node->ch - '0';
		}
		
		int leval = evaluate(node->left);
		int reval = evaluate(node->right);
		
		if(node->ch == '+')
			return leval+reval;
		
		if(node->ch == '-')
			return leval-reval;
		
		if(node->ch == '*')
			return leval*reval;
		
		if(node->ch == '/')
			return leval/reval;			
	}
};
int main(){
	ETree et;
	
	int ch;
	string exp;
	
	while(true){
		
		cout << "Expression Tree\n"
		     << "  1 - build tree from prefix expression\n"
			 << "  2 - display postorder\n"
			 << "  3 - evaluate tree\n"
			 << "  4 - delete expression tree\n\n"
			 << "Enter your choice : ";
		cin >> ch;
		
		if(ch==1){
			cout << "Enter prefix expression ";
			cin >> exp;
			et.build(exp);
			et.in(et.root);
			cout << endl;
		} else if(ch==2){
			et.postOrder();
		} else if(ch==3){
			cout << et.root->ch << endl;
			cout << "Evaluation = " << et.evaluate(et.root) << endl;
		} else if(ch==4) {
			et.clear(et.root);
		} else {
			cout << "Invalid choice\n";
		}
		
	}
}