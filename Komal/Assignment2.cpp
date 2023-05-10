// Assignment no 2
// phonebook
#include <iostream>
#define MAX 10
using namespace std;
class phonebook
{
public:
    string name;
    long int number;
    phonebook()
    {
        name = " ";
        number = 0;
    }
};
class hashtable
{
    phonebook phone[10];
    int pos;

public:
    hashtable()
    {
        for (int i = 0; i < MAX; i++)
        {
            phone[i].number = 0l;
            phone[i].name = " ";
        }
    }
    void display()
    {
        for (int i = 0; i < MAX; i++)
        {
            cout << i << ": " << phone[i].name << " " << phone[i].number << endl;
        }
    }
    void insert(phonebook);
    int hash(long int);
    int search(long int);
    void delet(long int);
};
int hashtable::hash(long int pno)
{
    return (pno % MAX);
}
void hashtable::insert(phonebook p)
{
    pos = hash(p.number);
    if (phone[pos].number == 0)
    {
        phone[pos] = p;
    }
    else
    {
        for (int i = (pos + 1) % MAX; i != pos; i = (i + 1) % MAX)
        {
            if (phone[i].number == 0)
            {
                phone[i] = p;
                break;
            }
        }
    }
}
int hashtable::search(long int ph)
{
    pos = hash(ph);
    int f;
    if (phone[pos].number == ph)
    {
        return pos;
    }
    else
    {
        for (int i = (pos + 1) % MAX; i != pos; i = (i + 1) % MAX)
        {
            if (phone[i].number == ph)
            {
                f = i;
                break;
            }
            else
            {
                f = -1;
            }
        }

        return f;
    }
}
void hashtable::delet(long int ph)
{
    pos = hash(ph);
    int f;
    if (phone[pos].number == ph)
    {
        phone[pos].name = " ";
        phone[pos].number = 0;
        cout << "deleted operation performed!!!" << endl;
    }
    else
    {
        for (int i = (pos + 1) % MAX; i != pos; i = (i + 1) % MAX)
        {
            if (phone[i].number == ph)
            {
                phone[i].name = " ";
                phone[i].number = 0;
                break;
            }
            else
            {
                f = -1;
            }
        }
        if (f = -1)
        {
            cout << "\n number not found in the phonebook" << endl;
        }
        else
        {
            cout << "deleted operation performed!!!" << endl;
        }
    }
}
int main()
{
    hashtable ht;
    phonebook pn;
    int i, n, choice, f;
    long int ph;
    do
    {
        cout << "Operations on phonebook" << endl;
        cout << "\n 1.inserting name and number in phonebook \n 2.deleting name and number from the phonebook"
             << "\n 3.searching phonebook \n4.displaying phonebook" << endl;
        cout << "\n enter your choice:" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:

            cout << "enter name which you want to insert" << endl;
            cin >> pn.name;
            cout << "enter number which you want to insert" << endl;
            cin >> pn.number;
            ht.insert(pn);

            break;
        case 2:
            cout << "enter which no. do you want to delete" << endl;
            cin >> ph;
            ht.delet(ph);
            break;
        case 3:
            cout << "enter which no. do you want to search:" << endl;
            cin >> ph;
            f = ht.search(ph);
            if (f > 0)
            {
                cout << "element found at" << f << endl;
            }
            else
            {
                cout << "element is not found" << endl;
            }
            break;
        case 4:
            ht.display();
            break;
        default:
            cout << "you enter invalid choice" << endl;
            break;
        }
    } while (choice != 0);
}