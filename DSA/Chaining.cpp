#include <iostream>
using namespace std;

class Node {
    public:

    string word;
    Node * next;

    Node(string str=""){
        word = str;
        next = NULL;
    }
};

class Dict {
    public:

    Node table[26];       // store first nodes of ll's

    Dict() {

        // table = new Node[26];
        cout << "Hash-Table created.\n";

    }

    int hash(string str) {
        return str[0]-'a';
    }

    void store(string str) {

        int idx = hash(str);

        if(table[idx].word=="")
            table[idx].word = str;
        else {
            add(str);
        }
        
    }

    void add(string str) {
        int idx = hash(str);
        Node myNode(str);
        
        Node * temp = *(table[idx]);

        while(temp->next != NULL) {
            temp =temp->next;
        }
        temp->next = &myNode;

    }

    void print() {
        for(int i=0; i<26; i++) {
            cout << i << " " <<(char)(97+i) << " : ";
            printLL(&table[i]);
        }
    }

    void printLL(Node * head){

        Node * temp = head;

        while(temp != NULL){
            cout << temp->word << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {

    Dict d;

    d.print();

    string s;

    for(int i=0; i<5; i++) {
        cin >> s;
        d.store(s);
        d.print();
    }


    return 0;
}