/*
Consider telephone book database of N clients. Make use of a hash table implementation to quickly look up client's telephone number
Make use of two collision handling techniques and compare them using number of comparisons required to find a set of telephone numbers
*/
#include <iostream>
#include <math.h>
using namespace std;
typedef unsigned long long int Long;

class Node
{
public:
    string name;
    Long phn;

    Node(Long phn = 0, string name = "null")
    {
        this->name = name;
        this->phn = phn;
    }
};

class Hash
{

    int hash1(Long);
    int hash2(Long);

    public:

        Node *table;
        int M; //  capacity
        int entries;
        const double th = 2.0;
        const double A = 0.6180339887;
    
        Hash()
        {
            cout << "Enter the size of hash-table : ";
            cin >> M;
            table = new Node[M];
            entries = 0;
            cout << hash1(8329310531);
        }
    
        void print();
        void printEntry(int);
        void add(Long, string);
        void search(Long);
        void remove(Long);
        void doubleHashing(Long, string);
        void reHash();
};
int Hash::hash1(Long Key)
{ // fold shift

    int hashAddress = 0;
    for (int i = 0; i < 3; i++)
    {
        hashAddress += Key % 1000;
        Key /= 1000;
    }
    return hashAddress % M;
}

int Hash::hash2(Long Key)
{ // multiplicative hashing

    double fract = (Key * A) - floor(Key * A);
    unsigned int hashAddress = floor(fract * M);
    return hashAddress % M;
}

void Hash::add(Long phn, string name)
{
    int index = hash1(phn);
    if (table[index].phn == 0)
    {
        table[index].phn = phn;
        table[index].name = name;
        entries++;
        cout << "\n\tEntry added successfully.\n\thashAddress = hash1()\n\n";
    }
    else
    {
        doubleHashing(phn, name);
    }
}
void Hash::doubleHashing(Long phn, string name)
{
    int initial = hash1(phn);
    int index = initial;
    int step = hash2(phn);
    int i = 1;
    while (table[index].phn != 0)
    {
        index = (initial + i * step) % M;
        if (index == initial)
        {
            cout << "Cannot add the entry. Hash table is full.\n";
            cout << "\treHashing()...\n\n";
            reHash();
            add(phn, name);
            return;
        }
        i++;
    }
    table[index].phn = phn;
    table[index].name = name;
    entries++;
    cout << "\n\tEntry added successfully.\n\thashAddress = hash1() + " << i << "*hash2()\n\n";
}

void Hash::search(Long phn)
{
    int index = hash1(phn);
    int initial = index;
    int step = hash2(phn);
    int i = 1;
    int probes = 0; // Counter to track the number of probes

    while (probes < M)
    {
        if (table[index].phn == phn)
        {
            cout << "\tTelephone number found!\n";
            cout << "\tName: " << table[index].name << "\n";
            cout << "\tTelephone: " << table[index].phn << "\n";
            return;
        }
        index = (initial + i * step) % M;
        i++;
        probes++;
    }

    cout << "Telephone number not found.\n";
}

void Hash::remove(Long phn)
{
    int index = hash1(phn);
    int initial = index;
    int step = hash2(phn);
    int i = 1;
    int probes = 0; // Counter to track the number of probes

    while (probes < M)
    {
        if (table[index].phn == phn)
        {
            table[index].phn = 0;
            table[index].name = "null";
            entries--;
            cout << "Telephone number removed successfully.\n";
            return;
        }
        index = (initial + i * step) % M;
        i++;
        probes++;
    }

    cout << "Telephone number not found.\n";
}

void Hash::print()
{
    cout << "index\t  phone\t\tname\n";
    for (int i = 0; i < M; i++)
    {
        printEntry(i);
    }
}

void Hash::printEntry(int i)
{

    cout << i << "\t";

    if (table[i].phn == 0)
        cout << "    N/A   ";
    else
        cout << table[i].phn;

    cout << "\t";
    cout << table[i].name;
    cout << "\n----------------------------------------\n";
}
void Hash::reHash()
{
    int oldCapacity = M;
    M *= 2;
    Node *temp = table;
    table = new Node[M];
    for (int i = 0; i < oldCapacity; i++)
    {
        if (temp[i].phn != 0)
        {
            add(temp[i].phn, temp[i].name);
        }
    }
    delete temp;
}
int main()
{
    Hash h;

    char ch;
    do{
        cout << "Enter num :";
        Long n;
        cin >> n;
        string x;
        cout << "Enter name : ";
        cin >> x;

        h.add(n, x);
        h.print();
        cout << "  ? ";
        cin >> ch;
    } while (ch == 'y');
    do{
        cout << "Enter num :";
        Long n;
        cin >> n;
        string x;
        cout << "Enter name : ";
        cin >> x;

        h.search(n);
        h.remove(n);
        h.print();
        cout << "  ? ";
        cin >> ch;
    } while (ch == 'y');
    }
