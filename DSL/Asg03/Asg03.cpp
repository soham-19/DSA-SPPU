/*

Implement all the functions of a dictionary (ADT) using hashing and handle collisions using chaining with/without replacement.

Data Set of (key, value) pairs, Keys are mapped to values, Keys must be comparable, Keys must be unique Standard Operations. Insert(key, value), Find(key), Delete(key)

*/
#include<iostream>
using namespace std;

bool isAlphaB(char ch){
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

char toLower(char ch){
    if(ch>='A'&&ch<='Z')
        return ch + 32;
    return ch;
}

string updateString(string s){
    string result;
    for (int i = 0; s[i] != '\0';i++){
        if(isAlphaB(s[i]))
            result += toLower(s[i]);
    }
    return result;
}

class Node{
    public:
    string keyword;
    string meaning;

    Node *next;

    Node(string k,string m){
        keyword = k;
        meaning = m;
        next = NULL;
    }
};

class List{

    public:
    Node *head;
    Node *tail;

    List(){
        head = tail = NULL;
    }

    void add(string);
    void search(string);
    void printLL();
    void deleteNode(string);
    void modifyMeaning(string);

};

void List::add(string s){

    string mean;
    cout << "Enter meaning : ";
    cin >> mean;

    Node *node = new Node(s, mean);

    if(head==NULL){
        head = tail = node;
    } else {
        tail = tail->next = node;
    }
}

void List::printLL(){
    
    Node *temp = head;
    int i = 1;

    while(temp!=NULL){
        if(i!=1)
            cout << "\t";
        cout << i << ". " << temp->keyword << " "<< " : " << temp->meaning << endl;
        temp = temp->next;
        i++;
    }
    cout << endl;
}

void List::search(string key){

    int probe = 0;
    Node *temp = head;

    if(head == NULL){
        cout << "Unsuccessfull search with probe = " << ++probe << endl;
        return;
    }
    while(temp!=NULL){
        ++probe;
        if(temp->keyword == key) {
            cout << "Successfull search with probe = " << probe << endl;
            return;
        }
    }
    cout << "Unsuccessfull search with probe = " << probe << endl;
}

void List::deleteNode(string key) {
    Node *curr = head, *prev = NULL;

    while(curr !=NULL){

        if(curr->keyword == key) {

            if(curr == head) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }

            delete curr;
            cout << "Successfull Deletion" << endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    cout << "Unsuccessfull Deletion" << endl;
}

void List::modifyMeaning(string key){
    Node *temp = head;

    if(head == NULL){
        cout << "Unsuccessfull attempt of updation" << endl;
        return;
    }
    while(temp!=NULL){
    
        if(temp->keyword == key) {
            cout << "Enter new meaning : ";
            cin >> temp->meaning;
            cout << "Successfull updation = " <<  endl;
            return;
        }
    }
    cout << "Unsuccessfull attempt of updation" <<  endl;

}

class Dict{

    int hash(string);

    public:
    List buckets[26];

    void insert(string);
    void find(string);
    void remove(string);
    void update(string);
    void printDict();
};

int Dict::hash(string s){
    return s[0] - 'a';
}

void Dict::insert(string s){
    int bi = hash(s);

    buckets[bi].add(s);
}

void Dict::find(string key){
    int bi = hash(key);

    buckets[bi].search(key);
}

void Dict::remove(string key) {
    int bi = hash(key);

    buckets[bi].deleteNode(key);
}

void Dict::update(string key){
    int bi = hash(key);
    buckets[bi].modifyMeaning(key);
}

void Dict::printDict(){

    cout << 'i' << "\t"
         << "chains\n";

    cout << "-----------------------------\n";
    for (int i = 0; i < 26;i++){
        cout << char(i + 'a') << "\t";
        buckets[i].printLL();
        cout << "-----------------------------\n";
    }
}

// main func
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
                dictionary->insert(updateString(s));
                cout << endl;
                break;

            case 2:
                cout << "Enter word to be searched : ";
                cin >> s;
                dictionary->find(updateString(s));
                cout << endl;
                break;

            case 3:
                cout << "Enter word to be updated : ";
                cin >> s;
                dictionary->update(updateString(s));
                cout << endl;
                break;

            case 4:
                cout << "Enter word to be removed : ";
                cin >> s;
                dictionary->remove(updateString(s));
                cout << endl;
                break;

            case 5:
                cout << " * D I C T I O N A R Y * : \n";
                dictionary->printDict();
                break;

            default:
                cout << "Invalid Choice.\nTry Again.\n";
        }
    }

}