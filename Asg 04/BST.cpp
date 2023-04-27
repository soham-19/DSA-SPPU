#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class Node
{

public:
	Node *left;
	int val;
	Node *right;

	Node(int v)
	{
		val = v;
		left = right = NULL;
	}
};

class BST
{

public:
	Node *root;

	BST()
	{
		cout << "BST creation successfull...\n";
		root = NULL;
	}

	void inOrder()
	{

		if (root == NULL)
			return;

		stack<Node *> s;
		Node *temp = root;

		cout << "in : ";
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

			cout << temp->val << " ";

			temp = temp->right;
		}
	}

	void inOrderDec()
	{

		if (root == NULL)
			return;

		stack<Node *> s;
		Node *temp = root;

		cout << "in : ";
		while (true)
		{

			while (temp != NULL)
			{
				s.push(temp);
				temp = temp->right;
			}

			if (s.empty())
			{
				cout << endl;
				break;
			}

			temp = s.top();
			s.pop();

			cout << temp->val << " ";

			temp = temp->left;
		}
	}

	void preOrder()
	{

		if (root == NULL)
			return;

		stack<Node *> s;
		Node *temp = root;

		cout << "pre : ";
		while (true)
		{
			while (temp != NULL)
			{
				cout << temp->val << " ";
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

			temp = temp->right;
		}
	}

	void DFS()
	{

		if (root == NULL)
			return;

		stack<Node *> s;
		Node *temp = root;

		cout << "DFS : ";
		do
		{

			cout << temp->val << " ";

			if (temp->right != NULL)
				s.push(temp->right);

			if (temp->left != NULL)
				s.push(temp->left);

			if (s.empty())
			{
				cout << endl;
				break;
			}

			temp = s.top();
			s.pop();

		} while (true);
	}

	void BFS()
	{

		if (root == NULL)
			return;

		Node *temp = root;
		queue<Node *> q;
		cout << "BFS : ";

		while (true)
		{

			cout << temp->val << " ";

			if (temp->left != NULL)
				q.push(temp->left);

			if (temp->right != NULL)
				q.push(temp->right);

			if (q.empty())
				break;

			temp = q.front();
			q.pop();
		}
	}

	void insert(int data)
	{

		if (root == NULL)
		{
			root = new Node(data);
			return;
		}

		Node *newN = new Node(data);
		Node *temp = root;

		while (temp != NULL)
		{
			if (newN->val < temp->val)
			{
				if (temp->left == NULL)
				{
					temp->left = newN;
					return;
				}
				else
					temp = temp->left;
			}
			else if (newN->val > temp->val)
			{
				if (temp->right == NULL)
				{
					temp->right = newN;
					break;
				}
				else
					temp = temp->right;
			}
			else
			{
				cout << "Data exists..\n";
				return;
			}
		}
	}

	int noOfNodesInLongestPath(Node *root) {	// height in terms of nodes

		if(root == NULL)
			return 0;

		return max(noOfNodesInLongestPath(root->left), noOfNodesInLongestPath(root->right)) + 1;
	}

	int getMinimum() {
		if(root == NULL)
			return 1;

		Node *temp = root;
		while(temp->left != NULL){
			temp = temp->left;
		}
		return temp->val;
	}

	int getMaximum() {
		if(root == NULL)
			return -1;

		Node *temp = root;
		while(temp->right != NULL){
			temp = temp->right;
		}
		return temp->val;
	}

	Node *mirror(Node *root) {

		if(root == NULL)
			return root;

		Node *Left = mirror(root->left);
		Node *Right = mirror(root->right);

		root->left = Right;
		root->right = Left;

		return root;
	}
	
	bool search(Node *root, int x)
	{
		if (root == NULL)
			return false;
		if (root->val == x)
			return true;

		if (x < root->val)
			return search(root->left, x);
		else
			return search(root->right, x);
	}
};

int main()
{

	int x;
	BST bstree;

	for (int i = 0; i < 15; i++){
		cout << " -> ";
		cin >> x;
		bstree.insert(x);
	}

	bstree.inOrder();
	cout << " height = " << bstree.noOfNodesInLongestPath(bstree.root);
	return 0;
}