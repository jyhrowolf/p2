#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "defn.h"
using namespace std;

void BinarySearchTreeCreate(bst a, bst b)
{
	if (b.record.app_name.compare(a.record.app_name) < 0)
	{
		if (b.left != NULL)
			BinarySearchTreeCreate(a, *b.left);
		else
			*b.left = a;
	}
	else
		if (b.right != NULL)
			BinarySearchTreeCreate(a, *b.right);
		else
			*b.right = a;
}

int BinarySearchTreeSize(bst b)
{
	int sum = 1;
	if (b.left != NULL)
		sum += BinarySearchTreeSize(*b.left);
	if (b.right != NULL)
		sum += BinarySearchTreeSize(*b.right);
	return sum;
}

void HeapUp(vector<app_info> h, bst b)
{
	if(b.left != NULL)
		HeapUp(h, *b.left);
	h.push_back(b.record);
	if(b.right != NULL)
		HeapUp(h, *b.right);
}

void Heapify(vector<app_info> h, int c, int i)
{
	int max = i; 
	int l = 2 * i + 1; 
	int r = 2 * i + 2; 

	if (l < c && h[l].price > h[max].price)
		max = l;
	if (r < c && h[r].price > h[max].price)
		max = r;
	if (max != i) {
		app_info temp = h[i];
		h[i] = h[max];
		h[max] = temp;
		Heapify(h, c, max);
	}
}

void BuildMaxHeap(vector<app_info> h, int c)
{
	int start = (c / 2) - 1;
	for (int i = start; i >= 0; i--) {
		Heapify(h, start, i);
	}
}

void PrintMax(bst b, float max)
{
	if (b.left != NULL)
		PrintMax(*b.left, max);
	if (b.record.price == max)
		cout << "\t" << b.record.app_name;
	if (b.right != NULL)
		PrintMax(*b.right, max);
}

void PrintBST(bst b)
{
	if (b.left != NULL)
		PrintBST(*b.left);
		cout << "\t" << b.record.app_name;
	if (b.right != NULL)
		PrintBST(*b.right);
}

int main() {
	int numberOfCategories;
	scanf_s("%d", &numberOfCategories);
	vector<categories> myCategories;
	for(int i = 0; i < numberOfCategories; i++)
	{
		categories newCategory;
		std::string name;
		getline(cin, name);
		newCategory.category = name;
		app_info *a = new app_info;
		bst *bin = new bst;
		bin->record = *a;
		newCategory.root = bin;
		myCategories.push_back(newCategory);
	}

	int numberOfApps;
	scanf_s("%d", &numberOfApps);
	for (int i = 0; i < numberOfApps; i++)
	{ 
		std::string category;
		getline(cin, category);
		int index = 0;
		for (int i = 0; i < numberOfCategories; i++)
		{
			if (myCategories[i].category == category)
				index = i;
		}
		bst bin = *myCategories[index].root;
		app_info a;
		if (myCategories[index].root->left == NULL && myCategories[index].root->right == NULL)
			app_info a = bin.record;
		else
			app_info *a = new app_info;
		a.category = category;

		std::string name;
		getline(cin, name);
		a.app_name = name;

		std::string version;
		getline(cin, version);
		a.version = version;

		float size;
		scanf_s("%f", &size);
		a.size = size;

		std::string units;
		getline(cin, units);
		a.units = units;

		float price;
		scanf_s("%f", &price);
		a.size = price;

		if (!(myCategories[index].root->left == NULL && myCategories[index].root->right == NULL))
		{
			bst* newBin = new bst;
			newBin->record = a;
			BinarySearchTreeCreate(*newBin, bin);
		}
	}
	int numberOfQueries;
	scanf_s("%d", &numberOfQueries);
	for (int i = 0; i < numberOfQueries;i++)
	{
		std::string input;
		getline(cin, input);

		std::vector<std::string> result;
		std::istringstream iss(input);
		for (std::string s; iss >> s; )
			result.push_back(s);
		if (result[0] == "find")
		{
			int index = -1;
			for (int i = 0; i < numberOfCategories; i++)
				if (myCategories[i].category == result[4])
					index = i;
			if (index == -1)
				cout << "Category " << result[4] << "not found";
			else
				if (myCategories[index].root->record.size != NULL)
				{
					int count = BinarySearchTreeSize(*myCategories[index].root);
					vector<app_info> heap;
					HeapUp(heap, *myCategories[index].root);
					BuildMaxHeap(heap, count);
					int maximum = heap[0].price;
					PrintMax(*myCategories[index].root, maximum);
					heap.clear();
					heap.shrink_to_fit();
				}
				else
					cout << "Category " << result[4] << "no apps found";
		}
		else if (result[0] == "print-apps")
		{
			int index = -1;
			for (int i = 0; i < numberOfCategories; i++)
				if (myCategories[i].category == result[2])
					index = i;
			if (index == -1)
				cout << "Category " << result[2] << "not found";
			else
				if (myCategories[index].root->record.size != NULL)
					PrintBST(*myCategories[index].root);
		}
	}

	return 0;
}