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
	Node *minValueNode(Node *);
	Node *remove(Node *, string);
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
	t->left = rotateLeft(t->left);
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

/* Given a non-empty binary search tree,
return the node with minimum key value
found in that tree. Note that the entire
tree does not need to be searched. */
Node * AVL::minValueNode(Node* node)
{
    Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
// Recursive function to delete a node
// with given key from subtree with
// given root. It returns root of the
// modified subtree.
Node* AVL::remove(Node* root, string key)
{
     
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;
 
    // If the key to be deleted is smaller
    // than the root's key, then it lies
    // in left subtree
    if ( key < root->keyword )
        root->left = remove(root->left, key);
 
    // If the key to be deleted is greater
    // than the root's key, then it lies
    // in right subtree
    else if( key > root->keyword )
        root->right = remove(root->right, key);
 
    // if key is same as root's key, then
    // This is the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) ||
            (root->right == NULL) )
        {
            Node *temp = root->left ?
                         root->left :
                         root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp; // Copy the contents of
                           // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node* temp = minValueNode(root->right);
 
            // Copy the inorder successor's
            // data to this node
            root->keyword = temp->keyword;
 
            // Delete the inorder successor
            root->right = remove(root->right,
                                     temp->keyword);
        }
    }
 
    // If the tree had only one node
    // then return
    if (root == NULL)
    return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->ht = 1 + max(height(root->left),
                           height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    int balance = BF(root);
 
    // If this node becomes unbalanced,
    // then there are 4 cases
 
    // Left Left Case
    if (balance > 1 &&
        BF(root->left) >= 0)
        return rotateRight(root);
 
    // Left Right Case
    if (balance > 1 &&
        BF(root->left) < 0)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
 
    // Right Right Case
    if (balance < -1 &&
        BF(root->right) <= 0)
        return rotateLeft(root);
 
    // Right Left Case
    if (balance < -1 &&
        BF(root->right) > 0)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
 
    return root;
}
int main(){

	AVL *t = new AVL();
	t->inOrder(t->root);
	for(int i=0; i<5; i++){
		cout << "Enter word : ";
		string s;
		cin >> s;
		// string m;
		// cout << "Enter meaning : ";
		// cin >> m;
		
		t->root = t->insert(t->root,s,s);
		t->inOrder(t->root);
	}
	string s;
	cin >> s;
	t->root = t->remove(t->root, s);
	t->inOrder(t->root);
}
