// problem1.cpp : Defines the entry point for the console application.

//#include "stdafx.h";
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Values stored by tree
struct Tree
{
	string data;
	int leftNum;
	int rightNum;
	Tree *left;
	Tree *right;
};

// Creates tree node
struct Tree *NewTreeNode(string data, int leftNumber, int rightNumber)
{
	Tree *node = new Tree;
	node->data = data;
	node->leftNum = leftNumber;
	node->rightNum = rightNumber;
	node->left = NULL;
	node->right = NULL;
	return node;
}

// Creates tree from values placed in vectors
struct Tree* CreateTree(struct Tree *node, vector<Tree*>& myVector)
{
	if (node->leftNum != -1)
	{
		node->left = myVector[node->leftNum];
		node->left = CreateTree(node->left, myVector);
	}
	if (node->rightNum != -1)
	{
		node->right = myVector[node->rightNum];
		node->right = CreateTree(node->right, myVector);
	}
	return node;
}

// Deletes tree 
void DeleteTree(struct Tree *node)
{
	if (node != NULL) 
	{
		DeleteTree(node->left);
		DeleteTree(node->right);
		delete node;
	}
}

/* print tree inorder */
void PrintTreeInOrder(struct Tree *node)
{
	if (node == NULL) return;

	PrintTreeInOrder(node->left);
	cout << node->data << " ";
	PrintTreeInOrder(node->right);
}

/* print tree in postorder*/
void PrintTreePostOrder(struct Tree *node)
{
	if (node == NULL) return;

	PrintTreePostOrder(node->left);
	PrintTreePostOrder(node->right);
	cout << node->data << " ";
}

/* print in preorder */
void PrintTreePreOrder(struct Tree *node)
{
	if (node == NULL) return;

	cout << node->data << " ";
	PrintTreePreOrder(node->left);
	PrintTreePreOrder(node->right);
}

int main()
{
	int numberOfNodes;
	cin >> numberOfNodes;

	string data;
	int leftNode;
	int rightNode;
	
	vector<Tree*> myVector;
	Tree *root;
	
	for (int i = 0; i < numberOfNodes; i++)
	{	
		cin >> data;
		cin >> leftNode;
		cin >> rightNode;
		Tree *root = NewTreeNode(data, leftNode, rightNode);
		myVector.push_back(root);
	}
	
	root = myVector[0];
	CreateTree(root, myVector);
	
	PrintTreePostOrder(root);
	cout << endl;

	PrintTreeInOrder(root);
	cout << endl;

	PrintTreePreOrder(root);

	DeleteTree(root);

	//int meow;
	//cin >> meow;

	return 0;
}