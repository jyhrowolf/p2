#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include "defn.h"

using namespace std;

void BinarySearchTreeCreate(bst a, bst b) // create binary search tree by adding bst a to bst b
{
	if (b.record.app_name.compare(a.record.app_name) < 0)
		if (b.left != NULL)
			BinarySearchTreeCreate(a, *b.left);
		else
			*b.left = a;
	else
		if (b.right != NULL)
			BinarySearchTreeCreate(a, *b.right);
		else
			*b.right = a;
}

int BinarySearchTreeSize(bst b) // add up every individual leaf to get total size of binary search tree.
{
	int sum = 1;
	if (b.left != NULL)
		sum += BinarySearchTreeSize(*b.left);
	if (b.right != NULL)
		sum += BinarySearchTreeSize(*b.right);
	return sum;
}

int BinarySearchTreeDepth(bst b) // get every layer to see the max depth of binary search tree
{
	int left = 0;
	if (b.left != NULL)
		left = BinarySearchTreeDepth(*b.left);
	int right = 0;
	if (b.right != NULL)
		right = BinarySearchTreeDepth(*b.right);

	return std::max(left + 1, right + 1);
}

bst BinarySearchTreeSearch(bst b, std::string name) // search through binary search tree b for name
{
	if (b.record.app_name == name)
		return b;
	if (b.record.app_name.compare(name) < 0)
	{
		if (b.left != NULL)
			return BinarySearchTreeSearch(b.left, name)
	}
	else
		if (b.right != NULL)
			return BinarySearchTreeSearch(b.right, name);
	return NULL;
}

void DeleteNode(bst root, std::string name) // delete the node with the same name as name from root tree
{
	if (root.record.app_name.compare(name) < 0)
		if (root.left != NULL)
			if (root.left->record.app_name == name)
			{
				if (root.left->left == NULL && root.left->right == NULL)
					root.left = NULL;
				else if (root.left->left == NULL && root.left->right != NULL)
					root.left = root.left->right;
				else if (root.left->left != NULL && root.left->right == NULL)
					root.left = root.left->left;
				else if (root.left->left != NULL && root.left->right != NULL)
				{
					BinarySearchTreeCreate(root.left->right, root.left->left);
					root.left = root.left->left;
				}
			}
			else
				DeleteNode(*root.left, name);
		else
			if (root.right != NULL)
				if (root.right->record.app_name == name)
				{
					if (root.right->left == NULL && root.right->right == NULL)
						root.right = NULL;
					else if (root.right->left == NULL && root.right->right != NULL)
						root.right = root.right->right;
					else if (root.right->left != NULL && root.right->right == NULL)
						root.right = root.right->left;
					else if (root.right->left != NULL && root.right->right != NULL)
					{
						BinarySearchTreeCreate(root.right->right, root.right->left);
						root.right = root.right->left;
					}
				}
				else
					DeleteNode(*root.right, name);
}

void PrintMax(bst b, float max) // print every binary node that has value max
{
	if (b.left != NULL)
		PrintMax(*b.left, max);
	if (b.record.price == max)
		cout << "\t\"" << b.record.app_name << "\"";
	if (b.right != NULL)
		PrintMax(*b.right, max);
}

void PrintBST(bst b) // print entire bianry search tree inorder
{
	if (b.left != NULL)
		PrintBST(*b.left);
	cout << "\t\"" << b.record.app_name << "\"";
	if (b.right != NULL)
		PrintBST(*b.right);
}

void PrintBSTFree(bst b) // print binary search tree only if the price is 0
{
	if (b.left != NULL)
		PrintBSTFree(*b.left);
	if (b.record.price == 0)
		cout << "\t\"" << b.record.app_name << "\"";
	if (b.right != NULL)
		PrintBSTFree(*b.right);
}

bool PrintRange(bst b, float low, float high) // print binary search tree nodes price within the range of low and high
{
	bool happened = false;
	if (b.left != NULL)
		if (PrintRange(*b.left, low, high))
			happened = true;
	if (b.record.price <= high && b.record.price >= low)
	{
		cout << "\t\"" << b.record.app_name << "\"";
		happened = true;
	}
	if (b.right != NULL)
		if (PrintRange(*b.right, low, high))
			happened = true;
	return happened;
}

bool PrintRangeApp(bst b, std::string low, std::string high) // print binary search tree nodes names within the range of low and high
{
	bool happened = false;
	if (b.left != NULL)
		if (PrintRange(*b.left, low, high))
			happened = true;
	if (b.record.app_name.compare(high) <= 0 && b.record.app_name.compare(low) >= 0)
	{
		cout << "\t\"" << b.record.app_name << "\"";
		happened = true;
	}
	if (b.right != NULL)
		if (PrintRange(*b.right, low, high))
			happened = true;
	return happened;
}