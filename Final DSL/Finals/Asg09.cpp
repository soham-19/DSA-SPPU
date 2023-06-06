/*
A Dictionary stores keywords and its meanings. 
Provide facility for adding new keywords, 
deleting keywords, 
updating values of any entry 
Provide facility to display whole data sorted in ascending/ Descending order 
Also find how many maximum comparisons may require for finding any keyword. 
Use Height balance tree and find the complexity for finding a keyword
*/
#include<iostream>
using namespace std;
#define SPACE 10

class Node{
	public:
		Node* left;
		string keyword;
		string meaning;
		Node* right;
		
		Node(string keyword){
			this->keyword = keyword;
			cout << "Enter meaning of \"" << this->keyword << "\" : ";
			cin.ignore();
			getline(cin,this->meaning);
			left = right = NULL;
		}
};

class AVL{
	public:
		Node* root;
		
		AVL(){
			root = NULL;
		}
		
		// traversals
		void preOrder(Node*);
		void inOrder(Node*);
		void postOrder(Node*);
		void asc(Node*);
		void dsc(Node*);
		
		// search update
		Node* search(string, bool);
		void update(string);
		
		//insert delete successor
		Node* insert(Node*,string);
		Node* remove(Node*,string);
		Node* successor(Node*);
		
		//balanceAVL
		Node* balanceAVL(Node*);
		
		// rotations
		Node* right_rotate(Node*);
		Node* left_rotate(Node*);
		Node* RR(Node*);
		Node* RL(Node*);
		Node* LR(Node*);
		Node* LL(Node*);
		
		// height bf
		int height(Node*);
		int balFact(Node*);
		
		// display
		void printTree(Node*, int);
		
};

void AVL::printTree(Node * root, int space) {
        // Base case 
        if (root == NULL){
            return;
        } 

        space += SPACE; // to increase the amount of padding as tree grows larger

        printTree(root -> right, space); // Print Right child 

        cout << endl; // print a blank line

        // Printing the blank spaces before each node
        for (int i = SPACE; i < space; i++){
            cout << " "; 
        }

        //Print the value
        cout << root -> keyword << "\n"; 

        printTree(root -> left, space); // Print Right Child
    }

// traversals
void AVL::preOrder(Node* t){
	if( t!= NULL){
		cout << t->keyword << " ";
		preOrder(t->left);
		preOrder(t->right);
	}
}

void AVL::inOrder(Node* t){
	if( t!= NULL){
		inOrder(t->left);
		cout << t->keyword << " ";
		inOrder(t->right);
	}
}

void AVL::postOrder(Node* t){
	if( t!= NULL){
		postOrder(t->left);
		postOrder(t->right);
		cout << t->keyword << " ";
	}
}

void AVL::asc(Node* t){
	if( t!= NULL){
		asc(t->left);
		cout << "\t" << t->keyword << " : " << t->meaning << endl;
		asc(t->right);
	}
}

void AVL::dsc(Node* t){
	if( t!= NULL){
		dsc(t->right);
		cout << "\t" << t->keyword << " : " << t->meaning << endl;
		dsc(t->left);
	}
}

// search update
Node* AVL::search(string x, bool flag){
	Node* temp = root;
	int probe = 0;
	
	while(temp!=NULL){
		probe++;
		
		if(x < temp->keyword)
			temp = temp->left;
		else if(temp->keyword < x)
			temp = temp->right;
		else {
			if(flag)
				cout << "\"" << x << "\" found with probe = " << probe << endl;
			return temp;
		}
	}
	if(flag)
		cout << "\"" << x << "\" not found with probe = " << ++probe << endl;
	return temp;
}

void AVL::update(string x){
	Node* node = search(x,false);
	
	if(node == NULL){
		bool add;
		cout << "\"" << x << "\" not found in Dictionary\nPress 1 to add it.\n";
		cin >> add;
		if(add){
			root = insert(root,x);
		}
	} else {
		string mean;
		cout << "Enter new meaning of \"" << x << "\" : ";
		cin.ignore();
		getline(cin,mean);
		cout << "\nBefore Updation " << node->keyword << " : " << node->meaning << endl;
		node->meaning = mean;
		cout << "\nAfter Updation " << node->keyword << " : " << node->meaning << endl;
	}
}

// insert delete successor
Node* AVL::insert(Node* node, string x){
	if(node==NULL){
		return new Node(x);
	}
	
	if(x < node->keyword){
		node->left = insert(node->left, x);
	} else if(node->keyword < x){
		node->right = insert(node->right, x);
	} else {
		cout << "Data exists already.\nDuplicates not allowed.\n";
		return node;
	}
	
	return balanceAVL(node);
}

Node* AVL::remove(Node* node, string x){
	if(node==NULL){
		return node;
	}
	
	else if(x < node->keyword){
		node->left = remove(node->left,x);
	} else if ( node->keyword < x){
		node->right = remove(node->right,x);
	} else {
		
		if(node->left == NULL && node->right == NULL){	// case 1 : 0 children
			delete node;
			return NULL;
		} else if(node->left == NULL){					// case 2: 1 child only  				
			Node* temp = node->right;
			delete node;
			return temp;
		} else if(node->right == NULL) {
			Node* temp = node->left;
			delete node;
			return temp;
		} else {										// case 3: 2 children
			
			Node* IS = successor(node->right);
			node->keyword = IS->keyword;
			node->meaning = IS->meaning;
			
			node->right = remove(node->right, IS->keyword);			
		}
	}
	return balanceAVL(node);
}

Node* AVL::successor(Node* t){
	while(t->left != NULL)
		t = t->left;
	return t;
}

// balanceAVL
Node* AVL::balanceAVL(Node* node){
	int bf = balFact(node);
	
	if(bf == 2){
		if(balFact(node->left) >=0)
			return LL(node);
		return LR(node);
		
	}else if(bf==-2){
		if(balFact(node->right) <=0)
			return RR(node);
		return RL(node);		
	}
	return node;
}

// rotations
Node* AVL::right_rotate(Node* x){
	// cout << "Before : \n";
	// display(x);
	cout << "preforming right-rotation about \"" << x->keyword << "\"\n";
	Node* y = x->left;
	x->left = y->right;
	y->right = x;
	// cout << "After : \n";
	// display(y);
	return y;
}

Node* AVL::left_rotate(Node* x){
	// cout << "Before : \n";
	// display(x);
	cout << "preforming left-rotation about \"" << x->keyword << "\"\n";
	Node* y = x->right;
	x->right = y->left;
	y->left = x;
	// cout << "After : \n";
	// display(y);
	return y;
}

Node* AVL::LL(Node* x){
	cout << "\t**LL Case for \"" << x->keyword << "\"" << "\n";
	return right_rotate(x);
}

Node* AVL::RR(Node* x){
	cout << "\t**RR Case for \"" << x->keyword << "\"" << "\n";
	return left_rotate(x);
}

Node* AVL::LR(Node* x){
	cout << "\t**LR Case for \"" << x->keyword << "\"" << "\n";
	x->left = left_rotate(x->left);
	return right_rotate(x);
}

Node* AVL::RL(Node* x){
	cout << "\t**RL Case for \"" << x->keyword << "\"" << "\n";
	x->right = right_rotate(x->right);                    
	return left_rotate(x);
}

// height bf
int AVL::height(Node* t){
	if(t==NULL)
		return 0;
	return max(height(t->left),height(t->right))+1;
}

int AVL::balFact(Node* x){
	return height(x->left) - height(x->right);
}

int main(){
	
	int ch;
	string x;
	
	AVL avl;
	
	while(true){
		
		cout << "	* A V L *\n"
			 << "1-insert\n"
			 <<"2-delete\n"
			 <<"3-update\n"
			 <<"4-search\n"
			 <<"5-display ascending\n"
			 <<"6-display descending\n"
			 <<"7-traversals\n"
			 <<"0-terminate\n"
			 <<"\nEnter your choice : ";
		cin >> ch;
		cout << endl;
		
		switch(ch){
			case 0:
				cout << "	T E R M I N A T I N G\n";
				return 0;
			case 1:
				cout << "How many words : ";
				cin >> ch;
				for(int i=0; i<ch;i++){
					cout << "Enter the word to be inserted : ";
					cin >> x;
					avl.root = avl.insert(avl.root, x);
				}	
					avl.printTree(avl.root, 0);
				break;
			case 2:
				cout << "Enter the word to be deleted : ";
				cin >> x;
				avl.root = avl.remove(avl.root, x);
				avl.printTree(avl.root, 0);
				break;
			case 3:
				cout << "Enter the word to be updated : ";
				cin >> x;
				avl.update(x);
				break;	
			case 4:
				cout << "Enter the word to be searched : ";
				cin >> x;
				avl.search(x,true);
				break;	
			case 5:
				cout << "Ascending Order Dictionary : \n";
				avl.asc(avl.root);
				break;
			case 6:
				cout << "Descending Order Dictionary : \n";
				avl.dsc(avl.root);
				break;	
			case 7:
				cout << "PreOrder :\t ";
				avl.preOrder(avl.root);
				cout << endl;
				cout << "InOrder :\t ";
				avl.inOrder(avl.root);
				cout << endl;
				cout << "PostOrder :\t ";
				avl.postOrder(avl.root);
				cout << endl;
				cout << "Tree is : \n";
				avl.printTree(avl.root, 0);
				break;
			default:
				cout << "Invalid Choice!!\nTry Again!!\n\n";
		}
	}
	
}