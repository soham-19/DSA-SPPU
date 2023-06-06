/*
Implement all the functions of a dictionary (ADT) using hashing and handle collisions using chaining with/without replacement.

Data Set of (key, value) pairs, Keys are mapped to values, Keys must be comparable, Keys must be unique Standard Operations. Insert(key, value), Find(key), Delete(key)
*/

/*
class node class list class dict
*/

#include<iostream>
using namespace std;
#define null NULL

class Node{
	public:
	string keyword;
	string meaning;
	Node* next;
	
	Node(string keyword){
		this->keyword = keyword;
		cout << "Enter meaning of \""<<this->keyword<<"\" : ";
		cin >>this->meaning;
		next = null;
	}
};

class List{
	public:
	Node* head;
	Node* tail;
	
	List(){
		head = tail = null;
	}
	
	void push_back(string);
	void search(string);
	void dlt(string);
	void modify(string);
	void printLL();	
};

void List::push_back(string key){
	
	if(head == null){
		head = tail = new Node(key);
		return;
		
	} else {
		tail->next = new Node(key);
		tail = tail->next;
	}
}

void List::search(string key){
	int probe = 0;
	if(head == null){
		cout << "\""<<key << "\" not found in probe = " << ++probe<<endl;
		return;
	}
	
	Node*temp = head;
	while(temp!=null){
		probe++;
		if(temp->keyword==key){
			 cout << "\""<<key << "\"  found in probe = " << probe<<endl;
			return;
		}
		temp = temp->next;
	}
	
	cout << "\""<<key << "\" not found in probe = " << ++probe<<endl;
}

void List::dlt(string key){
	
	Node*prev = null;
	Node* curr = head;
	
	while(curr!=null){
		
		if(curr->keyword == key){
			
			if(prev == null){
				head = curr->next;
			} else {
				prev->next = curr->next;
			}
			cout << "\""<<key << "\" has been deleted\n";			
			delete curr;
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	cout << "\""<<key << "\" didn't exist in record\n";
}

void List::modify(string key){
	
	if(head == null){
		cout << "\""<<key << "\" not found in records"<<endl;
		return;
	}
	
	Node*temp = head;
	while(temp!=null){
		
		if(temp->keyword==key){
			string old = temp->meaning;
			cout << "Enter new meaning for \""<<key<<"\""<<endl;
			cin >> temp->meaning;
			cout << "Before Updation : \""<<key << "\" : " << old <<"\""<<endl;
			cout << "After Updation : \""<<key << "\" : " << temp->meaning <<"\""<<endl;
			return;
		}
		temp = temp->next;
	}
	cout << "\""<<key << "\" didn't exist in record\n";
}

void List::printLL(){
	
	if(head == null){
		cout << "empty chain\n";
		return;
	}
	
	int i=1;
	Node* temp = head;
	
	while(temp!=null){
		
		if(i==1){
			cout <<"\t"; 
		} else {
			cout << "\t\t";
		}    cout << i <<".";
		cout << "\""<<temp->keyword << "\"" << ":\t"<<temp->meaning<<endl;
		temp = temp->next;
		i++;
	}
}
class Dict{
	
	List buckets[26];	
	public:
	int hash(string);
	void insert(string);
	void find(string);
	void remove(string);
	void update(string);
	void print();
};
	  
int Dict::hash(string s){
	return (int)(s[0]-'a');
}

void Dict::insert(string key){
	int bi = hash(key);
	buckets[bi].push_back(key);
}

void Dict::find(string key){
	int bi = hash(key);
	buckets[bi].search(key);
}

void Dict::remove(string key){
	int bi = hash(key);
	buckets[bi].dlt(key);
}

void Dict::update(string key){
	int bi = hash(key);
	buckets[bi].modify(key);
}
		
void Dict::print(){
	
	cout << "char\t" << "Chains\n";
	cout << "---------------------------------------\n";
	for(int i=0;i<26;i++){
		cout << char(i+'a') << "\t";
		buckets[i].printLL();
		cout << "---------------------------------------\n";
	}
	cout << endl;
}

bool isAlpha(char ch){
	return (ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z');
}

char toLowerCase(char ch){
	if(ch>='A' && ch <='Z'){
		return ch+32;
	}
	return ch;
}

string lowercase(string s){
	string result;
	for(int i=0;s[i] != '\0';i++){
		if(isAlpha(s[i]))
			result += toLowerCase(s[i]);
	}
	return result;
}
int main(){
	
	int ch;
	string x;
	Dict d;
	
	while(true){
		cout << " * * * Dictionary using Chaining * * *\n"
		     << "1-insert\n"
			 << "2-find\n"
			 << "3-remove\n"
			 << "4-update\n"
			 << "5-print\n"
			 << "0-terminate\n\n";
		cout << "Enter your choice : ";
		cin >> ch;
		
		switch(ch){
			
			case 0:
				cout << " T E R M I N A T I N G \n";
				return 0;
				
			case 1:
				cout << "Enter word to be inserted : ";
				cin >> x;
				x = lowercase(x);
				d.insert(x);
				break;
				
			case 2:
				cout << "Enter word to be searched : ";
				cin >> x;
				x = lowercase(x);
				d.find(x);
				break;				
			case 3:
				cout << "Enter word to be removed : ";
				cin >> x;
				x = lowercase(x);
				d.remove(x);
				break;

			case 4:
				cout << "Enter word to be updated : ";
				cin >> x;
				x = lowercase(x);
				d.update(x);
				break;
				
			case 5:
				d.print();
				break;
				
			default:
				cout << "Invalid choice.\n";

		}
	}
}
