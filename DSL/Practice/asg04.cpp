/*
Beginning with an empty binary search tree, 
Construct binary search tree by inserting the values in the order given 
After constructing a binary tree

i Insert new node, 
i. Find number of nodes in longest path from root, 
iii. Minimum data value found in the tree, 
iv Change a tree so that the roles of the left and right pointers are swapped at every node, 
v Search a value

*/

#include<iostream>
using namespace std;

class Node{
    public:
        Node *left;
        int val;
        Node *right;

        Node(int val){
            this->val = val;
            left = right = NULL;
        }

        Node(){
            cout << "Enter data : ";
            cin >> this->val;
            left = right = NULL;
        }
};

class BST{
    public:
        Node *root;

        BST(){
            root = NULL;
        }

        void insert();
        int height(Node *t);
        void minimum();
        void maximum();
        Node *mirror(Node *t);
        void search(int key);
        void in(Node*t);
};

void BST::insert() {

    Node *newNode = new Node();

    Node *temp = root;
    if(temp==NULL){
            root = newNode;
            return;
    }

    while(temp!=NULL){

        if(newNode->val < temp->val){

            if(temp->left==NULL){
                temp->left = newNode;
                return;
            } else {
                temp = temp->left;
            }
        } else if(newNode->val > temp->val){

            if(temp->right==NULL){
                temp->right = newNode;
                return;
            } else {
                temp = temp->right;
            }
        } else {
            cout << "Data already exists.\nDuplicates are not allowed!!\n";
        }
    }
}

int BST::height(Node*t){
    if(t==NULL)
        return 0;

    return max(height(t->left), height(t->right)) + 1;
}

void BST::minimum(){
    if(root==NULL){
        cout << "null-tree\n";
        return;
    } else {
        Node*temp = root;
        while(temp->left!=NULL)
            temp = temp->left;
        cout << "Minimum : " << temp->val << endl;
    }
}

void BST::maximum(){
    if(root==NULL){
        cout << "null-tree\n";
        return;
    } else {
        Node*temp = root;
        while(temp->right!=NULL)
            temp = temp->right;
        cout << "Maximum : " << temp->val << endl;
    }
}
Node* BST::mirror(Node*t){
    if(t==NULL)
        return t;
    Node *L = mirror(t->left);
    Node *R = mirror(t->right);
    t->left = R;
    t->right = L;

    return t;
}

void BST::search(int key) {

    Node *temp = root;
    int probe = 0;

    while(temp!=NULL){
        probe++;
        if(key< temp->val){

            if(temp->left==NULL){
                break;
            } else {
                temp = temp->left;
            }
        } else if(key > temp->val){

            if(temp->right==NULL){
                break;
            } else {
                temp = temp->right;
            }
        } else {
            cout << "Search Successfull with probe = " << probe;
            return;
        }
    }
    cout << "Search Un-successfull with probe = " << probe;
}

void BST::in(Node*t){
    if(t!=NULL){
        in(t->left);
        cout << t->val << " ";
        in(t->right);
    }
}

int main(){

    int choice;
    int x;
    int len;
    int arr[10];
    BST *b = new BST();
    while(true){

        cout << "   * * * BST OPERATIONS * * *\n";
        cout << "1-construct\n2-insert\n3-height\n4-min & max\n5-search\n6-mirror\n";
        cout << "Enter choice -> ";
        cin >> choice;

        switch(choice){

            case 0:
                cout << "T E R M I N A T I N G \n\n\n";
                return 0;
            
            case 1:
                cout << "Enter array size : ";
                cin >> len;
                for (int i = 0; i < len;i++){
                    cout << "Ele " << i << " : ";
                    cin >> arr[i];
                }
                // b->construct(arr,len);
                break;

            case 2:
                // cout << "Enter element : ";
                // cin >> x;
                b->insert();
                break;

            case 3:
                cout << "Height : " << b->height(b->root) << endl;
                break;
            case 4:
                b->minimum();
                b->maximum();
                break;
            case 5:
                cout << "Enter key : ";
                cin >> x;
                b->search(x);
                break;

            case 6:
                cout << "In : ";
                b->in(b->root);
                cout << endl;
                b->mirror(b->root);
                cout << "In : ";
                b->in(b->root);
                cout << endl;
                break;
            case 7:
                cout << "In : ";
                b->in(b->root);
                cout << endl;
        }
    }
}