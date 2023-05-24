/*
Beginning with an empty binary search tree, Construct binary search tree by inserting the values in the order given After constructing a binary tree

i Insert new node, i. Find number of nodes in longest path from root, iii. Minimum data value found in the tree, iv Change a tree so that the roles of the left and right pointers are swapped at every node, v Search a value
*/

#include<iostream>
using namespace std;
#define null NULL

/*
    Node
    BST
    stack
*/

class Node {
    public:
        Node *left;
        int val;
        Node *right;

        Node(){
            cout << "Enter value : ";
            cin >> val;
            left = right = null;
        }
};

class BST{
    public:
        Node *root;

        BST(){
            root = null;
        }

        void insert();              //done
        int height(Node*);          //done
        void minMax();              // done
        Node *mirror(Node *);       // done
        void search();              //done
        void inOrder(Node *);
        void preOrder(Node *);
};

void BST::insert(){

    Node *node = new Node();
    if(root == null){
        root = node;
        return;
    }

    Node *temp = root;

    while(temp!=null){

        if(node->val < temp->val){

            if(temp->left == null){
                temp->left = node;
                return;
            }

            temp = temp->left;

        } else if (temp->val < node->val) {

            if(temp->right == null){
                temp->right = node;
                return;
            }
            temp = temp->right;

        } else {
            cout << "Value is already present.\n";
            return;
        }

    }
}

void BST::search() {

    int key;
    cout << "Enter key to be searched : ";
    cin >> key;


    if(root == null) {
        cout << "Tree is empty.\nSearch unsuccessfull with probe = 1\n";
    }

    int probe = 0;

    Node *temp = root;

    while(temp != null) {

        probe++;
                
        if(key < temp->val) {

            if(temp->left == null) {
                probe++;
                cout << "Search unsuccessfull with probe = " << probe << endl;
                return;
            }

            temp = temp->left;
        }

        else if(temp->val < key) {

            if(temp->right == null) {
                probe++;
                cout << "Search unsuccessfull with probe = " << probe << endl;
                return;
            }

            temp = temp->right;
        }

        else {
            cout << "Search successfull with probe = " << probe << endl;
            return;
        }
    }
}

void BST::inOrder(Node* r){
    if(r!=null){
        inOrder(r->left);
        cout << r->val << " ";
        inOrder(r->right);
    }
}

void BST::preOrder(Node* r){
    if(r!=null){
        cout << r->val << " ";
        preOrder(r->left);
        preOrder(r->right);
    }
}

int BST::height(Node*t){
    if(t==null || (t->left==null && t->right==null)){
        return 0;
    }
    return max(height(t->left), height(t->right)) + 1;
}

void BST::minMax(){

    Node *temp = root;
    while(temp->left != null)
        temp = temp->left;

    cout << "Min : " << temp->val << endl;

    temp = root;

    while(temp->right != null)
        temp = temp->right;

    cout << "Max : " << temp->val << endl;

    delete temp;
}

Node* BST::mirror(Node*t) {
    if(t==null)
        return t;

    Node *L = mirror(t->left);
    Node *R = mirror(t->right);

    t->left = R;
    t->right = L;

    return t;
}

int main(){

    BST *bst = new BST();

    while(true) {

        cout << "In - ";
        bst->inOrder(bst->root);
        cout << endl;
        cout << "Pre - ";
        bst->preOrder(bst->root);
        cout << endl;

        bst->insert();
        cout << endl;
        bst->search();
    }
}