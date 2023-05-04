#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    char val;
    Node *left, *right;

    Node(char ch)
    {
        val = ch;
        left = right = NULL;
    }
};

class ExpressionTree
{
public:
    Node *root;

    ExpressionTree()
    {
        root = NULL;
    }

    bool isOperator(char ch)
    {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/';
    }

    void makeTree(string prefix)
    {

        stack<Node *> stk;

        int len = prefix.length();

        for (int i = len - 1; i >= 0; i--)
        {

            char ch = prefix[i];

            if (isOperator(ch))
            {

                Node *node = new Node(ch);

                if (!stk.empty())
                {
                    node->left = stk.top();
                    stk.pop();
                }

                if (!stk.empty())
                {
                    node->right = stk.top();
                    stk.pop();
                }
                stk.push(node);
            }
            else
            {
                Node *node = new Node(ch);
                stk.push(node);
            }
        }

        root = stk.top();
    }

    void in()
    {
        if (root == NULL)
        {
            cout << "Empty tree\n";
            return;
        }
        stack<Node *> s;
        Node *temp = root;
        cout << " inOrder : ";

        while (true)
        {
            while (temp != NULL)
            {
                s.push(temp);
                temp = temp->left;
            }
            if (s.empty())
            {
                cout << endl;
                break;
            }
            temp = s.top();
            s.pop();
            cout << temp->val;
            temp = temp->right;
        }
    }
};
int main()
{

    ExpressionTree et;

    et.makeTree("*-ab+cd");

    et.in();
}