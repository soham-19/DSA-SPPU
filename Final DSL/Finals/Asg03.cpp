/*
Implement all the functions of a dictionary (ADT) using hashing and handle collisions using chaining with/without replacement.

Data Set of (key, value) pairs, Keys are mapped to values, Keys must be comparable, Keys must be unique Standard Operations. Insert(key, value), Find(key), Delete(key)
*/

#include<iostream>
using namespace std;

bool isAlpha(char ch){
	return (ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z');
}

char toLower(char ch){
	if(ch>='A'&&ch<='Z')
		return ch+32;
	return ch;
}

string update(string s){
	string result;
	for(int i=0; s[i] != '\0'; i++){
		if(isAlpha(s[i])){
			result += toLower(s[i]);
		}
	}
	return result;
}

class Node{
	public:
		string keyword;
		string meaning;
		Node* next;
		
		Node(string k){
			this->keyword = k;
			next = NULL;
			cout << "Enter meaning : ";
			cin >> meaning;
		}
};

class List{
	public:
		Node* head;
		Node* tail;
		
		List(){
			head = tail = NULL;
		}
		
		void push_back(string x){
			if(head == NULL){
				head = tail = new Node(x);
			} else {
				tail->next = new Node(x);
				tail = tail->next;
			}
		}
		
		void search(string x){
			int probe = 0;
			Node* temp = head;
			while(temp != NULL){
				probe++;
				if(temp->keyword == x){
					cout << "\"" << x << "\" found with probe = " << probe << endl << endl;
					return;
				}
				temp = temp->next;
			}
			cout << "\"" << x << "\" not found with probe = " << ++probe << endl << endl;
		}
		
		void del(string x){
			Node* curr = head;
			Node* prev = NULL;
			
			while(curr != NULL){
				
				if(curr->keyword == x){
					
					if(prev == NULL){
						head = curr->next;
					} else {
						prev->next = curr->next;
					}
					delete curr;
					cout << "Deleted \"" << x << "\"\n";
					return;
				}
				prev = curr;
				curr = curr->next;
			}
			cout << "\"" << x << "\" not found\n"; 
		}
		
		void update(string x){
			Node* curr = head;			
			while(curr != NULL){
				
				if(curr->keyword == x){
					cout << "Enter new meaning : ";
					cin >> curr->meaning;
					cout << "Updation successfull.\n";
					return;
				}
				curr = curr->next;
			}
			cout << "\"" << x << "\" not found\n"; 
		}
		
		void printLL(){
			int count = 1;
			Node* curr= head;
			while(curr!=NULL){
				cout << "\t" << count++ << ". " << curr->keyword << " : " << curr->meaning << endl;
				curr = curr->next;
			}
			cout << endl;
		}
		
		
};

class Dict{
	public:
	
	List buckets[26];
	
	int hash(string);
	void insert(string);
	void find(string);
	void remove(string);
	void modify(string);
	void print();
};

int Dict::hash(string s){
	return s[0] - 'a';
}

void Dict::find(string key){
	key = update(key);
	int bi = hash(key);
	buckets[bi].search(key);	
}

void Dict::remove(string key){
	key = update(key);
	int bi = hash(key);
	buckets[bi].del(key);	
}

void Dict::insert(string key){
	key = update(key);
	int bi = hash(key);
	buckets[bi].push_back(key);	
}

void Dict::modify(string key){
	key = update(key);
	int bi = hash(key);
	buckets[bi].update(key);	
}
void Dict::print(){
	cout << "char : \t\t" << "Chains\n";
	cout << "-------------------------------------------------\n";
	for(int i=0; i<26; i++){
		cout << char(i+'a') << " : \n";
		buckets[i].printLL();
		cout << "-------------------------------------------------\n";
	}
	cout << endl << endl;
}
int main(){
	
	Dict d;
	string x;
	int ch;
	
	while(true){
		cout << "* C H A I N I N G *\n"
			 << " 1 - insert\n"
			 << " 2 - search\n"
			 << " 3 - remove\n"
			 << " 4 - update\n"
			 << " 5 - display\n"
			 << " 0 - terminate\n\n"
			 << "Enter your choice : ";
		cin >> ch;
		
		switch(ch){
			case 0:
				cout << " T E R M I N A T I N G\n";
				return 0;
			case 1:
				cout << "Enter word to be inserted : ";
				cin >> x;
				d.insert(x);
				break;
			case 2:
				cout << "Enter word to be searched : ";
				cin >> x;
				d.find(x);
				break;
			case 3:
				cout << "Enter word to be removed : ";
				cin >> x;
				d.remove(x);
				break;
			case 4:
				cout << "Enter word to be modified : ";
				cin >> x;
				d.modify(x);
				break;
			case 5:
				d.print();
				break;
			default:
				cout << "Let's try again.\n";
				
		}
	}
	
}