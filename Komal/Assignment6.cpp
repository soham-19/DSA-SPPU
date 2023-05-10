// dictionary using binary search tree
#include <iostream>
#include <string.h>
#include <stack>
using namespace std;

class node
{
public:
    char word[10];
    char meaning[10];
    node *left, *right;
};
class btree
{
    node *root;

public:
    btree()
    {
        root = new node;
        root = NULL;
    }
    void create_node();
    void display();
    void insert_node(node *);
    void search_element(char[]);
    void modify_meaning(char[], char[]);
    void delete_element(char[]);
    void descendingorderdisplay(node *);
    void ascendingorderdisplay();
    void deleteall();
};
void btree::deleteall(){
    root=NULL;
}
void btree::create_node()
{
    node *New;

    New = new node;
    cout << "enter word which you want to insert:" << endl;
    cin >> New->word;
    cout << "enter meaning of " << New->word << " :" << endl;
    cin >> New->meaning;
    New->left = NULL;
    New->right = NULL;
    insert_node(New);
}
void btree::insert_node(node *New)
{
    char ch;
    node *temp;
    int i = 0;
    temp = new node;
    temp = root;
    if (root == NULL)
    {
        root = New;
    }
    else
    {
        while (temp != NULL)
        {
            while (New->word[i] != '\0')
            {
                if (int(toupper(New->word[i])) > int(toupper(temp->word[i])))
                {
                    if (temp->right == NULL)
                    {
                        temp->right = New;
                        return;
                    }
                    else
                    {
                        temp = temp->right;
                    }
                }
                else if ((int(toupper(New->word[i])) < int(toupper(temp->word[i]))))
                {
                    if (temp->left == NULL)
                    {
                        temp->left = New;
                        return;
                    }
                    else
                    {
                        temp = temp->left;
                    }
                }
                else
                {
                    i++;
                }
            }
            if (New->word[i] == '\0')
            {
                cout << "word is already present" << endl;
                return;
            }
        }
    }
}
void btree::search_element(char word[])
{
    node *temp = root;
    int i = 0;
    int count=0;
    if (root == NULL)
    {
        cout << "tree is empty" << endl;
    }
    else
    {
        while (temp != NULL)
        {
            if (strcmp(temp->word, word) == 0)
            {
                count++;
                cout << temp->word << " is found and its meaning is " << temp->meaning << endl;
                cout<<"No of comparison required are "<<count<<endl;
                break;
            }
            else
            {
                while (word[i] != '\0')
                {
                    if (temp->word[i] > word[i])
                    {
                        temp = temp->left;
                        count++;
                        break;
                    }
                    else if (temp->word[i] < word[i])
                    {
                        temp = temp->right;
                        count++;
                        break;
                    }
                    else
                    {
                        count++;
                        i++;
                    }
                }
            }
        }
        if (temp == NULL)
        {
            cout << "word not found in the dictionary" << endl;
        }
    }
}
void btree::modify_meaning(char word[], char meaning[])
{
    node *temp = root;
    int i = 0;
    if (root == NULL)
    {
        cout << "tree is empty" << endl;
    }
    else
    {
        while (temp != NULL)
        {
            if (strcmp(temp->word, word) == 0)
            {
                strcpy(temp->meaning, meaning);
                return;
            }
            else
            {
                while (word[i] != '\0')
                {
                    if (temp->word[i] > word[i])
                    {
                        temp = temp->left;
                        break;
                    }
                    else if (temp->word[i] < word[i])
                    {
                        temp = temp->right;
                        break;
                    }
                    else
                    {
                        i++;
                    }
                }
            }
        }
        if (temp == NULL)
        {
            cout << "word not found in the dictionary" << endl;
        }
    }
}
void btree::delete_element(char word[])
{
    node *temp = root;
    node *prev = temp;
    int i = 0;
    if (root == NULL)
    {
        cout << "tree is empty" << endl;
    }
    if(strcmp(root->word, word) == 0){
        if(root->left!=NULL){
            prev=root;
            root=root->left;
            while(root->right!=NULL){
                root=root->right;
            }
            if(root->right==NULL){
                root->right=prev->right;
                return;
            } 
        }
        else{
            root=root->right;
        }
    }
    else
    {
        while (temp != NULL)
        {
            if (strcmp(temp->word, word) == 0)
            {
                while (word[i] != '\0')
                {
                    if (prev->word[i] > word[i])
                    {
                        if (temp->left != NULL)
                        {
                            prev->left = temp->left;
                            while (prev->right != NULL)
                            {
                                prev = prev->right;
                            }
                            if (prev->right == NULL)
                            {
                                prev->right = temp->right;
                                return;
                            }
                        }
                        else
                        {
                            prev->left = temp->right;
                            return;
                        }
                    }
                    else if (prev->word[i] < word[i])
                    {
                        if (temp->left != NULL)
                        {
                            prev->right = temp->left;
                            while (prev->right != NULL)
                            {
                                prev = prev->right;
                            }
                            if (prev->right == NULL)
                            {
                                prev->right = temp->right;
                                return;
                            }
                        }
                        else
                        {
                            prev->right = temp->right;
                            return;
                        }
                    }
                    else
                    {
                        i++;
                    }
                }
            }
            else
            {
                while (word[i] != '\0')
                {
                    if (temp->word[i] > word[i])
                    {
                        prev = temp;
                        temp = temp->left;
                        break;
                    }
                    else if (temp->word[i] < word[i])
                    {
                        prev = temp;
                        temp = temp->right;
                        break;
                    }
                    else
                    {
                        i++;
                    }
                }
            }
        }
        if (temp == NULL)
        {
            cout << "word not found in the dictionary" << endl;
        }
    }
}
void btree::display()
{
    int ch;
    cout<<"1.Ascending order\n2.Descending order display"<<endl;
    cout<<"enter your choice:";
    cin>>ch;
    switch(ch){
        case 1:
        ascendingorderdisplay();
        cout<<endl;
        break;
        case 2:
        descendingorderdisplay(root);
        cout<<endl;
        break;
    }
    
}
void btree::descendingorderdisplay(node *temp){
    if(root==NULL){
        cout<<"dictionary is empty"<<endl;
    }
    if(temp!=NULL){
        descendingorderdisplay(temp->right);
        cout<<temp->word<<" "<<temp->meaning<<endl;
        descendingorderdisplay(temp->left);
    }
}
void btree::ascendingorderdisplay(){
    node *temp;
    temp = root;
    stack<node *> s;
    if(root==NULL){
        cout<<"dictionary is empty"<<endl;
    }
    while (1)
    {
        while (temp != NULL)
        {
            s.push(temp);
            temp = temp->left;
        }
        if (s.empty())
        {
            return;
        }
        else
        {
            temp = s.top();
            s.pop();
            cout << temp->word << " "<<temp->meaning<<endl;
            temp = temp->right;
        }
    }
}

int main()
{
    btree bst;
    int ch;
    char word[20], meaning[20];
    do
    {
        cout << "1.inserting node\n2.display\n3.search word"
             << "\n4.modify meaning\n5.delete word\n6.clear dictionary" << endl;
        cout << "enter your choice:";
        cin >> ch;
        switch (ch)
        {
        case 1:
            bst.create_node();
            cout << endl
                 << endl
                 << endl;
            break;
        case 2:
            bst.display();
            cout << endl
                 << endl
                 << endl;
            break;
        case 3:
            cout << "which word do you want to search:";
            cin >> word;
            bst.search_element(word);
            cout << endl
                 << endl
                 << endl;
            break;
        case 4:
            cout << "Meaning of which word do you want to change:";
            cin >> word;
            cout << "enter new meaning:";
            cin >> meaning;
            bst.modify_meaning(word, meaning);
            cout << endl
                 << endl
                 << endl;
            break;
        case 5:
            cout << "enter which word you want to delete:";
            cin >> word;
            bst.delete_element(word);
            cout << endl
                 << endl
                 << endl;
            break;
        case 6:
            
            bst.deleteall();
            cout<<"All dictionary cleared";
            cout << endl
                 << endl
                 << endl;
            break;
        default:
            cout << "enter valid choice" << endl;
            cout << endl
                 << endl
                 << endl;
            break;
        }
    } while (ch != 0);
    return 0;
}
