/*
Beginning with an empty binary search tree, Construct binary search tree by inserting the values in the order given After constructing a binary tree

i Insert new node, i. Find number of nodes in longest path from root, iii. Minimum data value found in the tree, iv Change a tree so that the roles of the left and right pointers are swapped at every node, v Search a value
*/

#include<iostream>
using namespace std;
#define null NULL
#define SPACE 10

class Node{
    public:
        Node *left;
        int val;
        Node *right;

        Node(int x){
            left = right = null;
            val = x;
        }
};

class Stack{
    public:
        int top;
        Node *stack[100];

        Stack(){
            top = -1;
        }

        bool isEmpty(){
            return top == -1;
        }
        bool isFull(){
            return top == 100 - 1;
        }
        void push(Node*n){
            if(isFull()){
                cout << "Stack Full.\n";
                return;
            }
            stack[++top] = n;
        }
        void pop(){
            if(isEmpty()) {
                cout << "Stack Empty.\n";
            } else {
                top--;
            }
        }

        Node* peek(){
            if(isEmpty()){
                cout << "Stack Empty.\n";
                return null;
            }
            return stack[top];
        }
};

class BST{
    public:
        Node *root;

        BST(){
            root = null;
        }

        void insert(int);
        int height(Node *);
        void maxPath(Node *);
        void minMax();
        Node *mirror(Node *);
        void search(int);
        void construct(int[],int);
        void inOrder();
        void preOrder();
        void postOrder();
        void display(Node *,int);
};

void BST::construct(int arr[], int n){
    for (int i = 0; i < n;i++)
        insert(arr[i]);
}

void BST::insert(int x) {

    if(root==NULL){
        root = new Node(x);
        return;
    }

    Node *temp = root;
    while(temp!=null){

        if(x < temp->val) {
            if(temp->left==null){
                temp->left = new Node(x);
                return;
            }
            temp = temp->left;

        } else if (temp->val < x) {
            if(temp->right == null){
                temp->right = new Node(x);
                return;
            }
            temp = temp->right;

        } else {
            cout << "Value exists already.\nDuplicates are not allowed.\n";
            return;
        }
    }
}
void BST::display(Node* root, int space){
    if(root == NULL)
        return;
    space += SPACE;
    display(root->right, space);
    cout << endl;
    for (int i = SPACE; i < space;i++){
        cout << " ";
    }
    cout << root->val << endl;
    display(root->left, space);
}

int BST::height(Node*t){
    if(t==null)
        return 0;
    return max(height(t->left), height(t->right)) + 1;
}

void BST::maxPath(Node* t) {

    if(t==null){
        cout << endl;
        return;
    }

    cout << t->val << " ";

    int lh = height(t->left);
    int rh = height(t->right);

    if(lh >= rh)
        maxPath(t->left);
    else
        maxPath(t->right);
}

void BST::minMax(){

    if(root==null){
        cout << "Tree is empty.\n";
        return;
    }

    Node *temp = root;
    while(temp->left != null)
        temp = temp->left;
    cout << "Minimum Value = " << temp->val<<endl;

    temp = root;
    while(temp->right != null)
        temp = temp->right;
    cout << "Maximum Valur = " << temp->val << endl;
}

Node* BST::mirror(Node*t){
    if(t==null)
        return t;

    Node *L = mirror(t->left);
    Node *R = mirror(t->right);

    t->left = R;
    t->right = L;

    return t;
}

void BST::search(int x) {

    int probe = 0;

    if(root == null){
        cout << "tree is empty.\n";
        return;
    }

    Node *temp = root;

    while(temp!=null) {

        ++probe;

        if(x < temp->val)
            temp = temp->left;
        else if(temp->val < x)
            temp = temp->right;
        else {
            cout << "found in " << probe << " comparisions.\n";
            return;
        }
    }
    cout << "not found in " << ++probe << " comparisions.\n";
}

void BST::preOrder(){
    cout << "Prerder : ";
    if(root == null){
        cout << "null\n";
        return;
    }
    Node *temp = root;
    Stack s;

    while(true){

        while(temp!=null){
            s.push(temp);
            cout << temp->val << " ";
            temp = temp->left;
        }

        if(s.isEmpty()){
            cout << endl;
            return;
        }

        temp = s.peek();
        s.pop();

        temp = temp->right;
    }
}

void BST::inOrder(){
    cout << "InOrder : ";
    if(root==null){
        cout << "null\n";
        return;
    }
    Stack s;
    Node *temp = root;
    while(true){

        while(temp!=null){
            s.push(temp);
            temp = temp->left;
        }

        if(s.isEmpty()){
            cout << endl;
            return;
        }

        temp = s.peek();
        s.pop();
        cout << temp->val << " ";
        temp = temp->right;
    }
}


void BST::postOrder(){

    if (root == null){
        cout << "null.\n";
        return;
    }

    Stack s1;
    
    Stack s2;
    cout << "PostOrder  : ";
    s1.push(root);
    while(!s1.isEmpty()){

        Node *curr = s1.peek();
        s1.pop();
        s2.push(curr);
        if(curr->left!=null)
            s1.push(curr->left);

        if(curr->right!=null)
            s1.push(curr->right);
    }

    while(!s2.isEmpty()){
        cout << s2.peek()->val << " ";
        s2.pop();
    }
    cout << endl;
}
int main() {

    int ch, x;
    BST bstree;

    while(true) {

        cout << "     * * * Binary Search Tree * * *" << endl
             << endl
             << "1-insert" << endl
             << "2-height" << endl
             << "3-minimum maximum" << endl
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
                bstree.display(bstree.root, 0);
                break;
            }
            case 2: {
                cout << "Height = " << bstree.height(bstree.root) << endl;
                bstree.maxPath(bstree.root);
                break;
            }
            case 3: {
                bstree.minMax();
                break;
            }
            case 4: {
                cout << "Before mirroring, ";
                bstree.inOrder();
                bstree.root = bstree.mirror(bstree.root);
                cout << "After mirroring, ";
                bstree.inOrder();
                break;
            }
            case 5: {
                cout << "Enter key -> ";
                cin >> x;
                bstree.search(x);
                break;
            }
            case 6: {
                bstree.preOrder();
                bstree.inOrder();
                bstree.postOrder();
                break;
            }
            default:
                cout << "Invalid choice \n\n";

        }
    }
}