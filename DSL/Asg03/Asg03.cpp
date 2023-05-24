/*

Implement all the functions of a dictionary (ADT) using hashing and handle collisions using chaining with/without replacement.

Data Set of (key, value) pairs, Keys are mapped to values, Keys must be comparable, Keys must be unique Standard Operations. Insert(key, value), Find(key), Delete(key)

*/

/*
node
ll
dict
    insert
    search
    delete
    update
    print
*/

//                  start of program

#include<iostream>
using namespace std;

//          global functions
bool isAlphabet(char ch){
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

char toLower(char ch){
    if (ch >= 'A' && ch <= 'Z')
        return ch + 32;
    return ch;
}

string updateString(string str){
    string result;
    for (int i = 0; str[i] != '\0';i++){
        if(isAlphabet(str[i])) {
            result += toLower(str[i]);
            cout << result << endl;
        }
    }
    return result;
}

//      classes

class Node{
    public:
        string keyword;
        string meaning;
        Node *next;


        Node(string w,string m){
            keyword = w;
            meaning = m;
            next = NULL;
        }
};

class List{

    public:
        Node *head, *tail;

        List(){
            head = tail = NULL;
        }

        void printList();
        void push_back(string);
        void search(string);
        void updateMean(string);
        void del(string);
};

void List::printList(){

    int i = 1;
    Node *temp = head;
    while(temp!=NULL){

        if(i!=1)
            cout << "\t\t";
    
        cout << i << ". " << temp->keyword << " : " << temp->meaning << endl;
        temp = temp->next;
        i++;
    }
}

void List::push_back(string w) {

    string m;
    cout << "Enter meaning of '" << w << "' : ";
    cin.ignore();
    getline(cin,m);

    if(head==NULL){
        head = tail = new Node(w, m);
    } else {
        tail->next = new Node(w, m);
        tail = tail->next;
    }
}

void List::search(string key){
    int probe = 0;
    Node *temp = head;

    while(temp!=NULL){
        probe++;
        if(temp->keyword == key) {
            cout << "Search Successfull with probe = " << probe << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Search unsuccessfull with probe = " << probe << endl;
}

void List::updateMean(string key) {
    Node *temp = head;

    while(temp!=NULL){
        if(temp->keyword == key) {
            cout << "Enter new meaning : ";
            cin.ignore();
            getline(cin, temp->meaning);
            return;
        }
        temp = temp->next;
    }
    cout << "Key not found.\nPress y/Y to insert it. : ";
    char ch;
    cin >> ch;
    if(ch=='Y'||ch=='y'){
        push_back(key);
    }
}

void List::del(string key) {

    Node *prev = NULL, *curr = head;
    while(curr!=NULL) {

        if(curr->keyword==key) {

            if(prev==NULL) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            cout << "Key deleted.\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Not found\n";
}

class Dict{

        int hash(string);

    public:
        List buckets[26];

        void printDict();
        void insert(string);
        void find(string);
        void update(string);
        void remove(string);
};

int Dict::hash(string s){
    return s[0] - 'a';
}

void Dict::printDict(){

    cout << "   "  << "ch\t:\t"
         << "Chains\n";
    cout << "\n------------------------------\n";

    for (int i = 0; i < 26;i++){
        cout << "   " <<char(i + 'a') << "\t:\t";
        buckets[i].printList();
        cout << "\n------------------------------\n";
    }
}

void Dict::insert(string s) {
    int bi = hash(s);
    buckets[bi].push_back(s);
}

void Dict::find(string s) {
    int bi = hash(s);
    buckets[bi].search(s);
}

void Dict::update(string s) {
    int bi = hash(s);
    buckets[bi].updateMean(s);
}

void Dict::remove(string s) {
    int bi = hash(s);
    buckets[bi].del(s);
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