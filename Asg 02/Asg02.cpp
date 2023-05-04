/*
Consider telephone book database of N clients. Make use of a hash table implementation to quickly look up client's telephone number 
Make use of two collision handling techniques and compare them using number of comparisons required to find a set of telephone numbers
*/
#include<iostream>
using namespace std;
typedef unsigned long long int Long;

class Node{

    string name;
    Long phn;
    int wt;

public:
    Node(string name="",Long ph=0){
        this->name = name;
        phn = ph;

        wt = 0;
        for (int i = 0; i < name.length(); i++){
            wt += (int)name[i];
        }
    }

    friend class Telephone;
};

class Telephone{

    int M;
    const double th = 2.0;
    int nodes;
    Node *table;

    public:

    Telephone(){
        nodes = 0;
        cout << "Enter the size of phone-book : ";
        cin >> M;
        cout << "Telephone-book of size " << M << " has been created.\n";
        table = new Node[M];
    }

    void rehash(){
        nodes = 0;
        int oldM = M;
        M = 2*M;
        cout << "Telephone-book of size " << M << " has been created.\n";
        Node *temp = table;
        table = new Node[M];

        for (int i = 0; i < oldM; i++) {
            if(temp[i].name!=""){
                add(temp[i].name, temp[i].phn);
            }
        }

        delete temp;

    }

    void printBook(){
        cout << "--------------------------------\n";
        cout << "index\tname\tphone\n";
        cout << "--------------------------------\n";
        for (int i = 0; i < M;i++){
            cout << i << ((table[i].name=="")?"null":table[i].name)<< "\t" << table[i].phn << "\t"<< table[i].wt << endl;
            cout << "--------------------------------\n";
        }
    }

    void add(string n,Long ph=100){

        double currentCap = (double)nodes / M;
        if(nodes==M){
            rehash();
        }

        Node node(n, ph);
        unsigned int idx = hash( node.wt);
        if(table[idx].wt == 0){
            table[idx] = node;
            cout << "Insertion "
                 << " completed.\n";
            nodes++;
            return;
        }
        int i = (idx == M - 1) ? 0 : idx + 1;

        for (; i != idx; i = (i + 1) % M) {
            if(table[i].wt==0){
                table[i] = node;
                cout << "Insertion successfull\n";
                nodes++;
                return;
            }
        }
        cout << "Insertion unsuccessfull\n";
    }

    int search(string n){

        Node temp(n);
        unsigned int idx = hash( temp.wt);
        int probe = 1;

        if(table[idx].wt == 0){
            cout << "Found at index " << idx << " with probe = "<<probe <<endl;
            return idx;
        }
        int i = (idx == M - 1) ? 0 : idx + 1;

        for (; i != idx; probe++, i = (i + 1) % M) {
            if(table[i].name==n){

                cout << "Found at index " << idx << " with probe = "<<probe <<endl;
                return i;
            }
        }
        cout << "Search unsuccessfull with probe = "<< probe <<"\n";
        return -1;
    }

    void dlt(string n){
        int idx = search(n);
        table[idx].name = "";
        table[idx].phn = 1;
        table[idx].wt = 0;
    }

    unsigned int hash(int w){
        return w % M;
    }

};

int main(int argc, char const *argv[])
{
        Telephone *tb = new Telephone();
        
        int x;
        string name;
        int n;

        cout << "   *** PHONEBOOK ***\n\n";

        while(true) {

            cout << "Select Operatin\n";
            cout << "1. add()\n";
            cout << "2. search()\n";
            cout << "3. containsKey()\n";
            cout << "4. remove()\n";
            cout << "5. print()\n";
            cout << "6. rehash()\n";
            cout << "-1. exit()\n";
            cout << "--> ";
            cin >> x;

            switch(x) {

                case -1:
                    cout << "T E R M I N A T I N G\n";
                    return 0;
                case 1:
                    cout << "Enter name : ";
                    cin >> name;
                    cout << "Enter number : ";
                    cin >> n;
                    tb->add(name, n);
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    cout << "Enter name : ";
                    cin >> name;
                    tb->dlt(name);
                    break;
                case 5:
                    tb->printBook();
                    break;
                
            }
        }
        return 0;
}