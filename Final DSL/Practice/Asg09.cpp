/*
A Dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry Provide facility to display whole data sorted in ascending/ Descending order Also find how many maximum comparisons may require for finding any keyword. Use Height balance tree and find the complexity for finding a keyword
*/
#include<iostream>
using namespace std;
#define null NULL

// class node->class avl
class Node{
    public:
        string keyword;
        string meaning;
        Node *left, *right;

        Node(string keyword){
            this->keyword = keyword;
            cout << "\tEnter meaning : ";
            cin >> this->meaning;
            left = right = null;
        }
};

class AVL{
    public:
        Node *root;
    AVL(){
        root = null;
    }

    Node *rotate_right(Node *);
    Node *rotate_left(Node *);
    Node *LL(Node *);
    Node *RR(Node *);
    Node *RL(Node *);
    Node *LR(Node *);

    int height(Node *);
    int balfact(Node *);
    Node *balanceAVL(Node *);

    Node *insert(Node *,string);
    Node *search(string, bool);
    Node *remove(Node*,string);
    Node *successor(Node *);
    void update(string key);

    void preOrder(Node *);
    void inOrder(Node *);
    void ascending(Node *);
    void descending(Node *);
    void postOrder(Node *);
};

Node* AVL::rotate_right(Node*x){
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Node* AVL::rotate_left(Node*x){
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Node* AVL::LL(Node* x){
    cout << "\n\tLL  case\n\n";
    return rotate_right(x);
}
Node* AVL::LR(Node*x){
    cout << "\n\tLR  case\n\n";
    x->left = rotate_left(x->left);
    return rotate_right(x);
}
Node* AVL::RR(Node*x){
    cout << "\n\tRR  case\n\n";
    return rotate_left(x);
}
Node*AVL::RL(Node*x){
    cout << "\n\tRL  case\n\n";
    x->right = rotate_right(x->right);
    return rotate_left(x);
}

int AVL::height(Node*t){
    if(t==null)
        return 0;
    return max(height(t->left), height(t->right)) + 1;
}

int AVL::balfact(Node*t){
    return height(t->left) - height(t->right);
}

Node* AVL::balanceAVL(Node* node){

    int bf = balfact(node);
    if (bf == 2) { // Left subtree is heavier
        if (balfact(node->left) >= 0) { // Left Left Case LL
            return LL(node);
        }
        else { // Left Right Case LR
            return LR(node);
        }
    }
    else if (bf == -2) { // Right subtree is heavier
        if (balfact(node->right) <= 0) { // Right Right Case RR
            return RR(node);
        }
        else { // Right Left Case RL
            return RL(node);
        }
    }
    return node;
}

Node* AVL::insert(Node*node,string key) {
    if(node==null)
        return new Node(key);

    if(key < node->keyword)
        node->left = insert(node->left, key);
    else if(node->keyword < key)
        node->right = insert(node->right, key);
    else {
        cout << "Data already exists.\n";
        return node;
    }
    return balanceAVL(node);
}

Node* AVL::successor(Node*t){
    while(t->left!=null)
        t = t->left;
    return t;
}

Node* AVL::remove(Node* node, string key) {
    if (node == null)
        return null;

    if (key < node->keyword)
        node->left = remove(node->left, key);

    else if (node->keyword < key)
        node->right = remove(node->right, key);

    else {
        // case 1 : 0 childs are present -> mag replace by null
        if(node->left==null && node->right == null){
            delete node;
            return null;
        }
        // case 2 : 1 child -> mg replace by that child
        else if(node->left == null) {   // fakt right ahe so tyane replace
            Node *temp = node->right;
            delete node;
            return temp;
        } else if (node->right == null){    // fakt left ahe so tyane replace
            Node *temp = node->left;
            delete node;
            return temp;
        }
        else {  // case 3 2 child mg replace by inorder successor
            Node* IS = successor(node->right);
            node->keyword = IS->keyword;
            node->meaning = IS->meaning;
            node->right = remove(node->right, IS->keyword);
        }

    }
    return balanceAVL(node);
}

Node* AVL::search(string key,bool flag){
    int probe = 0;

    Node *temp = root;
    while(temp!=null) {
        probe++;
        if(key < temp->keyword)
            temp = temp->left;
        else if(temp->keyword < key)
            temp = temp->right;
        else {
            if(flag)
                cout << "Found with probe = " << probe << endl;
            return temp;
        }
    }
    if(flag)
        cout << "Not found with probe = " << ++probe << endl;
    return null;
}

void AVL::update(string key) {

    string mean;
    Node *node = search(key, false);
    if(node==null) {
        bool add;
        cout << "Value did not exist.\nPress 1 to add it.\n";
        cin >> add;
        if(add){
            cout << "Enter meaning : ";
            cin >> mean;
            insert(root,key);
            return;
        }
    } else {
        cout << "Enter new meaning : ";
        cin >> mean;
        cout << "Before Updation : " << node->keyword << " : " << node->meaning << endl;
        node->meaning = mean;
        cout << "After Updation : " << node->keyword << " : " << node->meaning << endl;
    }
}

void AVL::preOrder(Node* t){
    if(t==null)
        return;
    cout << t->keyword << " ";
    preOrder(t->left);
    preOrder(t->right);
}

void AVL::inOrder(Node* t){
    if(t==null)
        return;
    inOrder(t->left);
    cout << t->keyword << " ";
    inOrder(t->right);
}

void AVL::ascending(Node* t){
    if(t==null)
        return;
    ascending(t->left);
    cout <<"\t"<<t->keyword << " : " << t->meaning << endl;
    ascending(t->right);
}

void AVL::descending(Node* t){
    if(t==null)
        return;
    descending(t->right);
    cout << "\t"<<t->keyword << " : " << t->meaning << endl;
    descending(t->left);
}

void AVL::postOrder(Node* t){
    if(t==null)
        return;
    postOrder(t->left);
    postOrder(t->right);
    cout << t->keyword << " ";
}

int main(){

    string k, m;
    int ch;
    AVL avltree;
    while(true){
        cout << "\t\t\t * A V T   T R E E *\n"
             << "\t\t1-insert\n"
             << "\t\t2-delete\n"
             << "\t\t3-update\n"
             << "\t\t4-search\n"
             << "\t\t5-print ascending\n"
             << "\t\t6-print descending\n"
             << "\t\t7-traverse\n"
             << "\t\tEnter your choice -> ";
        cin >> ch;

        switch(ch){

            case 1:
                cout << "\tEnter word to be inserted : ";
                cin >> k;
                avltree.root = avltree.insert(avltree.root, k);
                break;
            case 2:
                cout << "\tEnter word to be deleted : ";
                cin >> k;
                avltree.root = avltree.remove(avltree.root,k);
                break;
            case 3:
                cout << "\tEnter word to be updated : ";
                cin >> k;
                avltree.update(k);
                break;
            case 4:
                cout << "\tEnter word to be searched : ";
                cin >> k;
                avltree.search(k,true);
                break;
            case 5:
                cout << "\tAscending Order : \n";
                avltree.ascending(avltree.root);  
                cout<<endl;
                break;
            case 6:
                cout << "\tDescending Order : \n";
                avltree.descending(avltree.root);   
                cout<<endl;
                break;
            case 7:
                cout << "\tPre Order : ";
                avltree.preOrder(avltree.root); 
                cout<<endl;
                cout << "\tIn Order : ";
                avltree.inOrder(avltree.root);  
                cout<<endl;
                cout << "\tPost Order : ";
                avltree.postOrder(avltree.root);    
                cout<<endl;
                break;
            case 0 :
                cout << "\tT E R M I N A T I N G\n";
                return 0;
            default:
                cout << "\t\tEnter proper choice!!";
        }
    }
}