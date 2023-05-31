//C++ code for the above approach
#include <bits/stdc++.h>
using namespace std;

class Treenode {
public:
	int data;
	Treenode *left, *right;
	Treenode(int data) {
		this->data = data;
		left = right = NULL;
	}
};

class Tree {
public:
	Treenode *root;
	Tree() {
		root = NULL;
	}
};

int height(Treenode *root) {
	if (root == NULL)
		return 0;
	return max(height(root->left), height(root->right)) + 1;
}

int getcol(int h) {
	if (h == 1)
		return 1;
	return getcol(h - 1) + getcol(h - 1) + 1;
}

void printTree(int **M, Treenode *root, int col, int row, int height) {
	if (root == NULL)
		return;
	M[row][col] = root->data;
	printTree(M, root->left, col - pow(2, height - 2), row + 1, height - 1);
	printTree(M, root->right, col + pow(2, height - 2), row + 1, height - 1);
}

void TreePrinter(Tree tree) {
	int h = height(tree.root);
	int col = getcol(h);
	int **M = new int*[h];
	for (int i = 0; i < h; i++) {
		M[i] = new int[col];
	}
	printTree(M, tree.root, col / 2, 0, h);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < col; j++) {
			if (M[i][j] == 0)
				cout << " " << " ";
			else
				cout << M[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	Tree myTree;
	myTree.root = new Treenode(1);
	myTree.root->left = new Treenode(2);
	myTree.root->right = new Treenode(3);
	myTree.root->left->left = new Treenode(4);
	myTree.root->left->right = new Treenode(5);
	myTree.root->right->left = new Treenode(6);
	myTree.root->right->right = new Treenode(7);
	TreePrinter(myTree);
	return 0;
}
