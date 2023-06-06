/*
Consider telephone book database of N clients. Make use of a hash table implementation to quickly look up client's telephone number
Make use of two collision handling techniques and compare them using number of comparisons required to find a set of telephone numbers
*/

#include<iostream>
#include<math.h>
using namespace std;
typedef unsigned long long int Long;

class Node{
	public:
		string name;
		Long phn;
		
		Node(Long phn=0, string name="null"){
			phn = phn;
			name = name;
		}
};

class Dict{
	public:
		int M;
		Node *table;
		double A = 0.61897654;
		
		Dict(){
			cout << "Enter initial hash-table size : ";
			cin >> M;
			table = new Node[M];
		}
		
		int hash1(Long);
		int hash2(Long);
		void add(Long, string);
};

int Dict::hash1(Long phn){
	int ans = 0;
	for(int i=0; i<3; i++){
		ans += phn%1000;
		phn /= 1000;		
	}
}

int Dict::hash2(Long phn){
	double fract = (phn*A)-floor(phn*A);
	int hashed = floor(fract*M);
	return hashed%M;
}

void Dict::add(Long ph, string name){
	
	int idx = hash1(ph);
	
	if(table[idx].phn == 0){
		table[idx].phn = ph;
		table[idx].name = name;
		cout << "\tInsertion : hashAddress = hash1()\n";
		return;
	}
	doubleHashing(ph,name);
}

void Dict::doubleHashing(Long ph, string name){
	int idx = hash1(ph);
	int initial = idx;
	int i=1;
	while(table[idx].phn != 0){
		idx = (initial + i*step)%M;
		i++;
		if(idx == initial){
			cout << "Hash table full.\n";
			cout << "ReHashing\n";
			reHash();
			add(ph,name);
		}
	}
	table[idx].phn = ph;
	table[idx].name = name;
	cout << "\tInsertion : hashAddress = hash1() + " << i << "*hash2()\n";
}

void Dict::remove(Long ph){
	int idx = hash1(ph);
	int initial = idx;
	int i=1;
	while(i<=M){
		if(table[idx].phn == ph){
			table[idx],phn = 0;
			table[idx].name = "null";
			cout << ph << " removed.\n";
			return;
		}
		idx = (initial + i*step)%M;
		i++;
	}
	cout << ph << " not found.\n";
}

void Dict::search(Long ph){
	int idx = hash1(ph);
	int initial = idx;
	int i=1;
	while(i<=M){
		if(table[idx].phn == ph){
			cout << "\tEntry found!!\n";
			cout << table[idx].phn << endl;
			cout << table[idx].name << endl;
			return;
		}
		idx = (initial + i*step)%M;
		i++;
	}
	cout << ph << " not found.\n";
}

int main(){
	
}
