#include <iostream>
#include <string>
using namespace std;
#define size 50

class node {
	public:
		string key, meaning;
		node *left, *right;
        node(){
            left = right = NULL;
        }
};
class Stack {
	int i;
	node **arr;
	public:
	Stack() {
		arr = new (node*[size]);
		i = -1;
	}
	inline bool full() {
		return i == size-1;
	}
	inline bool empty() {
		return i == -1;
	}
	void push(node *n) {
		if (full()) {
			return;
		}
		arr[++i] = n;
	}
	void pop() {
		if (empty()) {
			return;
		}
		i--;
	}
	node* top() {
		return arr[i];
	}
};
// ==========================
class tree {
	node *newnode, *q, *delNode;
	public:
	node *root;
	tree() {
		root = NULL;
	}
	// ======================
	void insertData(string s, string m) {
		newnode = new(node);
		newnode->key = s;
		newnode->meaning = m;
		newnode->left = NULL;
		newnode->right = NULL;
		if (root == NULL) {
			root = newnode;
			cout << "Root inserted!";
			return;
		}
		q = root;
		while (q != NULL) {
			if (s > q->key) {
				if (q->right == NULL) {
					q->right = newnode;
					cout << "Inserted at right\n";
					break;
				}
				else {
					q = q->right;
				}
			}
			else if (s < q->key) {
				if (q->left == NULL) {
					q->left = newnode;
					cout << "Inserted at left\n";
					break;
				}
				else {
					q = q->left;
				}
			}
			else {
				cout << "Key already present\n";
				break;
			}
		}
	}
	// ======================
	void searchData(string s) {
		int searchCount = 0;
		if (root == NULL) {
			cout << "Tree doesn't exist\n";
			return;
		}
		q = root;
		while (q != NULL) {
			if (s < q->key) {
				q = q->left;
				searchCount++;
			}
			else if (s > q->key) {
				q = q->right;
				searchCount++;
			}
			else {
				searchCount++;
				cout << "Word found\nNo. of comparisons = " << searchCount;
				cout << "\nWord\t\tMeaning\n";
				cout << q->key << "\t\t" << q->meaning << endl;
				return;
			}
		}
		searchCount++;
		cout << "Key not found\n";
		cout << "No. of comparsions = " << searchCount << endl;
	}
	// ======================
	void updateData(string s) {
		if (root == NULL) {
			cout << "Tree doesn't exist\n";
			return;
		}
		q = root;
		while (q != NULL) {
			if (s < q->key) {
				q = q->left;
				// searchCount++;
			}
			else if (s > q->key) {
				q = q->right;
				// searchCount++;
			}
			else {
				cout << "Word: " << q->key << "\nMeaning: " << q->meaning << endl;
				cout << "\nEnter the new meaning: ";
				getline(cin, q->meaning);
				cout << "Meaning updated successfully\n";
				return;
			}
		}
		cout << "Key not found\n";
	}
	// ======================
	node* inOrderSuccessor(node *root) {
		q = root;
		while (q->left != NULL) {
			q = q->left;
		}
		return q;
	}
	// ======================
	node* deleteData(node *root, string s) {
		if (root == NULL) {
			return root;
		}
		// Key is smaller than the current node
		if (s < root->key) {
			root->left = deleteData(root->left, s);
		}
		// Key is greater than the current node
		else if (s > root->key) {
			root->right = deleteData(root->right, s);
		}
		else {		// Key found
			// Three cases
			// Case 1: Leaf Node
			if (root->left == NULL && root->right == NULL) {
				delete(root);
				return NULL;
			}
			// Case 2.a: Node with left child
			else if (root->right == NULL) {
				node* temp = root->left;
				delete root;
				return temp;
			}
			// Case 2.b: Node with right child
			else if (root->left == NULL) {
				node* temp = root->right;
				delete root;
				return temp;
			}
			// Case 3: Node with two child nodes
			else {
				node* temp = inOrderSuccessor(root->right);
				root->key = temp->key;
				root->meaning = temp->meaning;
				root->right = deleteData(root->right, temp->key);
			}
		}
		return root; // after the big else condition (else of "Key found")
	}
	string toLower(string s) {
		string res;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] >= 65 && s[i] <= 90) {
				s[i] += 32;
			}
		}
		return res;
	}
	// ======================
	void preOrderNonRec() {
		if (root == NULL) {
			cout << "Tree does not exist\n";
			return;
		}
		Stack s1;
		q = root;
		cout << "Pre-Order:\n";
		while (true) {
			while (q != NULL) {
				cout << q->key << " ";
				s1.push(q);
				q = q->left;
			}
			if (s1.empty()) {
				break;
			}
			q = s1.top();
			s1.pop();
			q = q->right;
		}
	}
	// ======================
	void inOrderNonRec() {
		if (root == NULL) {
			cout << "Tree does not exist\n";
			return;
		}
		Stack s1;
		q = root;
		while (true) {
			while (q != NULL) {
				s1.push(q);
				q = q->left;
			}
			if (s1.empty()) {
				break;
			}
			q = s1.top();
			s1.pop();
			cout << q->key << " ";
			q = q->right;
		}
	}
	void postOrderNonRec() {
		if (root == NULL) {
			cout << "Tree does not exist\n";
			
			return;
		}
	}
	// ======================
	void inOrderNonRec_Rev() {
		if (root == NULL) {
			cout << "Tree does not exist\n";
			return;
		}
		Stack s1;
		q = root;
		do {
			while (q != NULL) {
				s1.push(q);
				q = q->right;
			}
			if (s1.empty()) {
				break;
			}
			q = s1.top();
			s1.pop();
			cout << q->key << " ";
			q = q->left;
		} while (true);
	}	
};
// ==========================
int main(int argc, char const* argv[]) {
	tree t1;
	int ch;
	string word, meaning;
	node* returnedNode;
	char opt;
	do {
		cout << "(1) Insert Key\n";
		cout << "(2) Search Key\n";
		cout << "(3) Update Meaning\n";
		cout << "(4) Delete Key\n";
		cout << "(5) Ascending Traversal\n";
		cout << "(6) Descending Traversal\n";
		cout << "\nEnter choice: ";
		cin >> ch;
		cin.ignore();
		switch(ch) {
			case 1:
				cout << "Enter a word: ";
				getline(cin, word);
				cout << "Enter its meaning: ";
				getline(cin, meaning);
				
				t1.insertData(word, meaning);
				break;
			
			case 2:
				cout << "Enter a key to search: ";
				getline(cin, word);
				t1.searchData(word);
				break;
			
			case 3:
				cout << "Enter a key whose meaning is to be updated: ";
				getline(cin, word);
				t1.updateData(word);
				break;
			
			case 4:
				cout << "Enter a key to delete: ";
				getline(cin, word);
				t1.root = t1.deleteData(t1.root, word);
				cout << "Node deleted!";
				break;
			
			case 5:
				cout << "Word\t\tMeaning\n";
				t1.inOrderNonRec();
				break;
			
			case 6:
				cout << "Word\t\tMeaning\n";
				t1.inOrderNonRec_Rev();
				break;
			
			default:
				cout << "\nInvalid Choice\n";
				break;
		}
		cout << "\nContinue? (Y/N): ";
		cin >> opt;
	} while (opt == 'y' || opt == 'Y');
	return 0;
}