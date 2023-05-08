//se-b-38
//Soham A. Kulkarni

#include<bits/stdc++.h>
using namespace std;

// A dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting keywords, updating keywords of any entry. Provide a facility to display whole data sorted in ascending/descending order. also find how many maximum comparisions may require for finding any keyword. Use BST for implementation.

//global functions
bool isalphabate(char ch){
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

char tolowerA(char ch){
    if (ch >= 'A' && ch <= 'Z')
        return ch + 32;
    return ch;
}

string modify(string str) {

    int count = 0;
    string result;
    for (char i : str){
        if(isalphabate(i))         // add only alpha else skip it 
            result += tolowerA(i);     //tolower added always (a->a A->a)
    }
    return result;
}

//classes and methods
class Node {
    public:

	    Node *left;
        string keyword;
        vector<string> mean;    //storing multiple meanings
	    Node *right;

	    Node(string k) {
            
		    keyword = k;
            cout << "Add the meanings to the entered word \n";
            bool press = 0;

            do {
                string meaning;
                cout << "-> ";
                cin.ignore();
                getline (cin, meaning);
                mean.push_back(meaning);

                cout << "Press 1 to add more meaning or 0 to continue : ->";
                cin >> press;
            } while (press);

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

        void insert(string);

        Node *successor(Node *);
        Node *remove(Node *, string);

        Node *searchNode(Node*, string,int*);
        void update(Node *, string);

        void printAscending();
        void printDescending();
        void preOrder();

};

void BST::insert(string data) {

        data = modify(data);    // only lower case alphabates are processed

        if (root == NULL)
        {
            root = new Node(data);
            return;
	}

	Node *newN = new Node(data);
	Node *temp = root;

	while (temp != NULL) {

		if (newN->keyword < temp->keyword) {
			if (temp->left == NULL) {
				temp->left = newN;
				return;
			} 
            else 
			    temp = temp->left;
            
		}
        else if (newN->keyword > temp->keyword) {
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

Node* BST:: successor(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

Node* BST::remove(Node* root, string key) {

    if(root == NULL)
        return root;
    
    if(key < root->keyword)
        root->left = remove(root->left, key);

    else if(root->keyword < key)
        root->right = remove(root->right, key);

    else {

        if(root->left == NULL && root->right == NULL){
            delete root;
            return NULL;
        }

        if (root->left == NULL)
            return root->right;

        else if (root->right == NULL)
            return root->left;

            Node *IS = successor(root->right);  // replacing by inorder succ.

            root->keyword = IS->keyword;
            root->mean.clear();
            for (int i = 0; i < IS->mean.size(); i++)
            {
            root->mean.push_back(IS->mean[i]);  // copy meanings of IS to current node
            }

            root->right = remove(root->right, IS->keyword); //delete inorder succ. now after copying
    }

    return root;
}

void BST:: update(Node*root, string x) {
    int *i = new int;
    *i = 0;
    Node *node = searchNode(root, x,i);
    if(node == NULL) {
        cout << "Data not found ... adding to the BST \n";
        insert(x);
    }
    else {

        cout << "Current Data : ";
        cout << node->keyword << " :\t";
        for(string s : node->mean)
            cout << s << " ";
        cout << endl;

        cout << "Modifying meanings\n";

        node->mean.clear();

        bool press = 0;

        do
        {
            string meaning;
            cout << "-> ";
            cin.ignore();
            getline(cin, meaning);
            node->mean.push_back(meaning);

            cout << "Press 1 to add more meaning or 0 to continue : ->";
            cin >> press;
        } while (press);

        cout << "New Data : ";
        cout << node->keyword << " :\t";
        for(string s : node->mean)
            cout << s << " ";
        cout << endl;
    }
}

Node* BST:: searchNode(Node*root, string x,int* probe) {
    if(root == NULL || root->keyword == x){
        (*probe)++;
        return root;
    }
    else if (x < root->keyword){
        (*probe)++;
		return searchNode(root->left, x,probe);
    }
	else{
        (*probe)++;
		return searchNode(root->right, x,probe);
    }
}

void BST::printAscending() {
    if (root == NULL) {
        cout << "Empty tree\n";
		return;
    }
	stack<Node *> s;
	Node *temp = root;
	cout << " ascending order : ";
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
		cout << temp->keyword << " ";
		temp = temp->right;
    }    
}

void BST::printDescending() {
    if (root == NULL) {
        cout << "Empty tree\n";
		return;
    }
	stack<Node *> s;
	Node *temp = root;
	cout << "descending order : ";
	while (true) {
		while (temp != NULL){
			s.push(temp);
			temp = temp->right;
		}
		if (s.empty()) {
			cout << endl;
			break;
		}
		temp = s.top();
		s.pop();
		cout << temp->keyword << " ";
		temp = temp->left;
    }    
}

void BST::preOrder() {

    if (root == NULL) {
        cout << "Empty tree\n";
		return;
    }

	stack<Node *> s;
	Node *temp = root;

	cout << "preOrder : \n";
	while (true) {

		while (temp != NULL){
            cout <<" " <<  temp->keyword << "\t";
            cout << '[';
            for (int i = 0; i < temp->mean.size(); i++) {
                if(i==temp->mean.size()-1)
                    cout << temp->mean[i];
                else{
                    cout << temp->mean[i] << ", ";
                }
            }
            cout << ']'
                << endl;
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

int main() {

    string  x;
    int ch;
    BST bstree;

    while (true)
    {

        cout << "     * * * Dictionary using BST * * *" << endl
             << endl
             << "1-add an entry" << endl
             << "2-delete an entry" << endl
             << "3-update an entry" << endl
             << "4-search an entry" << endl
             << "5-display ascending" << endl
             << "6-display descending" << endl
             << "7-display pre order" << endl
             << endl;
        cout << endl
             << "Enter your choice -> ";
        cin >> ch;

        switch (ch)
        {
        case 0:
            cout << "T E R M I N A T I N G\n";
            return 0;
        case 1:
        {
            cout << "Enter data -> ";
            cin >> x;
            bstree.insert(x);
            break;
        }
        case 2:
        {
            cout << "Enter key -> ";
            cin >> x;
            bstree.remove(bstree.root, x);
            break;            
        }
        case 3:
        {
            cout << "Enter key -> ";
            cin >> x;
            bstree.update(bstree.root,x);
            break;
        }

        case 4:
        {
            cout << "Enter key -> ";
            cin >> x;
            int *a = new int;   // to track comparisions
            *a = 0;
            Node *n = bstree.searchNode(bstree.root, x,a);
            if(n == NULL)
                cout << "Data not found\t";
            else
                cout << "Data found\t";
            cout << "probe = " << *a << endl;
            break;
        }
        case 5:
        {
            bstree.printAscending();
            break;
        }
        case 6:
        {
            bstree.printDescending();
            cout << endl;
            break;
        }
        case 7:
        {
            bstree.preOrder();
            break;
        }
        default:
            cout << "Invaild choice \n\n";

        }
    }

    return 0;
}

/*
BST creation successfull...
     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 1
Enter data -> pot
Add the meanings to the entered word 
-> POT
Press 1 to add more meaning or 0 to continue : ->0
     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 1
Enter data -> fan
Add the meanings to the entered word
-> FAn
Press 1 to add more meaning or 0 to continue : ->0
     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 1
Enter data -> tap
Add the meanings to the entered word
-> TAP
Press 1 to add more meaning or 0 to continue : ->0
     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 1
Enter data -> apple
Add the meanings to the entered word
-> APPLE
Press 1 to add more meaning or 0 to continue : ->1
-> fruit
Press 1 to add more meaning or 0 to continue : ->0
     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 1
Enter data -> gate
Add the meanings to the entered word
-> GATE
Press 1 to add more meaning or 0 to continue : ->0
     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 1
Enter data -> ICE-Cream
Add the meanings to the entered word
-> ice-cream
Press 1 to add more meaning or 0 to continue : ->0
     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 1
Enter data -> sun
Add the meanings to the entered word
-> SUN
Press 1 to add more meaning or 0 to continue : ->0
     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 1
Enter data -> VAN
Add the meanings to the entered word
-> VAN
Press 1 to add more meaning or 0 to continue : ->0
     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 1
Enter data -> ZEBRA
Add the meanings to the entered word
-> ZEBRA
Press 1 to add more meaning or 0 to continue : ->0
     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 5
 ascending order : apple fan gate icecream pot sun tap van zebra
     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 6
descending order : zebra van tap sun pot icecream gate fan apple

     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 7
preOrder :
 pot    [POT]
 fan    [FAn]
 apple  [APPLE, fruit]
 gate   [GATE]
 icecream       [ice-cream]
 tap    [TAP]
 sun    [SUN]
 van    [VAN]
 zebra  [ZEBRA]

     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 2
Enter key -> fan
     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 5
 ascending order : apple gate icecream pot sun tap van zebra
     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 3
Enter key -> gate
Current Data : gate :   GATE
Modifying meanings
-> gate
Press 1 to add more meaning or 0 to continue : ->1
-> exam
Press 1 to add more meaning or 0 to continue : ->0
New Data : gate :       gate exam
     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 7
preOrder :
 pot    [POT]
 gate   [gate, exam]
 apple  [APPLE, fruit]
 icecream       [ice-cream]
 tap    [TAP]
 sun    [SUN]
 van    [VAN]
 zebra  [ZEBRA]

     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 4
Enter key -> zebra
Data found      probe = 4
     * * * Dictionary using BST * * *

1-add an entry
2-delete an entry
3-update an entry
4-search an entry
5-display ascending
6-display descending
7-display pre order


Enter your choice -> 0
T E R M I N A T I N G
*/