/*
Consider the telephone book database of N clients. Make use of a hash table implementation to quickly look up a client's telephone number. Make use of two collision handeling techniques and compare them using number of comparisions required to find a set of telephone numbers.
*/

#include <iostream>
using namespace std;
#define MAX 20

class Info
{

public:
	long int phnNo;
	string name;

	Info(long int phn = 0, string name = "")
	{
		phnNo = phn;
		this->name = name;
	}
};

class Hashing
{
public:
	int probe;
	int prime;
	int M;
	float a;

	Info table[MAX];

	Hashing(int M)
	{
		this->M = M;
		a = 0.6879f;
		prime = 37;
		cout << "Hash Table of size " << M << " created..." << endl;
	}

	void print()
	{
		string n;
		for (int i = 0; i < M; i++)
		{

			if (table[i].name != "")
				n = table[i].name;
			else
				n = "null";

			cout << i << " : " << table[i].phnNo << " : " << n << endl;
		}
		cout << endl;
	}

	// hash functions

	// store

	void store(Info key)
	{

		int i = mod(key);

		if (table[i].phnNo != 0)
			i = linearProbing(key,i);
		if (i == -1)
			return;
		table[i] = key;
	}
	/*
	void get(Info key)
	{

		int i = mod(key);
		if (table[i].phnNo == key.phnNo)
		{
			cout << "found at " << i << endl;
		}
		else
		{
			cout << "implementaining linear probing...\n";
			i = linearProbing(key, i);
			if (i == -1)
				return;

			cout << "implementaining quadratic probing...\n";
			i = linearProbing(key, i);
			if (i == -1)
				return;
		}

		return false;
		return table[i].phnNo == key.phnNo;
	}
	*/

	// mod
	int mod(Info key)
	{
		int idx = (key.phnNo) % M;
		if (idx >= M)
			return idx % M;
		return idx;
	}

	int linearProbing(Info key, int filled)
	{ // ( Hash(key) + i )%M;
		int i;
		if(filled == M-1)
			i = 0;
		else
			i = filled +1;

		while(i != filled) {

			if(table[i].phnNo == 0)
				return i;
			i++;
		}
		cout << "Linear Probing Failed to store " << key.phnNo << "\n";
		return -1;
	}

	/*
	int quadraticProbing(Info key)
	{
		int hash = mod(key);
		int i = 1;
		int j;
		while (i <= (M - 1)/ 2)
		{
			j = (hash + i * i) % M;
			if (table[j].phnNo == 0)
				return j;
			j = (hash - i * i) % M;
			if (table[j].phnNo == 0)
				return j;
			i++;
		}
		cout << "Quadratic probing Failed\n";
		return -1;
	}*/
};

int main()
{

	Hashing h(10);
	h.print();

	int i=9;
	for(int i1=0; i1<19; i1++) {
		string n = "he";
		n += to_string(i1);
		h.store(Info(i,n));
		i++;
	}

	h.print();

	return 0;
}