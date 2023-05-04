#include<iostream>
using namespace std;

class Node {
    public:
        string word;
        string meaning;
        Node *next;
        int i;

        Node(string w = "null", string m = "unknown")
        {
            next = NULL;
            word = w;
            meaning = m;
        }
};

class LinkedList{
    public:
        int size;
        Node *head, *tail;

        LinkedList() {
            size = 0;
            head = tail = NULL;
        }

        void add(Node * node) {
            node->i = size;
            size++;

            if(head == NULL)
                head = tail = node;
            else {
                tail->next = node;
                tail = tail->next;
            }
        }

        string remove(string key) {

            if(head == NULL)
                return NULL;

            else {

                size--;

                if(head->word == key && head==tail) {
                    string mean = head->meaning;
                    head = tail = NULL;
                    return mean;
                }
                else if (head->word == key) {
                    string mean = head->meaning;
                    Node *temp = head;
                    head = head->next;
                    delete temp;
                    return mean;
                }
                else {

                    Node *prev = head;
                    Node *curr = head->next;

                    while(curr != NULL && curr->word != key){
                        prev = curr;
                        curr = curr->next;
                    }

                    if(curr == NULL){
                        size++;
                        return NULL;
                    }
                    else {
                        string mean = curr->meaning;
                        prev->next = curr->next;

                        if(curr == tail)
                            tail = prev;

                        delete curr;

                        return mean;
                    }
                }
                
            }
        }

        Node* get(int idx) {
            int i = 0;
            Node *temp = head;
            while(i<idx){
                temp = temp->next;
                i++;
            }
            return temp;
        }
        
        int search(string key) {
            // int di = 0;
            // Node *temp = head;
            // while(temp != NULL) {
            //     if(temp->word == key)
            //         return di;
            //     di++;
            //     temp = temp->next;
            // }
            // return -1;
            for (int i = 0; i < size; i++) {
                if(get(i)->word == key)
                    return i;
            }
            return -1;
        }

        void printll(){
        if(head == NULL) {
            cout << "empty LL\n";
            return;
        }
        Node * temp = head;
        while(temp != NULL) {
            cout << '[' << temp->word << " : " << temp->meaning << ']' << "->";
             
            temp = temp->next;
        }
        cout << "NULL" <<endl;
    }

};

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
        if(isalphabate(i))         //alpha asel tr ch str la add else skip 
            result += tolowerA(i);     //tolower added always
    }
    return result;
}

class Dict {

    int hash(string str) {
        return str[0] - 'a';
    }

    public:
        LinkedList *table[26];

        Dict() {
            cout << "tDictionary creation successfull !!\n\n";
        }

        void put(string str, string mean = "unknown") {

            cout << "hi";
            str = modify(str);
            cout << str << " ";
            int bi = hash(str);
            cout << bi << endl;
            // int di = table[bi]->search(str);
            // cout << di << endl;
            Node *n = new Node(str, mean);
            table[bi]->add(n);
            cout << "done";
                }

        bool containsWord(string key) {
            key = remove(key);
            int bi = hash(key);
            int di = table[bi]->search(key);

            return di != -1;
        }

        string remove(string w) {

            int bi = hash(w);
            int di = table[bi]->search(w);

            if(di==-1){
                return table[bi]->remove(w);
            }
            return "none";
        }

        string get(string w) {

            w = remove(w);
            int bi = hash(w);
            int di = table[bi]->search(w);
            return di == -1 ? "none" : table[bi]->get(di)->meaning;
        }
        void print(){
            cout << "index\tchar\tlinked list\n";
            cout << "=================================\n";
            for (int i = 0; i < 26; i++) {
                cout << i << "\t" << (char)(i + 'a') << "\t";
                table[i]->printll(); // print whole ll starting frm alpha.
                cout << "\n=================================\n";
            }
        }
};

int main() {

        LinkedList* ll = new LinkedList();
        Node *n = new Node("a", "A");
        ll->add(n);
        n= new Node("b", "B");
        ll->add(n);
        n= new Node("c", "C");
        ll->add(n);
        ll->printll();
        cout << ll->get(2)->word;
        cout << ll->search("a") << "\t" << ll->search("b") << "\t" << ll->search("c") << "\t";
        ll->remove("a");
        ll->printll();
        // return 0;

        Dict *d = new Dict();
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
                "Decorum", "Marshmallow"};

        // for(int i=0; i<1; i++)
        // d->put(arr[i]);
    int choice;
    string str;
    string mean;


    while(true) {

        cout << "1. put()\n";
        cout << "2. get()\n";
        cout << "3. containsWord()\n";
        cout << "4. remove()\n";
        cout << "5. print()\n";
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
                d->put(str, mean);
                break;
            
            case 2:
                cout << "Enter key -> ";
                cin >> str;
                cout << d->get(str) << endl;
                break;

            case 3:

                cout << "Enter key -> ";
                cin >> str;
                cout << d->containsWord(str) << endl;
                break;
                
            case 4:
                cout << "Enter key -> ";
                cin >> str;
                cout << d->remove(str) << endl;
                break;

            case 5:
                d->print();
                break;
            default:
                break;
        }
    }
}