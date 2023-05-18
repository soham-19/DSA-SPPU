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
        int val;
        Node *left;
        Node *right;

        Node(int v){
            val = v;
            left = right = nullptr;
        }
};

class BST {
    public:
        Node *root;

        BST(){
            cout << "BST has been created.\n";
            root = nullptr;
        }

        void construct(int arr[],int n);
        void insert(int ele);
        int height(Node* root);
        int minNode();
        int MaxNode();
        Node *mirror(Node *root);
        void search(int key);
        void in(Node *root);
};

void BST::construct(int arr[],int n){

    for (int i = 0; i < n;i++){
        insert(arr[i]);
    }
    cout << "BST constructed successfully\n";
}

void BST::insert(int ele){

    if(root == nullptr){
        root = new Node(ele);
        return;
    }

    Node *temp = root;

    while(temp != nullptr){

        if(ele < temp->val){
            if(temp->left == nullptr){
                temp->left = new Node(ele);
                return;
            }
            temp = temp->left;
        }
        else if(ele > temp->val){
            if(temp->right==nullptr){
                temp->right = new Node(ele);
                return;
            }
            temp = temp->right;
        }
        else{
            "Data exists already.\n";
            return;
        }

    }
}

void BST::search(int key){

    if(root == nullptr){
        cout << "BST is empty.\n";
        return;
    }
    Node *temp = root;
    int probe = 0;

    while(temp != nullptr){
        probe++;
        if(key < temp->val){
            if(temp->left == nullptr){
                cout << "Search unsuccessfull.\t Probe = " << probe << endl;
                return;
            }
            temp = temp->left;
        }
        else if(key > temp->val){
            if(temp->right==nullptr){
                cout << "Search unsuccessfull.\t Probe = " << probe << endl;
                return;
            }
            temp = temp->right;
        }
        else{
            cout << "Search successfull.\t Probe = " << probe << endl;
            return;
        }
    }
}

int BST::height(Node*root){

    if(root == nullptr)
        return 0;

    int lh = height(root->left);
    int rh = height(root->right);

    if(lh<rh)
        return rh + 1;

    return lh + 1;
}

int BST::minNode(){
    if(root == nullptr){
        cout << "BST is empty.\n";
        return -1;
    }
    Node *temp = root;
    while(temp->left != NULL){
        temp = temp->left;
    }
    return temp->val;
}

int BST::MaxNode(){
    if(root == nullptr){
        cout << "BST is empty.\n";
        return -1;
    }
    Node *temp = root;
    while(temp->right != nullptr){
        temp = temp->right;
    }
    return temp->val;
}

Node * BST::mirror(Node*root){
    if(root == nullptr)
        return root;

    Node *LS = mirror(root->left);
    Node *RS = mirror(root->right);

    root->left = RS;
    root->right = LS;

    return root;
}

void BST::in(Node*root){
    if(root!=nullptr){
        in(root->left);
        cout << root->val << " ";
        in(root->right);
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
                b->construct(arr,len);
                break;

            case 2:
                cout << "Enter element : ";
                cin >> x;
                b->insert(x);
                break;

            case 3:
                cout << "Height : " << b->height(b->root) << endl;
                break;
            case 4:
                cout << "Min : " << b->minNode() << endl
                     << "Max : " << b->MaxNode() << endl;
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
        }
    }
}