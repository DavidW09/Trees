// problem3.cpp : Defines the entry point for the console application.

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

// Tree fields
struct Tree
{
	string data;
	Tree *left;
	Tree *right;
	Tree(string str) : data(str), left(NULL), right(NULL) {}
};

// Creates tree from inorder and postorder traversals
struct Tree* CreateTree(vector<string>& inorderVect, vector<string>& postorderVect)
{
	if (postorderVect.size() == 0) return NULL;
	int size = postorderVect.size();

	Tree* root = new Tree(postorderVect[size - 1]);
	stack<Tree*> myStack;
	
	myStack.push(root);
	int index = size - 1;
	
	for (int i = size - 2; i >= 0; i--) 
	{
		Tree* currentNode = myStack.top();
		if (myStack.top()->data != inorderVect[index])
		{
			currentNode->right = new Tree(postorderVect[i]);
			myStack.push(currentNode->right);
		}
		else 
		{
			while (!myStack.empty() && myStack.top()->data == inorderVect[index]) 
			{
				currentNode = myStack.top();
				myStack.pop();
				index--;
			}
			if (index >= 0)
			{
				currentNode->left = new Tree(postorderVect[i]);
				myStack.push(currentNode->left);
			}
		}
	}
	return root;
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
	vector<string> postorderVector;

	for (int i = 0; i < numberOfNodes; i++)
	{
		cin >> data;
		postorderVector.push_back(data);
	}

	vector<string>  inorderVector;

	for (int i = 0; i < numberOfNodes; i++)
	{
		cin >> data;
		inorderVector.push_back(data);
	}

	//sets root so you can print afterwards.
	Tree *root = CreateTree(inorderVector, postorderVector);

	vector<vector<string> > myVect;

	int maxDepth = MaxTreeDepth(root);
	myVect.resize(maxDepth + 1);
	// puts tree in level order
	int level = 0;
	LevelOrderTree(root, myVect, level);
	// prints tree in level order
	for (int i = 0; i <= maxDepth; i++)
	{
		for (int j = 0; j < myVect[i].size(); j++)
			cout << myVect[i][j] << " ";
	}

	DeleteTree(root);

    return 0;
}

