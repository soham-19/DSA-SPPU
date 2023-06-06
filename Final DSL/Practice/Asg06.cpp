// A dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting keywords, updating keywords of any entry. Provide a facility to display whole data sorted in ascending/descending order. also find how many maximum comparisions may require for finding any keyword. Use BST for implementation.

#include<iostream>
using namespace std;
#define null NULL

class Node{
    public:
    Node *left;
    string keyword;
    string meaning;
    Node *right;

    Node(string keyword,string meaning=""){
        this->keyword = keyword;
        this->meaning = meaning;
        left = right = null;
    }
};

class Stack{
    int top;
    Node *stack[100];
    public:
    Stack(){
        top = -1;
    }
    bool isEmpty(){
        return top == -1;
    }
    bool isFull(){
        return top == 99;
    }
    void push(Node*n) {
        if(isFull()){
            cout << "StackFull\n";
        } else {
            stack[++top] = n;
        }
    }

    void pop(){
        if(isEmpty()){
            cout << "Stack Empty\n";

        } else
            top--;
    }

    Node*peek(){
        if(isEmpty()){
            cout << "StackEmpty\n";
            return null;
        }
        return stack[top];
    }
};

class Dict{
    public:
    Node *root;
    
    Dict(){
        root = null;
    }

    void insert(string);
    Node *search(string, bool);
    void update(string);

    Node *remove(Node *, string);
    Node *successor(Node *);

    void preOrder();
    void inOrder();
    void inOrderDec();
    void postOrder();
};

void Dict::insert(string key) {

    if(root == null){
        root = new Node(key);
        return;
    }

    Node *temp = root;
    while(temp!=null){

        if(key <temp->keyword){

            if(temp->left==null){
                temp->left = new Node(key);
                return;
            }
            temp = temp->left;
        } else if(temp->keyword < key){

            if(temp->right==null){
                temp->right = new Node(key);
                return;
            }
            temp = temp->right;
        } else {
            cout << "Data already exists.\nDuplicates allowed.\n";
            return;
        }
    }
}

Node* Dict::search(string key,bool flag) {

    int probe = 0;
    if(root == null) {
        if(flag)
            cout << "empty tree.\n";
        return null;
    }

    Node *temp = root;
    while(temp!=null) {
        probe++;
        if(key < temp->keyword){
            temp = temp->left;
        } else if(temp->keyword<key){
            temp = temp->right;
        } else {
            if(flag)
                cout << "found with probe = " << probe<<endl;
            return temp;
        }
    }
    if(flag)
        cout << "not found with probe = " << ++probe << endl;
    return null;
}

void Dict::update(string key) {

    Node *node = search(key, false);
    if(node==null) {
        cout << "not found in dictionary.\nPress 1 to add the key : ";
        int ch;
        cin >> ch;
        if(ch==1)
            insert(key);
    } else {
        string old = node->meaning;
        cout << "Enter new meaning : ";
        cin >> node->meaning;

        cout << "Before updation : " << key << " : " << old << endl;
        cout << "After updation : " << key << " : " << node->meaning << endl;
    }
}

Node* Dict::successor(Node*t){
    while(t->left!=null)
        t = t->left;
    return t;
}

Node* Dict::remove(Node* node,string key) {

    if(root==null){
        return root;
    }

    else if(key < node->keyword)
        root->left = remove(root->left, key);

    else if(node->keyword < key)
        root->right = remove(root->right, key);

    else {

        // case 1 0 child

        if(node->left==null&&node->right==null){
            delete node;
            return null;
        }

        else if(node->left == null) {
            Node *temp = node->right;
            delete node;
            return temp;
        }

        else if(node->right == null) {
            Node *temp = node->left;
            delete node;
            return temp;
        }

        else {
            // case 3:

            Node *IS = successor(root->right);
            node->keyword = IS->keyword;
            node->meaning = IS->meaning;

            node->right = remove(node->right, key);
        }
    }

    return node;
}

void Dict::preOrder(){
    cout << "Pre Order : \t";
    if(root==null){
        cout << "empty tree.\n";
        return;
    }
    Node *temp = root;
    Stack s;

    while(true){
    while(temp!=null) {
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

void Dict::inOrder(){
    if(root==null){
        cout << "empty tree.\n";
        return;
    }
    Node *temp = root;
    Stack s;
    while(true){
    while(temp!=null) {
        s.push(temp);
        temp = temp->left;
    }

    if(s.isEmpty()){
        cout << endl;
        return;
    }

    temp = s.peek();
    s.pop();

    cout << temp->keyword << " ";
    temp = temp->right;

    }
}

void Dict::inOrderDec(){
    if(root==null){
        cout << "empty tree.\n";
        return;
    }
    Node *temp = root;
    Stack s;

    while(true){
    while(temp!=null) {
        s.push(temp);
        temp = temp->left;
    }

    if(s.isEmpty()){
        cout << endl;
        return;
    }

    temp = s.peek();
    s.pop();

    cout << temp->keyword << " ";
    temp = temp->right;
    }
}

void Dict::postOrder(){
    cout << "Post Order : \t";
    if(root==null){
        cout << "empty tree.\n";
        return;
    }

    Stack s1, s2;
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

        cout << s2.peek()->keyword << " ";
        s2.pop();
    }
    cout << endl;
}

bool isA(char ch){
    return (ch>='A'&&ch<='Z') || (ch>='a'&&ch<='z');
}

char low(char ch){
    if(ch>='A'&&ch<='Z')
        return ch + 32;
    return ch;
}

string modify(string s){
    string result;
    for (int i = 0; s[i] != '\0';i++){
        if(isA(s[i]))
            result += low(s[i]);
    }

    return result;
}

int main(){

    int ch;
    string x;

    Dict *d = new Dict();

    while(true){

        cout << "   * * * BST DICTIONARY * * *\n";
        cout << "1-add an entry\n"
        << "2-delete an entry\n"
        << "3-update meaning\n"
        << "4-search\n"
        << "5-display in ascending order\n"
        << "6-display in descending order\n"
        << "7-display traversals (keys)\n";

        cout << "  Enter your choice: -> ";
        cin >> ch;

        switch(ch) {

            case 0:
                cout <<"     T E R M I N A T I N G\n";
                return 0;
            case 1:
                cout << "Enter word to be inserted : ";
                cin >> x;
                x = modify(x);
                d->insert(x);
                break;
            case 2:
                cout << "Enter word to be deleted : ";
                cin >> x;
                x = modify(x);
                d->root = d->remove(d->root, x);
                break;
            case 3:
                cout << "Enter word to be updated : ";
                cin >> x;
                x = modify(x);
                d->update(x);
                break;
            case 4:
                cout << "Enter key to be searched : ";
                cin >> x;
                d->search(x, true);
                break;
            case 5:
                cout << "Ascending Order Dictionary : \t";
                d->inOrder();
                break;
            case 6:
                cout << "Descending Order Dictionary : \t";
                d->inOrderDec();
                break;
            case 7:
                d->preOrder();
                cout << "In Order : \t";
                d->inOrder();
                d->postOrder();
                break;
            default:
                cout << "Invalid choice.\nLet's Try Again.\n\n";
        }
    }
}