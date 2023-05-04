#include <iostream>
using namespace std;

class Node {
	public:
	string word;
	Node * next;
	
	Node(string str="") {
		word = str;
		next = NULL;
	}

};

class Dict {

	public:
	Node *table;
	
	Dict() {
		table = new Node[26];
		cout << "Dictionary created\n";
	}
	
	int hash(string str) {
		return str[0]-'a';  //abc  
	}
	
	void store(Node * myNode) {
		int idx = hash(myNode->word);
		
		if(table[idx] == NULL){
			
			table[idx] = myNode;
			return;
		}
		add(myNode);

		
	}
	
	void print() {
		cout << "index\t" << "word\t\n";
		for(int i=0; i<26; i++) {
			cout << i << "\t";
			printList(table[i]);
		}
	}
	
	void add(Node *myNode) {
	
		int idx = hash(myNode->word);
		myNode->next = table[idx];
		table[idx] = myNode;

	}
	
	void printList(Node *head) {
	
		Node* temp = head;
		if(temp==NULL) {
		cout << "empty\n";
			return;
		}
		while(temp != NULL) {
			cout << temp->word << ", ";
			temp = temp->next;
		}
		cout << endl;
	}
	
};

int main() {

	Dict d;
	d.print();
	for(int i=0; i<6; i++){
		string s;
		cin >> s;
		Node myN(s);
		d.store(&myN);
		d.print();
	}
}
