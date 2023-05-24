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
	Node *rotateLeft(Node *t);
	Node* LL(Node* t);
	Node* RR(Node* t);
	Node* LR(Node* t);
	Node* RL(Node* t);
	Node* insert(Node*,string,string);
	void displayRotation(Node *);
	friend class Node;
};

int AVL::height(Node* node) {
    if (node == nullptr) {
        return 0;
    }
	return max(height(node->left), height(node->right)) + 1;
}

int AVL::BF(Node*t){
	int bf = height(t->left) - height(t->right);
	cout << "Curr bf " << t->keyword << " = "<< bf<< endl;
	return bf;
}

void AVL::inOrder(Node*root){
	if(root==NULL)
		return;
	cout << root->keyword << " : " << root->ht << "\n";
	inOrder(root->left);
	inOrder(root->right);
}

void AVL::displayRotation(Node*x) {
	cout << "\t\t  |" << endl;
	cout <<"\t\t"<< x->keyword << endl;
	cout << "\t\t/  \\\n";
	cout <<"\t  "<< (x->left==NULL?"null":x->left->keyword) << "   " << (x->right==NULL?"null":x->right->keyword) << endl;
}
Node* AVL::rotateRight(Node*x){

	cout << "\tBefore Right Rotation : \n";
	displayRotation(x);
	cout << "Performing right-rotation with pivot = " << x->keyword << endl;

	Node * y;
	y= x->left;
	x->left = y->right;
	y->right = x;

	x->ht = height(x);
	y->ht = height(y);

	cout << "\n\tAfter Right Rotation : \n";
	displayRotation(y);

	return y;
}


Node* AVL::rotateLeft(Node*x){

	cout << "\tBefore Left Rotation : \n";
	displayRotation(x);
	cout << "Performing left-rotation with pivot = " << x->keyword << endl;

	Node * y;

	y= x->right;
	x->right = y->left;
	y->left = x;

	x->ht = height(x);
	y->ht = height(y);
	cout << "\n\tAfter Left Rotation : \n";
	displayRotation(y);

	return y;
}

Node* AVL::LL(Node* t){

	cout << "\t\t*\tLL Case\n";
	t = rotateRight(t);
	return t;
}

Node* AVL::RR(Node* t){

	cout << "\t\t*\tRR Case\n";
	t = rotateLeft(t);
	return t;
}

Node* AVL::LR(Node* t){

	cout << "\t\t*\tLR Case\n";
	t->left = rotateLeft(t->left
	t = rotateRight(t);
	return t;
}

Node* AVL::RL(Node* t){

	cout << "\t\t*\tRL Case\n";
	t->right = rotateRight(t->right);
	t = rotateLeft(t);
	return t;
}
Node* AVL::insert(Node* root, string key, string mean) {
    if (root == NULL) {
        return new Node(key, mean);
    }
    if (key < root->keyword) {
        root->left = insert(root->left, key, mean);
        if (BF(root) == 2) {
            if (key < root->left->keyword) {
                root = LL(root);
            } else {
                root = LR(root);
            }
        }
    } else if (key > root->keyword) {
        root->right = insert(root->right, key, mean);
        if (BF(root) == -2) {
            if (key > root->right->keyword) {
                root = RR(root);
            } else {
                root = RL(root);
            }
        }
    }
    root->ht = height(root);
    return root;
}

int main(){

	AVL *t = new AVL();
	t->inOrder(t->root);
	for(int i=0; i<50; i++){
		cout << "Enter word : ";
		string s;
		cin >> s;
		// string m;
		// cout << "Enter meaning : ";
		// cin >> m;
		
		t->root = t->insert(t->root,s,s);
		t->inOrder(t->root);
	}
	t->inOrder(t->root);
}