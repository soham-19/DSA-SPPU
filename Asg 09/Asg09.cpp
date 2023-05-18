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
        ht = 1;
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
};

int AVL::height(Node*t){
	if(t==NULL){
		return 0;
	}
	return max(height(t->left), height(t->right)) + 1;
}

int AVL::BF(Node*t){
	if(t==NULL){
		return 0;
	}
	int lh, rh;

	if(t->left==NULL){
		lh = 0;
	} else {
		lh = t->left->ht + 1;
	}

	if(t->right==NULL){
		rh = 0;
	} else {
		rh = t->right->ht + 1;
	}

	return lh - rh;
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

int main(){

	AVL *t = new AVL();
	t->root = new Node("soham", "SOH");
	t->root->right = new Node("xebra", "SOH");
	t->root->left = new Node("flag", "FLAG");
	t->root->left->left = new Node("apple", "fruit");

	t->inOrder(t->root);
	cout << endl;
	t->root = t->rotateRight(t->root);
	t->inOrder(t->root);
}
