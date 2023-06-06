/*

Implement all the functions of a dictionary (ADT) using hashing and handle collisions using chaining with/without replacement.

Data Set of (key, value) pairs, Keys are mapped to values, Keys must be comparable, Keys must be unique Standard Operations. Insert(key, value), Find(key), Delete(key)
*/

/*
approach
class node
class linked list
class dict : in that array of linked list 
    insert : add at end of ll
    find : search in ll

*/

#include<iostream>
using namespace std;

bool isalphabate(char ch){
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

char tolowerA(char ch){
    if (ch >= 'A' && ch <= 'Z')
        return ch + 32;
    return ch;
}

string updateStr(string str) {

    string result;

    for (int i = 0; str[i] != '\0';i++){

        if(isalphabate(str[i]))         //alpha asel tr ch str la add else skip 
            result += tolowerA(str[i]);     //lowercase added always
    }
    return result;
}

class Node{
    public:
        string keyword;
        string meaning;
        Node *next;

        Node(string w, string m){
            keyword = w;
            meaning = m;
            next = NULL;
        }
};

class List{
    public:
        Node *head,*tail;

        List(){
            head = NULL;
        }

        void printList();
        void push_back(string w);
        void search(string key);
        void modify(string);
        void dlt(string key);
};

void List::printList(){

    Node *temp = head;
    if(temp == NULL){
        cout << "empty bucket.\n";
        return;
    }
    int count = 1;

    while(temp != NULL){
        if(count==1){
            cout << "\t" << count++ << ". " << temp->keyword <<" : " << temp->meaning << endl;
        }
        else{
            cout << "\t\t" << count++ << ". " << temp->keyword <<" : " << temp->meaning << endl;
        }
        temp = temp->next;
    }
}

void List::push_back(string w){

    cout << "Enter the meaning : ";
    string mean;
    cin.ignore();
    getline(cin, mean);

    Node *newNode = new Node(w, mean);

    if(head==NULL){
        head = tail = new Node(w, mean);
        return;
    }
    tail->next = new Node(w, mean);
    tail = tail->next;
}

void List::search(string key){
    int probe = 0;
    Node *temp = head;
    while(temp!=NULL){
        probe++;
        if(temp->keyword == key){
            cout << "Search Successfull with probe = " << probe << endl;
            cout << key << " : " << temp->meaning << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Search Unsuccessfull with probe = "<< probe << endl;
}

void List::modify(string key){

    Node *temp = head;
    while(temp!=NULL){

        if(temp->keyword == key){
            cout << "Enter new meaning : ";
            cin >> temp->meaning;
            return;
        }
        temp = temp->next;
    }
    cout << "keyword doesn't exist.\n";
    cout << "Press (y/Y) to add it : ";
    char ch;
    cin >> ch;
    if(ch=='y' || ch=='Y'){
        push_back(key);
    }
}

void List::dlt(string key) {

    Node* curr = head;
    Node* prev = NULL;
    int probe = 0;
    while (curr != NULL) {
        probe++;
        if (curr->keyword == key) {
            if (prev == NULL) {
                // If the node to be removed is the head node
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            cout << key << " has been removed. Probe = " << probe << endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Deletion unsuccessfull with probe = " << probe << endl;
}

class Dict{
    public:
        List buckets[26];

        int hash(string s);
        void print();
        void insert(string s);
        void find(string);
        void update(string);
        void remove(string);
};

void Dict::print(){

    cout << "Char" << "\t" << "Linked-List\n";
    cout << "------------------------------\n";
    for (int i = 0; i < 26; i++) {

        cout << char(i + 'a') << "\t";
        buckets[i].printList();
        cout << "------------------------------\n";
    }
}

int Dict::hash(string s){
    return s[0] - 'a';
}

void Dict::insert(string s){
    s = updateStr(s);
    int idx = hash(s);
    buckets[idx].push_back(s);
}

void Dict::find(string key){
    key = updateStr(key);
    int idx = hash(key);
    buckets[idx].search(key);

}

void Dict::update(string key){
    key = updateStr(key);
    int idx = hash(key);
    buckets[idx].modify(key);
}

void Dict::remove(string key) {
    key = updateStr(key);
    int idx = hash(key);
    buckets[idx].dlt(key);
}

int main(){

    string s;
    int ch;
    Dict *dictionary = new Dict();

    while(true){
        
        cout << "   * * * Dictionary - Chaining * * *\n";
        cout << "1.insert an entry\n";
        cout << "2.find an entry\n";
        cout << "3.update an entry\n";
        cout << "4.remove an entry\n";
        cout << "5.print the dictionary\n";
        cout << "0.terminate the program\n";

        cout << "\n-> Enter your choice -> ";
        cin >> ch;

        switch(ch){

            case 0:
                cout << "\n\n    * T E R M I N A T I N G *\n\n";
                return 0;

            case 1:
                cout << "Enter word to be inserted : ";
                cin >> s;
                dictionary->insert(updateStr(s));
                cout << endl;
                break;

            case 2:
                cout << "Enter word to be searched : ";
                cin >> s;
                dictionary->find(s);
                cout << endl;
                break;

            case 3:
                cout << "Enter word to be updated : ";
                cin >> s;
                dictionary->update(s);
                cout << endl;
                break;

            case 4:
                cout << "Enter word to be removed : ";
                cin >> s;
                dictionary->remove(s);
                cout << endl;
                break;

            case 5:
                cout << " * D I C T I O N A R Y * : \n";
                dictionary->print();
                break;

            default:
                cout << "Invalid Choice.\nTry Again.\n";
        }
    }

    return 0;
}