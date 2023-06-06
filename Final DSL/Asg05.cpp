#include<iostream>
#include<stack>
using namespace std;
#define M 100

bool isAlpha(char ch){
    return (ch>='A'&&ch<='Z') || (ch>='a'&&ch<='z');
}

bool isOperator(char ch){
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int len(string s){
    int i;
    for (i= 0; s[i] != '\0';i++){}
    return i;
}

class Node{
    public:
    Node *left;
    char data;
    Node *right;

    Node(char val){
        data = val;
        left = right = NULL;
    }
};

class Stack{
    int top;
    Node *stack[M];

    public:
    Stack(){
        top = -1;
    }
    bool isEmpty(){
        return top == -1;
    }
    bool isFull(){
        return top == M - 1;
    }
    void push(Node* n){
        if(isFull()){
            cout << "StackFullException\n";
        }
        stack[++top] = n;
    }
    void pop(){
        if(isEmpty()){
            cout << "StackEmptyException\n";
            return;
        }
        top--;
    }
    Node* peek(){
        if(isEmpty()){
            cout << "StackEmptyException\n";
            return NULL;
        }
        return stack[top];
    }
};

class Tree{
    public:
    string prefix;
    Node *root;

    Tree(){
        root = NULL;
    }

    void buildFromPrefix(string);
    void buildFromPostfix(string);
    void display(Node *);
    void postOrder();
    void deleteTree(Node *);
    int eval(Node *);
};

int Tree::eval(Node* node) {
    if (node==NULL)
        return 0;

    if (node->left==NULL && node->right==NULL) {
        // Handle variables
        if (isAlpha(node->data)) {
            char variable = node->data;
            int value;
            cout << "Enter value for " << variable << ": ";
            cin >> value;
            return value;
        }
        // Handle constants (convert char to int)
        return node->data - '0';
    }

    int l_val = eval(node->left);
    int r_val = eval(node->right);

    if (node->data == '+')
        return l_val + r_val;

    if (node->data == '-')
        return l_val - r_val;

    if (node->data == '*')
        return l_val * r_val;
    return l_val / r_val;
}

void Tree::buildFromPrefix(string prefix) {
    Stack st;
    int length = len(prefix);
    for (int i = length - 1; i >= 0; i--) {
        Node *newNode = new Node(prefix[i]);
        if (isOperator(prefix[i])) {
            newNode->left = st.peek();
            st.pop();
            newNode->right = st.peek();
            st.pop();
            st.push(newNode);
        }
        else {
            st.push(newNode);
        }
    }
    if(!isOperator(st.peek()->data)){
        cout << "Invalid Testcase.\nThere is no opeartor.\n";
        root = NULL;
        return;
    }
    root = st.peek();
}
void Tree::buildFromPostfix(string postfix) {
    Stack st;
    int length = postfix.length();
    for (int i = 0; i < length; i++) {
        Node *newNode = new Node(postfix[i]);
        if (isOperator(postfix[i])) {
            newNode->right = st.peek();
            st.pop();
            newNode->left = st.peek();
            st.pop();
            st.push(newNode);
        } else {
            st.push(newNode);
        }
    }
    if (!isOperator(st.peek()->data)) {
        cout << "Invalid Testcase.\nThere is no operator.\n";
        root = NULL;
        return;
    }
    root = st.peek();
}

void Tree::display(Node* node) {
    if (node != NULL) {
        cout << node->data;
        if (node->left!=NULL || node->right!=NULL) {
            cout << "(";
            display(node->left);
            cout << ",";
            display(node->right);
            cout << ")";
        }
    }
}

void Tree::postOrder(){
    cout << "PostOrder : ";
    Stack s1, s2;
    if(root==NULL){
        cout << "null tree\n";
        return;
    }
    s1.push(root);

    while(!s1.isEmpty()){
        Node* curr = s1.peek();
        s1.pop();
        s2.push(curr);
        if(curr->left!=NULL)
            s1.push(curr->left);
        if(curr->right != NULL)
            s1.push(curr->right);
    }
    while(!s2.isEmpty()){
        cout << s2.peek()->data;
        s2.pop();
    }
    cout << endl;
}

void Tree::deleteTree(Node*t){
    if(t==NULL)
        return;

    deleteTree(t->left);
    deleteTree(t->right);

    cout << "Deleted \"" << t->data << "\"\n";
    delete t;
}

int main(){

    Tree t;
    int ch;
    string x;

    while(true) {

        cout << "   * E X P R E S S I O N   T R E E *\n"
             << "1-build expression-tree\n"
             << "2-print postorder\n"
             << "3-display expression tree\n"
             << "4-evaluate expression tree\n"
             << "5-delete expression tree\n"
             << "0-terminate\n"
             << "Enter your choice : ";
        cin >> ch;

        switch(ch) {
            case 0:
                cout << "T E R M I N A T I N G\n";
                return 0;
            case 1:
                t.deleteTree(t.root);
                cout << "Enter prefix expression : ";
                cin >> x;
                t.buildFromPostfix(x);
                break;
            case 2:
                t.postOrder();
                break;
            case 3:
                t.display(t.root);
                cout << endl;
                break;
            case 4:
                cout << "Evalution = " << t.eval(t.root) << endl;
                break;
            case 5:
                t.deleteTree(t.root);
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }
}