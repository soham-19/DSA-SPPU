#include <iostream>
#include <string.h>
#define MAX 26
#define limit 20
using namespace std;
class node
{
public:
    char word[limit], meaning[limit];
    node *next;
};
class hashtable
{
    node *table[MAX];
    int pos;

public:
    hashtable()
    {
        for (int i = 0; i < MAX; i++)
        {
            table[i] = new node;
            table[i] = NULL;
        }
    }
    void display();
    void createinfo();
    void insert(node *);
    int hash(char[]);
    void delet(char[]);
    void search(char[]);
    void delete_all();
};
void hashtable::delete_all(){
    for (int i = 0; i < MAX; i++)
        {
            table[i] = NULL;
        }
}
void hashtable::display()
{
    node *temp;
    cout << "letter :word         meaning" << endl;
    for (int i = 0; i < MAX; i++)
    {
        temp = table[i];
        cout << char(i + 65) << "      : ";
        if (table[i] == NULL)
        {
            cout << "";
        }
        else
        {
            while (temp->next != NULL)
            {
                cout << temp->word << " : " << temp->meaning << "->";
                temp = temp->next;
            }
            if (temp->next == NULL)
            {
                cout << temp->word << " : " << temp->meaning << "->";
            }
        }
        cout << endl;
    }
}
void hashtable::createinfo()
{
    node *New;
    New = new node;
    cout << "enter word:" << endl;
    cin >> New->word;
    cout << "enter Meaning of entered word:" << endl;
    cin >> New->meaning;
    New->next = NULL;
    insert(New);
}
int hashtable::hash(char word[limit])
{
    return (toupper(word[0]) - 65);
}
void hashtable::insert(node *New)
{
    // int pos;
    pos = hash(New->word);
    node *temp;
    temp = table[pos];
    if (table[pos] == NULL)
    {
        table[pos] = New;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = New;
    }
}
void hashtable::delet(char word[])
{
    int count;
    count = 0;
    pos = hash(word);
    node *temp, *prev;
    temp = table[pos];
    if (table[pos] == NULL)
    {
        cout << "No such element is found" << endl;
    }
    else
    {
        if (strcmp(temp->word, word) == 0)
        {
            if (temp->next == NULL)
            {
                table[pos] = NULL;
            }
            else
            {
                table[pos] = temp->next;
            }
        }
        else
        {
            while (temp != NULL)
            {
                prev = temp;
                temp = temp->next;
                if (strcmp(temp->word, word) == 0)
                {
                    prev->next = temp->next;
                    break;
                }
                else
                {
                    count = -1;
                }
            }
            if (temp == NULL)
            {
                count = -1;
            }
        }
        if (count == -1)
        {
            cout << "No such element is found" << endl;
        }
        else
        {
            cout << word << "  is deleted" << endl;
        }
    }
}
void hashtable::search(char word[])
{
    pos = hash(word);
    node *temp;
    temp = table[pos];

    if (table[pos] == NULL)
    {
        cout << "NO such word found in the dictionary";
    }
    else
    {
        while (temp != NULL)
        {
            if (strcmp(temp->word, word) == 0)
            {
                cout << "Meaning of " << word << " is:" << temp->meaning << endl;
                break;
            }
            else
            {
                temp = temp->next;
            }
        }
        if (temp == NULL)
        {
            cout << "word is not found in the dictionary" << endl;
        }
    }
}
int main()
{
    hashtable ht;
    char key[limit];
    int ch;
    do
    {
        cout << "\n Menu" << endl;
        cout << "\n 1.insert word in dictionary\n 2.display dictionary\n 3.delete word from the dictionary\n 4.searching word in the dictionary" << endl;
        cout << "enter your choice:" << endl;
        cin >> ch;
        cout << endl
             << endl;
        switch (ch)
        {
        case 1:
            ht.createinfo();
            break;
        case 2:
            ht.display();
            break;
        case 3:
            cout << "enter word which you want to deleted" << endl;
            cin >> key;
            ht.delet(key);
            break;
        case 4:
            cout << "enter word which you want to search:" << endl;
            cin >> key;
            ht.search(key);
            break;
        default:
            cout << "please enter valid choice!!!" << endl;
            break;
        }
    } while (ch != 0);
    return 0;
}