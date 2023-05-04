// 15/03/23

/*
Consider the telephone book database of N clients. Make use of a hash table implementation to quickly look up a client's telephone number. Make use of two collision handeling techniques and compare them using number of comparisions required to find a set of telephone numbers.
*/

#include <iostream>
#include<math.h>
using namespace std;
typedef unsigned long long int Long;

class Info {
    public:
    string name;
    Long phn;

    Info(Long phn = 0,string name = "") {
        this->name = name;
        if(phn%1000000000==0)
            this->phn = 0;
        else
            this->phn = phn;
    }
};

class Hashing {
    public:
    int M;
    int probe;
    Info* table;

    Hashing(int);
    void print();
    int hash(Long);
    int folding(Long);
	int linearProbing(Long);
    void store(Info);
    int makeNum(Long);
    bool lookup(Long);
    void search(Long);
    void remove(Long);
};

Hashing::Hashing(int M) {
    this->M = M;
    table = new Info[M];
    cout << "Hash Table of size " << M << " created\n";
}

void Hashing::print() {
    cout << "--------------------------------\n";
    cout << "index\tphn\tname\n";
    cout << "--------------------------------\n";
    for(int i=0; i<M; i++) {
        cout << i << ":\t" << table[i].phn << "\t" << (table[i].name==""?"\tempty":table[i].name) << endl;
        cout << "--------------------------------\n";
    }
    cout << endl;
}

int Hashing::hash(Long num) {
    return folding(num);
}

int Hashing::folding(Long num) {
    int folded = 0;
    int sum = 0;
    while(true) {
                            
        if(num<10){
            break;
        }
        folded = makeNum(num);
            sum += folded;
        num /= 1000;
    }

    return sum;
}

int Hashing :: makeNum(Long i) {
    int j = 0;
    int count = 0;
    while(count <3){
        int dig = i%10;
        j = 10*j + dig;
        i /=10;
        count++;
    }
    return j;
}
int Hashing::linearProbing(Long num) { // ( Hash(key) + i )%M;
    probe = 1;
    int filled = hash(num);
	int i;
	if(filled == M-1)
		i = 0;
	else
		i = filled +1;
		while(i != filled) {
            probe++;
	    	if(table[i].phn == 0)
			    return i;
    		i++;
		}
	// cout << "Linear Probing Failed to store " << num << "\n";
	return -1;
}


void Hashing::store(Info key) {

    int idx = hash(key.phn);

    if(table[idx].phn != 0) {
        idx = linearProbing(key.phn);
    }
    if(idx==-1)
        return;
    table[idx] = key;
}

bool Hashing:: lookup(Long num) {

    int idx = hash(num);
    probe = 1;

    if(table[idx].phn == num) {
        // cout << num << " found in constant time\n";
        return true;
    }
    else {
        idx = linearProbing(num);

        if(idx==-1) {
            // cout << num << " not found in hashtable\n";
            return false;
        }
        else {
            // cout << num << "found -> probe = " << probe << endl;
            return true;
        }
    }
}
void  Hashing:: search(Long num) {
    bool found = lookup(num);
    if(found == false) {
        cout << "not found in hash-table\n";
    }
    else{
        cout << "found with probe = " << probe << endl;
    }
}

void Hashing:: remove(Long num) {

    bool found = lookup(num);
    if(found == false){
        cout << "no deletion possible as record not found\n";
    }
    else {
        int idx = hash(num);

        if(table[idx].phn != num) {
            idx = linearProbing(num);
        }

        if(idx==-1)
            return;

        table[idx].phn = 0;
        table[idx].name = "";
        cout << "deletion successfull!!\n";
    }
    // print();
}

int main() {

    int n;
    string name;
    Long no;

    cout << "   W E L C O M E\n\n";

    do {
        cout << "Enter size of hash-table : ";
        cin >> n;
    }   while(n>100);

    Hashing hashObj(n);

    while(true) {

        cout << "Enter your choice.\n\n";
        cout << "1. Print Hash-Table\n";
        cout << "2. Store an entry\n";
        cout << "3 Search for an entry\n";
        cout << "4 Delete an entry\n";

        cout << " -> ";
        int ch; 
        cin >> ch;
        cout << "----------------------------------------------------------\n\n";

        if(ch == 0) {
            cout << "   T E R M I N A T I N G\n\n";
            exit(0);

        }
        else if (ch == 1) {
            hashObj.print();

        }
        else if (ch == 2) {
            cout << "Tel. No. -> ";
            cin >> no;
            cout << "Name -> ";
            cin >> name;
            Info obj(no, name);
            hashObj.store(obj);
        }
        else if(ch ==3) {
            cout << "->Phn No :  ";
            cin >> no;
            hashObj.search(no);

        }
        else if(ch==4) {
            cout << "->Phn No :  ";
            cin >> no;
            hashObj.remove(no);
        }    
        else {
            cout << "Re-enter ";
        }
    }
    return 0;
}
