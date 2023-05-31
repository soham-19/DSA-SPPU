/*
A Dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry Provide facility to display whole data sorted in ascending/ Descending order Also find how many maximum comparisons may require for finding any keyword Use Binary Search Tree for implementation
*/

#include<iostream>
using namespace std;
#define M 100

class Node{
    public:
        string keyword;
        string meaning;
        Node *left, *right;

        Node(string keyword){
            this->keyword = keyword;
            meaning = keyword;
            left = right = NULL;
        }
};

class Stack{
    public:
        int top;
        Node *stack[M];

        Stack(){
            top = -1;
        }

        bool isFull(){
            return top == M - 1;
        }
        bool isEmpty(){
            return top == -1;
        }

        void push(Node*n){
            if(isFull()){
                cout << "StackFull.\n";
                return;
            }
            stack[++top] = n;
        }

        Node*peek(){
            if(isEmpty()){
                cout << "StackEmpty.\n";
                return NULL;
            }
            return stack[top];
        }
        void pop(){
            if(isEmpty()){
                cout << "StackEmpty.\n";
            } else{
                top--;
            }
        }
};

class Dict{
    public:
        Node *root;

        Dict(){
            cout << "Dictionary has been crested.\n";
        }

        void insert(string);
        Node* remove(Node*,string);
        Node *successor(Node *);
        void update(string);
        void inOrder();
        void inOrderDec();
        void preOrder();
        void postOrder();
        Node *search(string, bool);
};

void Dict::inOrder(){
    if(root==NULL){
        cout << "empty tree.\n";
        return;
    }
    Stack s;
    Node *temp = root;
    while(true){
        while(temp!=NULL){
            s.push(temp);
            cout << temp->keyword << " ";
            temp = temp->left;
        }
        if(s.isEmpty()){
            cout << "\n";
            return;
        }

        temp = s.peek();
        s.pop();

        temp = temp->right;
    }
}

void Dict::inOrderDec(){
    if(root==NULL){
        cout << "empty tree.\n";
        return;
    }
    Stack s;
    Node *temp = root;
    while(true){
        while(temp!=NULL){
            s.push(temp);
            cout << temp->keyword << " ";
            temp = temp->right;
        }
        if(s.isEmpty()){
            cout << endl;
            return;
        }
        temp = s.peek();
        s.pop();
        temp = temp->left;
    }
}

void Dict::preOrder(){
    if(root==NULL){
        cout << "empty tree.\n";
        return;
    }
    Stack s;
    Node *temp = root;
    while(true){
        while(temp!=NULL){
            cout << temp->keyword << " ";
            s.push(temp);
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

void Dict::postOrder(){
    if(root==NULL){
        cout << "empty tree.\n";
        return;
    }
    Stack s1, s2;
    s1.push(root);
    while(!s1.isEmpty()){

        Node *curr = s1.peek();
        s1.pop();

        s2.push(curr);

        if(curr->left!=NULL)
            s1.push(curr->left);

        if(curr->right !=NULL)
            s1.push(curr->right);
    }

    while(!s2.isEmpty()){
        cout << s2.peek()->keyword << " ";
        s2.pop();
    }
    cout << endl;
}

void Dict::insert(string word) {

    if(root==NULL){
        root = new Node(word);
        return;
    }

    Node *temp = root;
    while(temp!=NULL){

        if(word < temp->keyword) {
            if(temp->left = NULL){
                temp->left = new Node(word);
                cout << "    Word \"" << word << "\" added successfully.\n";
                return;
            }
            temp = temp->left;
        } else if(temp->keyword < word) {
            if(temp->right == NULL){
                temp->right = new Node(word);
                cout << "    Word \"" << word << "\" added successfully.\n";
                return;
            }
            temp = temp->right;
        } else {
            cout << "Duplicates are not allowed.\n";
            return;
        }
    }
    cout << "    Word \"" << word << "\" not added.\n";
}

Node* Dict::search(string key,bool flag){

    if(root == NULL){
        cout << "empty tree.\n";
        return NULL;
    }
    int probe = 0;
    Node *temp = root;
    while(temp!=NULL){
        probe++;
        if(key < temp->keyword){
            temp = temp->left;
        } else if(temp->keyword<key){
            temp = temp->right;
        } else {
            if(flag)
                cout << "   Word\"" << key << "\" found in " << probe << " comparisions.\n";
            return temp;
        }
    }
    if(flag)
        cout << "   Word\"" << key << "\" not found in " << ++probe << " comparisions.\n";
    return temp;
}

void Dict::update(string key){
    Node *node = search(key, false);
    if(node==NULL){
        cout << "Word \"" << key << "\" not found in dictionary.\nPress 1 to insert it.\n";
        bool press;
        cin >> press;
        if(press){
            insert(key);
        }
        return;
    }
    string mean = node->meaning;
    cout << "Enter updated meaning : ";
    cin >> node->meaning;
    cout << "Before Updating : " << node->keyword << " : " << mean << endl;
    cout << "After Updating : " << node->keyword << " : " << node->meaning << endl;
}

Node * Dict::successor(Node*t){
    while(t->left!=NULL)
        t = t->left;
    return t;
}

Node* Dict::remove(Node*node,string key) {
    if(node==NULL)
        return node;
    
    else if(key < node->keyword) {
        node->left = remove(node->left, key);
    }

    else if(node->keyword < key) {
        node->right = remove(node->right, key);
    }

    else {
        // case 1 no child.
        if(node->left == NULL && node->right == NULL){
            delete node;
            return NULL;
        }

        else if (root->left == NULL){
            Node *temp = node->right;
            delete node;
            return temp;
        }
        else if (root->right==NULL){
            Node *temp = node->left;
            delete node;
            return temp;
        }
        else {
            Node *IS = successor(node->right);

            node->keyword = IS->keyword;
            node->meaning = IS->meaning;

            node->right = remove(node->right, IS->keyword);
        }
    }
    return node;
}

int main(){
    
}



