/*
A Dictionary stores keywords and its meanings. 
Provide facility for 
adding new keywords, 
deleting keywords, 
updating values of any entry 
Provide facility to display whole data sorted in ascending/ Descending order 
Also find how many maximum comparisons may require for finding any keyword. 
Use Height balance tree and find the complexity for finding a keyword
*/

#include<iostream>
using namespace std;
#define null NULL

class Node{
	public:
	string keyword;
	string meaning;
	Node*left,*right;
	
	Node(string keyword){
		this->keyword = keyword;
		cout << "Enter meaning of \"" << keyword << "\" : ";
		cin >> this->meaning;
		left = right = null;
	}
};

class AVL{
	public:
	
	Node* root;
	
	AVL(){
		root = null;
	}
	
	void display(Node*x);
	
	void preOrder(Node*);
	void inOrder(Node*);
	void postOrder(Node*);
	void ascending(Node*);
	void descending(Node*);
	
	Node*insert(Node*, string);
	Node* remove(Node*, string);   
	Node* inSuccessor(Node*);
	
	Node* right_rotate(Node*);
	Node* left_rotate(Node*);
	Node* LL(Node*);
	Node* LR(Node*);
	Node* RL(Node*);
	Node* RR(Node*);
	
	Node* balanceAVL(Node*);
	int height(Node*);
	int balFact(Node*);

	void update(string);
	Node* search(string, bool);
	
};

/*				traversals			*/
void AVL::preOrder(Node* t){
	if(t!=null){
		cout << t->keyword << " ";
		preOrder(t->left);
		preOrder(t->right);
	}
}
void AVL::inOrder(Node* t){
	if(t!=null){
		inOrder(t->left);
		cout << t->keyword << " ";
		inOrder(t->right);
	}
}

void AVL::postOrder(Node* t){
	if(t!=null){
		postOrder(t->left);
		postOrder(t->right);
		cout << t->keyword << " ";
	}
}

void AVL::ascending(Node* t){
	if(t!=null){
		ascending(t->left);
		cout << t->keyword << " : " << t->meaning << endl;
		ascending(t->right);
	}	
}

void AVL::descending(Node* t){
	if(t!=null){
		descending(t->right);
		cout << t->keyword << " : " << t->meaning << endl;
		descending(t->left);
	}	
}

/*				search and update			*/
Node* AVL::search(string key, bool flag){
	int probe = 0;
	Node* temp = root;
	while(temp!=null){
		probe++;
		if(key < temp->keyword) {
			temp = temp->left;
		} else if(temp->keyword < key) {
			temp = temp->right;
		} else {
			if(flag)
				cout << "\"" << key << "\" found with probe = " << probe << endl;
			return temp;
		}
	}
	if(flag)
		cout << "\" " << key << "\" not found with probe = " << ++probe << endl;
	return temp;
}

void AVL::update(string key){
	Node* node = search(key,false);
	
	if(node!=null){
		string mean;
		cout << "Enter new meaning of \"" << key << "\" : ";
		cin >> mean;
		
		cout << "Before Updation : " << node->keyword << " : " << node->meaning << endl;
		node-> meaning = mean;
		cout << "After Updation : " << node->keyword << " : " << node->meaning << endl;
	} else {
		bool add;
		cout << "\"" << key << "\" not found in AVL.\nPress 1 to insert it : ";
		cin >> add;
		if(add){
			root = insert(root,key);
		}
	}
}

/*				rotations			*/
Node* AVL::right_rotate(Node* x){
	display(x);
	cout << "Performing right rotation with pivot : \"" << x->keyword << "\"\n";
	Node* y = x->left;
	x->left = y->right;
	y->right = x;
	display(y);
	return y;
}

Node* AVL::left_rotate(Node* x){
	display(x);
	cout << "Performing left rotation with pivot : \"" << x->keyword << "\"\n";
	Node* y = x->right;
	x->right = y->left;
	y->left = x;
	display(y);
	return y;
}

Node* AVL::LL(Node* x){
	cout << "\nLL Case\n";
	return right_rotate(x);
}

Node* AVL::LR(Node* x){
	cout << "\nLR Case\n";
	x->left = left_rotate(x->left);
	return right_rotate(x);
}

Node* AVL::RL(Node* x){
	cout << "\nRL Case\n";
	x->right = right_rotate(x->right);
	return left_rotate(x);
}

Node* AVL::RR(Node* x){
	cout << "\nRR Case\n";
	return left_rotate(x);
}

/*				height,balFact			*/
int AVL::height(Node* t){
	if(t==null)
		return 0;
	return max(height(t->left),height(t->right))+1;
}

int AVL::balFact(Node* t){
	return height(t->left)-height(t->right);
}

/*				insert,remove,balanceAVL			*/
Node* AVL::insert(Node* node, string key){
	if(node==null)
		return new Node(key);
	
	if(key < node->keyword)
		node->left = insert(node->left, key);
	else if(node->keyword < key)
		node->right = insert(node->right, key);
	else {
		cout << "Data already exists.\nDuplicates not allowed.\n";
		return node;
	}
	return balanceAVL(node);
}

Node* AVL::remove(Node* node, string key){
	if(node==null)
		return node;
	
	else if (key < node->keyword)
		node->left = remove(node->left,key);
	else if(node->keyword < key)
		node->right = remove(node->right, key);
	
	else {
		
		// case 1 : 0 childs
		if(node->left == null && node->right == null){
			delete node;
			return null;
		}
		
		//case 2 : single child
		else if(node->right == null){
			Node* temp = node->left;
			delete node;
			return temp;
		}
		else if(node->left == null){
			Node* temp = node->right;
			delete node;
			return temp;
		}
		
		// case 3 : 2 children
		else {
			Node* IS = inSuccessor(node);
			
			// copy IS to node
			node->keyword = IS->keyword;
			node->meaning = IS->meaning;
			
			// delete in. order successor
			node->right = remove(node->right,IS->keyword);
		}
	}
	return balanceAVL(node);
}

Node* AVL::inSuccessor(Node* t){
	t = t->right;
	while(t->left != null)
		t = t->left;
	return t;
}

Node* AVL::balanceAVL(Node* node){
	int bf = balFact(node);
	
	if(bf == 2){
		if(balFact(node->left) >=0)
			return LL(node);
		return LR(node);
	} else if (bf==-2){
		if(balFact(node->right)<=0)
			return RR(node);
		return RL(node);
	}
	return node;
}

void AVL::display(Node*x){
	cout << "\t\t|\t\n";
	cout <<" \t"  <<x->keyword<<endl;
	cout << " \t    /\t  \\\n";
	cout << " \t " << ((x->left==null)?"null":x->left->keyword);
	cout << "   " <<((x->right==null)?"null":x->right->keyword) << endl;
	cout << endl;
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
			 <<"5-print ascending\n"
			 <<"6-print descending\n"
			 <<"7-traversals\n"
			 <<"0-terminate\n"
			 <<"Enter your choice : ";
			 
		cin >> ch;
		
		switch(ch){
			
			case 0:
				cout << "* T E R M I N A T I N G *\n";
				return 0;
				
			case 1:                          
				cout << "How many word : ";
				cin >> ch;
				for(int i=0; i<ch; i++){
					cout << "Enter word to be inserted : ";
					cin >> x;
					avl.root = avl.insert(avl.root,x);
				}
				
				break;
				
			case 2:
				cout << "Enter word to be deleted : ";
				cin >> x;
				avl.root = avl.remove(avl.root,x);
				break;

			case 3:
				cout << "Enter word to be updated : ";
				cin >> x;
				avl.update(x);
				break;
				
			case 4:
				cout << "Enter word to be searched : ";
				cin >> x;
				avl.search(x,true);
				break;

			case 5:
				cout << "Ascending Dictionary : \n";
				avl.ascending(avl.root);
				break;
				
			case 6:
				cout << "Descending Dictionary : \n";
				avl.descending(avl.root);
				break;
				
			case 7:
				cout << "Pre-Order : ";
				avl.preOrder(avl.root);		cout << endl;
				cout << "In-Order : ";
				avl.inOrder(avl.root);		cout << endl;
				cout << "Post-Order : ";
				avl.postOrder(avl.root); 	cout << endl;				
				break;
				
			default:
				cout << "Try Again.\n";
		}
		
	}
}
