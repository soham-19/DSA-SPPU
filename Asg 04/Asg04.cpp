#include<bits/stdc++.h>
using namespace std;

// Beginning with an empty binary search tree construct a binary search tree by inserting the values in the given order after constructing binary tree 
// insert new node 
// find number of nodes in the longest path from root 
// minimum data value found in the tree 
// change a tree so that the roles of left and right pointers are swapped at every node 
// search a value

class Node {
    public:
	    Node *left;
	    int val;
	    Node *right;

	    Node(int v) {
		    val = v;
		    left = right = NULL;
	    }
};

class BST {
    public:
        Node *root;
    
        BST() {
            cout << "BST creation successfull...\n";
		    root = NULL;
        }

        void inOrder();
        void preOrder();
        void insert(int);
        int height(Node*);
        int getMin();
        int getMax();
        Node *mirror(Node*);
        bool search(Node*, int);
};
void BST::inOrder() {

    if (root == NULL) {
        cout << "Empty tree\n";
		return;
    }

	stack<Node *> s;
	Node *temp = root;

	cout << " * inOrder : ";
	while (true) {

		while (temp != NULL){
			s.push(temp);
			temp = temp->left;
		}

		if (s.empty()) {
			cout << endl;
			break;
		}

		temp = s.top();
		s.pop();

		cout << temp->val << " ";

		temp = temp->right;
    }    

}
void BST::preOrder() {

    if (root == NULL) {
        cout << "Empty tree\n";
		return;
    }

	stack<Node *> s;
	Node *temp = root;

	cout << " * preOrder : ";
	while (true) {

		while (temp != NULL){
			cout << temp->val << " ";
			s.push(temp);
			temp = temp->left;
		}

		if (s.empty()) {
			cout << endl;
			break;
		}

		temp = s.top();
		s.pop();

		temp = temp->right;
    }    
}

void BST::insert(int data) {

	if (root == NULL) {
		root = new Node(data);
		return;
	}

	Node *newN = new Node(data);
	Node *temp = root;

	while (temp != NULL) {

		if (newN->val < temp->val) {
			if (temp->left == NULL) {
				temp->left = newN;
				return;
			} 
            else 
			    temp = temp->left;
            
		}
        else if (newN->val > temp->val) {
			if (temp->right == NULL) {
				temp->right = newN;
				break;
			}
			else
				temp = temp->right;
		}
		else {
			cout << "Data exists already\n";
			return;
		}
	}
}

int BST:: height(Node *root) {
	if(root == NULL)
		return 0;

	return max(height(root->left), height(root->right)) + 1;
}

int BST::getMin() {
    if(root == NULL){
        cout << "Empty Tree\n";
        return -1;
    }

    Node *temp = root;
    while(temp->left != NULL)
        temp = temp->left;

    return temp->val;
}

int BST::getMax() {
    if(root == NULL){
        cout << "Empty Tree\n";
        return -1;
    }

    Node *temp = root;
    while(temp != NULL)
        temp = temp->right;

    return temp->val;
}

Node* BST::mirror(Node *root) {

	if(root == NULL)
		return root;

	Node *Left = mirror(root->left);
	Node *Right = mirror(root->right);

	root->left = Right;
	root->right = Left;

	return root;
}

bool BST::search(Node *root, int x) {
	if (root == NULL)
		return false;
	else if (root->val == x)
		return true;

	else if (x < root->val)
		return search(root->left, x);
	else
		return search(root->right, x);
}

int main() {

    int ch, x;
    BST bstree;

    while(true) {

        cout << "     * * * Binary Search Tree * * *" << endl
             << endl
             << "1-insert" << endl
             << "2-height" << endl
             << "3-minimum" << endl
             << "4-mirror" << endl
             << "5-search" << endl
             << "6-print" << endl
             << endl;
        cout << endl
             << "Enter your choice -> ";
        cin >> ch;

        switch(ch) {
            case 0:
                cout << "T E R M I N A T I N G\n";
                return 0;
            case 1: {
                cout << "Enter data -> ";
                cin >> x;
                bstree.insert(x);
                break;
            }
            case 2: {
                cout << "Height = " << bstree.height(bstree.root) << endl;
                break;
            }
            case 3: {
                int minVal = bstree.getMin();
                if(minVal != -1)
                    cout << "Minimum = " << minVal << endl;
                break;
            }
            case 4: {
                bstree.root = bstree.mirror(bstree.root);
                cout << "After mirroring, ";
                bstree.inOrder();
                break;
            }
            case 5: {
                cout << "Enter key -> ";
                cin >> x;
                cout << bstree.search(bstree.root, x);
                break;
            }
            case 6: {
                bstree.inOrder();
                cout << endl;
                bstree.preOrder();
                break;
            }
            default:
                cout << "Invalid choice \n\n";

        }
    }
}