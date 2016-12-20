// problem2.cpp : Defines the entry point for the console application.

//#include "stdafx.h";
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Values stored by tree
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

// Finds max tree depth
int MaxTreeDepth(struct Tree *node)
{
	if (node == NULL || (node->left == NULL && node->right == NULL))
		return 0;

	int leftDepth = MaxTreeDepth(node->left);
	int rightDepth = MaxTreeDepth(node->right);

	return leftDepth > rightDepth ?
		leftDepth + 1 : rightDepth + 1;
}

// puts tree in level order
void LevelOrderTree(struct Tree *node, vector<vector<string> >&myVect, int level)
{
	if (node == NULL) return;

	if (node->left == NULL && node->right == NULL) 
	{
		myVect[level].push_back(node->data);
		return;
	}

	myVect[level++].push_back(node->data);
	LevelOrderTree(node->left, myVect, level);
	LevelOrderTree(node->right, myVect, level);
}

// Deletes the tree
void DeleteTree(struct Tree *node)
{
	if (node != NULL)
	{
		DeleteTree(node->left);
		DeleteTree(node->right);
		delete node;
	}
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


	vector<vector<string> > myVect;
	
	int maxDepth = MaxTreeDepth(root);
	myVect.resize(maxDepth + 1);

	int level = 0;
	// puts tree in level order
	LevelOrderTree(root, myVect, level);
	// prints tree in level order
	for (int i = 0; i <= maxDepth; i++)
	{
		for (int j = 0; j < myVect[i].size(); j++)
		{
			cout << myVect[i][j] << " ";
		}
	}

	DeleteTree(root);

	return 0;
}