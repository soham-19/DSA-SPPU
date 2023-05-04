//16/03/23

#include <iostream>
#include<string>
#include<string.h>
using namespace std;

bool isalphabate(char ch){
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

char tolowerA(char ch){
    if (ch >= 'A' && ch <= 'Z')
        return ch + 32;
    return ch;
}

string remove(string str) {

    int count = 0;
    string result;
    for (int i=0; str[i] != '\0'; i++){
        if(isalphabate(str[i]))         //alpha asel tr ch str la add else skip 
            result += tolowerA(str[i]);     //tolower added always
    }
    return result;
}

class Node {

    public:
    string word;
    string meaning;
    Node * next;

    Node(string str="", string mean="unknown"){     //default args
        word = str;
        meaning = mean;
        next = NULL;
    }

};

class linkedList {

    public:
    int probe;
    Node * head;
    Node * tail;
    int length;

    linkedList(){
        length = 0;
        head = NULL;
    }

    void add(string str, string mean) {

        Node * newN = new Node(str, mean);
        length++;

        if(head == NULL) {
            head = tail = newN;
        }
        else {
            tail->next = newN;
            tail = newN;
        }
    }

    void printll(){
        if(head == NULL) {
            cout << "empty LL\n";
            return;
        }
        Node * temp = head;
        while(temp != NULL) {
            cout << '[' << temp->word << " : " << temp->meaning << ']' << "->";
            if(temp->next != NULL)
                cout <<"\n\n\t\t";  
            temp = temp->next;
        }
        cout << "NULL" <<endl;
    }

    int search(string name )

};

class Dict {

    public:
    linkedList  table[26];

    Dict() {
        cout << "\t\tDictionary created successfully...!!\n\n";
    }

    int hash(string str) {
        return str[0]-'a';      //a-a=0; b-a=1; c-a=2..................
    }

    void store (string str, string mean="unknown") {
        // cout << "String you entered was : "  << str << endl;
        str = remove(str);
        
        // cout << "Updated str is  : " << str << endl;
        
        int idx = hash(str);
        table[idx].add(str, mean);
    }
    
    void print() {

        cout << "index\tchar\tlinked list\n";
        cout << "=================================\n";
        for(int i=0; i<26; i++)  {
            cout << i <<"\t" << (char)(i+'a') << "\t";
            table[i].printll();         //print whole ll starting frm alpha.
            cout << "\n=================================\n";

        }
    }

    void search(string str) {
        str = remove(str);

        int idx = hash(str);
        Node * s = table[idx].binSearch(str);
        
        if(s==NULL) {
            cout <<"unsuccessfull\n";
        } else {
            cout << "Probe = " <<table[idx].probe<<endl;
            cout << "Successfull\n";
        }
    }

    void delete_(string str) {
        str = remove(str);      //remove non-alphas. and convert to all smallcase

        int idx =hash(str);     // get no. of ll;

        linkedList * curr = &table[idx];    // pointing to current ll
        Node* s = curr->binSearch(str);     // get prev of node to be deleted

        if(s==NULL){
            cout << "Deletion not possible... word not found...\n";
        }
        else {
            if(s==curr->head) {     //either 1st or 2nd node

                if(s->word == curr->head->word) //1ST NODE AAHEE
                    
                    curr->head = curr->head->next;      //headof curr = its next (delete frm head)              
                else                                          //2nd node is to be  dlted
                    curr->head->next = curr->head->next->next;//atachya head chya next vha next ha tyacha pn nd so head->nxt = 3rd node

                    delete s;                   // execute always if/else both //                 
                
            }
            else{
                Node* d = s->next;  //to be deleted
                s->next = s->next->next;        //prev cha nxt = atachya node cha nxt;
                delete d;                   
            }
        }
    }
};

int main() {
    // demo information
    string arr[] = 
                    {   
                        "Abjure", "Future", "Picnic",
                        "Agonistic", "Garland", "Protect",
                        "Airline", "Gigantic", "Publish",
                        "Bandit", "Goofy", "Quadrangle",
                        "Banquet", "Government", "Recount",
                        "Binoculars", "Grandnieces", "Redoubtable",
                        "Biologist", "Handbook", "Reflection",
                        "Blackboard", "Himself", "Reporter",
                        "Board", "Indulge", "Ring",
                        "Bookworm", "Inflatable", "Salesclerk",
                        "Butterscotch", "Inimical", "Snapshot",
                        "Camera", "Interim", "Shellfish",
                        "Campus", "Invest", "Ship",
                        "Catfish", "Jackpot", "Significance",
                        "Carsick", "Kitchenette", "Sometimes",
                        "Celebrate", "Law", "Sublime",
                        "Celery", "Life", "Tabletop",
                        "Citizen", "Lifeline", "Teamwork",
                        "Coloring", "Love", "Tennis",
                        "Compact", "Magnificent", "Timesaving",
                        "Dark", "Malevolence", "Tree",
                        "Damage", "Man", "Termination",
                        "Dangerous", "Mascot", "Underestimate",
                        "Decorum", "Marshmallow"
                    };

    int choice;
    string str;
    string mean;

    Dict d;

    for(int i=0; i<71; i++)
        d.store(arr[i]);        // add demo entriessss

    
    d.print();
    cout << endl << endl;
    cout << "\t\t\t\tW E L C O M E\n";

    while(true) {

        cout << "1. add a word\n";
        cout << "2. search a word\n";
        cout << "3. delete a word\n";
        cout << "4. print dict-table\n";
        cout << "0. exit program\n";
        cout << "\n-> Enter your choice\t";
        cin >> choice;

        cout << "\n\n";

        switch(choice) {

            case 0:
                cout << "\t\tT E R M I N A T I N G\n\n";
                return 0;
            
            case 1:
                cout << "Enter word -> ";
                cin >> str;
                fflush(stdin);
                cout << "Enter meaning -> ";
                getline(cin, mean);
                d.store(str, mean);
                break;
            
            case 2:
                cout << "Enter key -> ";
                cin >> str;
                d.search(str);
                break;

            case 3:

                cout << "Enter key -> ";
                cin >> str;
                d.delete_(str);
                break;
                
            case 4:
                d.print();
                break;

        }
    }
}