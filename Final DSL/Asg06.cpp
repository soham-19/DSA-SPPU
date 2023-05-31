/*
A Dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry Provide facility to display whole data sorted in ascending/ Descending order Also find how many maximum comparisons may require for finding any keyword Use Binary Search Tree for implementation
*/
#include<iostream>
using namespace std;
#define M 100

bool isAlphabet(char ch){
    return (ch>='A'&& ch<='Z') || (ch>='a'&& ch<='z');
}

char toLower(char ch){
    if(ch>='A' && ch <='Z')
        return ch + 32;
    return ch;
}

string modify(string str){
    string result;
    for (int i = 0; str[i] != '\0';i++) {
        if(isAlphabet(str[i])) {
            result += toLower(str[i]);
        }
    }
    return result;
}

class Node{
    public:
        Node *left;
        string keyword;
        string meaning;
        Node *right;

        Node(string key){
            keyword = key;
            //cout << "Enter meaning : ";
            //cin.ignore();
            //getline(cin, meaning);
            meaning = key + "!";
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

        bool isEmpty(){
            return top == -1;
        }
        bool isFull(){
            return top == M - 1;
        }
        void push(Node*x){
            if(isFull()){
                cout << "push() failed. StackFull\n";
                return;
            }
            stack[++top] = x;
        }
        void pop(){
            if(isEmpty()){
                cout << "pop() failed. StackEmpty\n";
                return;
            }
            stack[top--] = NULL;
        }
        Node* peek(){
            if(isEmpty()){
                cout << "peek() failed. StackEmpty\n";
                return NULL;
            }
            return stack[top];
        }
};

class Dict{
    public:
        Node *root;

        Dict(){
            cout << "Dictionary has been created.\n";
            root = NULL;
        }

        void insert(string);
        Node *search(string,bool flag);
        void update(string);
        void inOrder();
        void inOrderDec();
        void preOrder();
        void postOrder();
        Node *remove(Node*,string);
        Node *successor(Node *);

        void in(Node* t) {
            if(t!=NULL){
                in(t->left);
                cout << t->keyword << " ";
                in(t->right);
            }
        }
};

void Dict::insert(string word) {

    if(root==NULL){
        root = new Node(word);
        return;
    }

    Node *temp = root;

    while(temp!=NULL){

        if(word<temp->keyword){

            if(temp->left == NULL){
                temp->left = new Node(word);
                cout << "The word \"" <<word<<"\" successfully added to the dictionary.\n";
                return;
            }
            temp = temp->left;

        } else if(temp->keyword < word) {

            if(temp->right == NULL) {
                temp->right = new Node(word);
                cout << "The word \"" <<word<<"\" successfully added to the dictionary.\n";
                return;
            }
            temp = temp->right;

        } else {
            cout << "Duplicates are not allowed.\n";
            return;
        }
    }
}

Node* Dict::search(string key,bool flag) {

    Node *temp = root;
    int probe = 0;
    while(temp!=NULL){
        probe++;
        if(key < temp->keyword) {
            temp = temp->left;

        } else if(temp->keyword < key) {
            temp = temp->right;
        } else {
            if(flag)
                cout << "Value " << key << " found in " << probe << " comparisons." << endl;
            return temp;
        }
    }
    probe++;

    if(flag)
        cout << "Value " << key << " not found in " << probe << " comparisons." << endl;
    return NULL;
}

void Dict::update(string key) {

    Node *temp = search(key, false);

    if(temp == NULL) {

        cout << "Value doesn't exist in Dictionary\nPress 1 to add word.\n";
        bool choice;
        if(choice)
            insert(key);
        return;
    }

    cout << "Before updating : " << temp->keyword << " : " << temp->meaning << endl;
    cout << "Enter new meaning : ";
    cin >> temp->meaning;
    cout << "Updation successfull!\n";
    cout << "After updating : " << temp->keyword << " : " << temp->meaning << endl;

}
Node* Dict::remove(Node*node,string key){

    if(node == NULL)
        return node;

    if(key < node->keyword)
        node->left = remove(node->left, key);
    
    else if(node->keyword < key)
        node->right = remove(node->right, key);

    // now we r on the node to be deleted.
    else {
        cout << "The word \"" << key << "\" has been deleted successfully from dictionary ";
        // case 1 : no child -> directly delete.
        if(node->left ==NULL && node->right==NULL){
            cout << "with case 1 : no children\n";
            delete node;
            return NULL;
        }

        //  case 2: one child only -> replace by child
        if(node->left==NULL) {  // left is absent -> replace by right child 
            cout << "with case 2 : only right children\n";
            Node *temp = node->right;
            delete node;
            return temp;
        }

        if(node->right==NULL) { // right child is absent replace by left child.
            cout << "with case 2 : only left children\n";
            Node *temp = node->left;
            delete node;
            return temp;
        }

        // case 3: both childs are there. replace by inorder successor.
        Node *IS = successor(node->right);
        cout << "with case 3 : both children (replaced by inorder successor : \""<<IS->keyword<<"\")\n";

            // copy contents of inorder succsoor to our node.
        node->keyword = IS->keyword;
        node->meaning = IS->meaning;

            // delete in order succssor
        node->right = remove(node->right, IS->keyword);
    }
    return node;
}

Node* Dict::successor(Node* t){
    while(t->left!=NULL)
        t = t->left;
    return t;
}

void Dict::inOrder(){
    if(root==NULL){
        cout << "empty tree\n";
        return;
    }
    Node *temp = root;
    Stack s;

    while(true) {

        while(temp!=NULL){
            s.push(temp);
            temp = temp->left;
        }

        if(s.isEmpty()){
            cout << endl;
            break;
        }
        temp = s.peek();
        s.pop();

        cout << temp->keyword << " ";
        temp = temp->right;
    }
}

void Dict::inOrderDec(){
    if(root == NULL){
        cout << "empty tree\n";
        return;
    }
    Node *temp = root;
    Stack s;
    while(true) {

        while(temp!=NULL){
            s.push(temp);
            temp = temp->right;
        }

        if(s.isEmpty()){
            cout << endl;
            return;
        }

        temp = s.peek();
        s.pop();
        cout << temp->keyword << " ";
        temp = temp->left;
    }
}
void Dict::preOrder(){
    if(root==NULL){
        cout << "empty tree\n";
        return;
    }
    Node *temp = root;
    Stack s;
    while(true){
        while(temp!=NULL){
            s.push(temp);
            cout << temp->keyword << " ";
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
        cout << "empty tree\n";
        return;
    }

    Stack s1, s2;
    s1.push(root);

    while(!s1.isEmpty()){

        Node *curr = s1.peek(); s1.pop();
        s2.push(curr);

        if(curr->left!=NULL)
            s1.push(curr->left);
        if(curr->right!=NULL)
            s1.push(curr->right);
    }

    while(!s2.isEmpty()){
        cout << s2.peek()->keyword << " ";
        s2.pop();
    }
    cout << endl;
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
                cout << "Ascending Order Dictionary : ";
                d->inOrder();
                break;
            case 6:
                cout << "Descending Order Dictionary : ";
                d->inOrderDec();
                break;
            case 7:
                cout << "Pre Order : ";
                d->preOrder();
                cout << "In Order : ";
                d->inOrder();
                cout << "Post Order : ";
                d->postOrder();
                break;
            default:
                cout << "Invalid choice.\nLet's Try Again.\n\n";
        }
    }
}