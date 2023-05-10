//Assignment 4
#include <iostream>
#include <string.h>
#include <stack>
#include <queue>
using namespace std;
class node
{
public:
    char word[10];
    node *left, *right;
    node()
    {
        left = NULL;
        right = NULL;
    }
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
    void inr();
    void prer();
    void post();
    void dfs();
    void bfs();
    void descending_order(node *);
    void max_element();
    void min_element();
    node *search_element(char[]);
    int height_tree(node *);
    void height();
    void mirror(node *);
    void mirror_image();
    node *prev_search(char[]);
    void delete_element(char[]);
    int compare_element(char[], char[]);
    int finding_nodes(node *);
    int counting_comparisons(int);
    int count_nodes(node *);
    void counting_nodes();
    int leaf_nodes(node *);
    void counting_leaf();
    int max_path_length(node *);
    void max_path_nodes();
};
void btree::create_node()
{
    node *New;

    New = new node;
    cout << "enter word which you want to insert:" << endl;
    cin >> New->word;
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
                cout << "element is already present" << endl;
                return;
            }
        }
    }
}
void btree::inr()
{
    node *temp;
    temp = root;
    stack<node *> s;
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
            cout << temp->word << " ";
            temp = temp->right;
        }
    }
}
void btree::descending_order(node *temp)
{
    if (temp != NULL)
    {
        descending_order(temp->right);
        cout << temp->word << " ";
        descending_order(temp->left);
    }
}
void btree::prer()
{
    node *temp;
    stack<node *> s;
    temp = root;
    while (1)
    {
        while (temp != NULL)
        {
            cout << temp->word << " ";
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
            temp = temp->right;
        }
    }
}
void btree::post()
{
    stack<node *> s1, s2;
    node *temp, *T;
    temp = root;
    s1.push(temp);
    while (!s1.empty())
    {
        T = s1.top();
        s1.pop();
        s2.push(T);
        if (T->left != NULL)
        {
            s1.push(T->left);
        }
        if (T->right != NULL)
        {
            s1.push(T->right);
        }
    }
    while (!s2.empty())
    {
        T = s2.top();
        s2.pop();
        cout << T->word << " ";
    }
}
void btree::dfs()
{
    node *temp = root;
    stack<node *> s;
    while (1)
    {
        cout << temp->word << " ";
        if (temp->right != NULL)
        {
            s.push(temp->right);
        }
        if (temp->left != NULL)
        {
            s.push(temp->left);
        }
        if (s.empty())
            return;
        else
        {
            temp = s.top();
            s.pop();
        }
    }
}
void btree::bfs()
{
    node *temp = root;
    queue<node *> q;
    while (temp != NULL)
    {
        cout << temp->word << " ";
        if (temp->left != NULL)
        {
            q.push(temp->left);
        }
        if (temp->right != NULL)
        {
            q.push(temp->right);
        }
        if (q.empty())
            return;
        else
        {
            temp = q.front();
            q.pop();
        }
    }
}
void btree::max_element()
{
    node *temp = root, *prev;
    if (temp == NULL)
    {
        cout << "tree is empty" << endl;
    }
    while (temp != NULL)
    {
        prev = temp;
        temp = temp->right;
    }
    cout << "Maximum element is: " << prev->word << endl;
}
void btree::min_element()
{
    node *temp = root, *prev;
    if (temp == NULL)
    {
        cout << "tree is empty" << endl;
    }
    while (temp != NULL)
    {
        prev = temp;
        temp = temp->left;
    }
    cout << "Minimum element is: " << prev->word << endl;
}
void btree::display()
{
    int ch;

    cout << "enter which order you want to display:" << endl;
    cout << "\n 1.preorder \n2.inorder \n3.postorder \n4.depthfirst traversal"
         << " \n5.breadthfirst traversal \n6.descending order" << endl;
    cout << "enter your choice:" << endl;
    cin >> ch;

    switch (ch)
    {
    case 1:
        prer();
        cout << endl;
        break;
    case 2:
        inr();
        cout << endl;
        break;
    case 3:
        post();
        cout << endl;
        break;
    case 4:
        dfs();
        cout << endl;
        break;
    case 5:
        bfs();
        cout << endl;
        break;
    case 6:
        descending_order(root);
        cout << endl;
        break;
    }
}
node *btree::prev_search(char word[])
{
    node *temp, *prev;
    temp = root;
    int i = 0;
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
    return prev;
}
node *btree::search_element(char word[])
{
    node *temp = root;
    int i = 0;
    int count = 0;
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
                        i++;
                        count++;
                    }
                }
            }
        }
        if (temp == NULL)
        {
            cout << "element is not found" << endl;
        }
    }
    counting_comparisons(count);
    return temp;
}
int btree::counting_comparisons(int x)
{
    cout << "No of comparisons required are:" << x << endl;
    return x;
}
int btree::height_tree(node *temp)
{
    int lh, rh;
    if (temp == NULL)
    {
        return 0;
    }
    if (temp->left == NULL && temp->right == NULL)
    {
        return 0;
    }
    lh = height_tree(temp->left);
    rh = height_tree(temp->right);
    if (lh > rh)
    {
        return lh + 1;
    }
    else
    {
        return rh + 1;
    }
}
void btree::height()
{
    int h = height_tree(root);
    cout << "height of tree is " << h << endl;
}
void btree::mirror(node *temp)
{
    node *t = new node;
    if (temp == NULL)
    {
        cout << "Tree is empty" << endl;
    }
    if (temp != NULL)
    {
        t = temp->left;
        temp->left = temp->right;
        temp->right = t;
    }
    if (temp->left != NULL)
    {
        mirror(temp->left);
    }
    if (temp->right != NULL)
    {
        mirror(temp->right);
    }
}
void btree::mirror_image()
{
    mirror(root);
}
int btree::compare_element(char New[], char exist[])
{
    int i = 0;
    int ch;
    while (New[i] != '\0')
    {
        if (New[i] > exist[i])
        {
            ch = 1;
            break;
        }
        else if (New[i] < exist[i])
        {
            ch = 0;
            break;
        }
        else
        {
            i++;
        }
    }
    return ch;
}
void btree::delete_element(char word[])
{
    node *temp = search_element(word);
    node *prev = prev_search(word);
    node *previous;

    int compare;
    if (temp != NULL)
    {
        compare = compare_element(temp->word, prev->word);
    }
    int i = 0;
    if (root == NULL)
    {
        cout << "tree is empty" << endl;
    }
    if (strcmp(root->word, word) == 0)
    {
        if (root->left != NULL)
        {
            previous = root;
            root = root->left;
            while (root->right != NULL)
            {
                root = root->right;
            }
            if (root->right == NULL)
            {
                root->right = previous->right;
                return;
            }
        }
        else
        {
            root = root->right;
        }
    }

    else if (temp != NULL)
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
        cout << "No such word is present in the tree" << endl;
    }
}
int btree::count_nodes(node *temp)
{
    if (temp == NULL)
    {
        return 0;
    }
    else
    {
        return (1 + count_nodes(temp->left) + count_nodes(temp->right));
    }
}
void btree::counting_nodes()
{
    int x = count_nodes(root);
    cout << "no. of nodes in the tree are: " << x << endl;
}
int btree::leaf_nodes(node *temp)
{
    int lh, rh;
    if (temp == NULL)
    {
        return 0;
    }
    else if (temp->left == NULL && temp->right == NULL)
    {
        return 1;
    }
    else
    {
        lh = leaf_nodes(temp->left);
        rh = leaf_nodes(temp->right);
        return lh + rh;
    }
}
void btree::counting_leaf()
{
    int x = leaf_nodes(root);
    cout << "no. of leaf nodes in the tree are:" << x << endl;
}
int main()
{
    btree bt;
    int ch;
    char word[20];
    do
    {
        cout << "\nOPERATIONS TO BE PERFORMED ON TREE"
             << "\n1.insert node \n2.display tree"
             << "\n3.Maximum element\n4.Minimum element"
             << "\n5.search element\n6.height of tree(no.of nodes in longest path from root)"
             << "\n7.mirror of tree\n8.delete element"
             << "\n9.counting no of nodes in the tree"
             << "\n10.counting no of leafnodes in the tree"
             << endl;
        cout << "enter your choice:" << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            bt.create_node();
            break;
        case 2:
            bt.display();
            break;
        case 3:
            bt.max_element();
            break;
        case 4:
            bt.min_element();
            break;
        case 5:
            cout << "enter word which want to search:";
            cin >> word;
            if (bt.search_element(word) != NULL)
            {
                cout << "element is found" << endl;
            }
            else
            {
                cout << "element is not found" << endl;
            }
            break;
        case 6:
            bt.height();
            break;
        case 7:
            bt.mirror_image();
            break;
        case 8:
            cout << "enter word which want to delete";
            cin >> word;
            bt.delete_element(word);
            break;
        case 9:
            bt.counting_nodes();
            break;
        case 10:
            bt.counting_leaf();
            break;
        default:
            cout << "Enter valid choice!!!" << endl;
            break;
        }
    } while (ch != 0);
    return 0;
}