/*Construct an expression tree from the given prefix expression eg. +--a*bc/def
 and traverse it using post order traversal
(non recursive ) and then delete the entire tree*/

#include <iostream>
#include <string  >
using namespace std;

struct node
{
    char data;
    node *left;
    node *right;
};

class tree
{
    public:
    char prefix[20];

    node *top;
    void expression(char[]);
    void display(node *);
    void non_rec_postorder(node *);
    void del(node *);
    int strlength(char[]);
    bool isalphabate(char ch)
    {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
    }
};

class stack
{
    node *data[30];
    int top;

public:
    stack()
    {
        top = -1;
    }
    int empty()
    {
        if (top == -1)
            return 1;
        return 0;
    }
    void push(node *p)
    {
        data[++top] = p;
    }
    node *pop()
    {
        return (data[top--]);
    }
};
int tree::strlength(char prefix[])
{
    int count = 0;
    for (int i = 0; prefix[i]; i++)
    {
        count++;
    }
    return count;
}

void tree::expression(char prefix[])
{
    char c;
    stack s;
    node *t1, *t2;
    
    int len = strlength(prefix);
    for (int i = len - 1; i >= 0; i--)
    {
        top = new node;
        top->left = NULL;
        top->right = NULL;
        if (isalphabate(prefix[i]))
        {
            top->data = prefix[i];
            s.push(top);
        }
        else if (prefix[i] == '+' || prefix[i] == '*' || prefix[i] == '-' || prefix[i] == '/')
        {
            t2 = s.pop();
            t1 = s.pop();
            top->data = prefix[i];
            top->left = t2;
            top->right = t1;
            s.push(top);
        }
    }
    top = s.pop();
}
void tree::display(node *root)
{
    if (root != NULL)
    {
        cout << root->data;
        display(root->left);
        display(root->right);
    }
}
void tree::non_rec_postorder(node *top)
{
    stack s1, s2; /*stack s1 is being used for flag . A NULL data implies that the right subtree has not been visited */
    node *T = top;
    cout << "\n";
    s1.push(T);
    while (!s1.empty())
    {
        T = s1.pop();
        s2.push(T);
        if (T->left != NULL)
            s1.push(T->left);
        if (T->right != NULL)
            s1.push(T->right);
    }
    while (!s2.empty())
    {
        top = s2.pop();
        cout << top->data;
    }
}
void tree::del(node *node)
{
    if (node == NULL)
        return;
    /* first delete both subtrees */
    del(node->left);
    del(node->right);
    /* then delete the node */
    cout << endl
         << "Deleting node : " << node->data << endl;
    free(node);
}
int main()
{
    char expr[20];
    tree t;

    cout << "Enter prefix Expression : ";
    cin >> expr;
    cout << expr;
    t.expression(expr);

    cout << "post : ";
    t.non_rec_postorder(t.top);
    t.del(t.top);
}