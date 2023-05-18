/*
A Dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry Provide facility to display whole data sorted in ascending/ Descending order Also find how many maximum comparisons may require for finding any keyword. Use Height balance tree and find the complexity for finding a keyword
*/

#include<iostream>
using namespace std;

class Node {
  public:
    string keyword;
    string meaning;
    int ht;
    Node* left;
    Node* right;

    Node(string key, string value) {
        keyword = key;
        meaning = value;
        ht = 0;
        left = NULL;
        right = NULL;
    }
};

class AVL {
  public:
    Node *root;

    AVL(){
      root = NULL;
    }

	int height(Node *t);
	int BF(Node *t);
	void inOrder(Node *t);
	Node *rotateRight(Node *t);
	Node *rotateLeft(Node *t);
	Node* LL(Node* t);
	Node* RR(Node* t);
	Node* LR(Node* t);
	Node* RL(Node* t);
	Node* insert(Node*,string,string);
};

int AVL::height(Node*t){
	if(t==NULL){
		return 0;
	} /*else if(t->left==NULL && t->right==NULL)
		return 0;*/
	return max(height(t->left), height(t->right)) + 1;
}

int AVL::BF(Node*t){
/*
	if(t==NULL){
		return 0;
	}
	int lh, rh;

	if(t->left==NULL){
		lh = 1;
	} else {
		lh = t->left->ht + 1;
	}

	if(t->right==NULL){
		rh = 1;
	} else {
		rh = t->right->ht + 1;
	}
	cout << "Curr bf = " <<lh - rh << endl;*/
	/*return lh - rh;*/
	cout << "Curr bf = " <<height(t->left)-height(t->right) << endl;
	return height(t->left)-height(t->right);
}

void AVL::inOrder(Node*root){
	if(root==NULL)
		return;
	cout << root->keyword << " : " << root->ht << " ";
	inOrder(root->left);
	inOrder(root->right);
}

Node* AVL::rotateRight(Node*x){

	Node * y;

	y= x->left;
	x->left = y->right;
	y->right = x;

	x->ht = height(x);
	y->ht = height(y);

	return y;
}

Node* AVL::rotateLeft(Node*x){

	Node * y;

	y= x->right;
	x->right = y->left;
	y->left = x;

	x->ht = height(x);
	y->ht = height(y);

	return y;
}

Node* AVL::LL(Node* t){

	cout << "LL Case\n";
	t = rotateRight(t);
	return t;
}

Node* AVL::RR(Node* t){

	cout << "RR Case\n";
	t = rotateLeft(t);
	return t;
}

Node* AVL::LR(Node* t){

	cout << "LR Case\n";
	t->left = rotateLeft(t->left);
	t = rotateRight(t);
	return t;
}

Node* AVL::RL(Node* t){

	cout << "RL Case\n";
	t->right = rotateRight(t->right);
	t = rotateLeft(t);
	return t;
}

Node* AVL::insert(Node* root, string key, string mean){

	Node* curr = NULL;
	int lh,rh;
	
	if(root==NULL){
			root = new Node(key,mean);
			return root;
	}
	else {
	
		if(key < root->keyword){
			root->left = insert(root->left,key,mean);
			cout << "BF : " << root->keyword << " : " << BF(root) << endl;
			
			if(BF(root)==2){
				if(key < root->left->keyword){
					root = LL(root);
				} else {
					root = LR(root);
				}
			}
		} else if (key > root->keyword){
			root->right = insert(root->right,key,mean);
			cout << "BF : " << root->keyword << " : " << BF(root) << endl;
			
			if(BF(root)==-2){
				if(key < root->right->keyword){
					root = RR(root);
				} else {
					root = RL(root);
				}
			}
		}
	}
}
int main(){

	AVL *t = new AVL();
	t->inOrder(t->root);
	for(int i=0; i<5; i++){
		cout << "Enter word : ";
		string s;
		cin >> s;
		string m;
		cout << "Enter meaning : ";
		cin >> m;
		
		t->root = t->insert(t->root,s,m);
		t->inOrder(t->root);
	}
}
