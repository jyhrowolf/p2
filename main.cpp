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

	return std::max(left+1,right+1);
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

void HeapUp(vector<app_info> h, bst b) // heap up h, from binary search tree b
{
	if(b.left != NULL)
		HeapUp(h, *b.left);
	h.push_back(b.record);
	if(b.right != NULL)
		HeapUp(h, *b.right);
}

void Heapify(vector<app_info> h, int c, int i) // heapify h
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

void BuildMaxHeap(vector<app_info> h, int c) // create a max heap from h
{
	int start = (c / 2) - 1;
	for (int i = start; i >= 0; i--) {
		Heapify(h, start, i);
	}
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
	if(b.record.price == 0)
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

bool TestForPrime(int val) // find if val is prime
{
	int limit, factor = 2;

	limit = (long)(sqrtf((float)val) + 0.5f);
	while ((factor <= limit) && (val % factor))
		factor++;

	return(factor > limit);
}

int main() {
	int numberOfCategories; // create categories and fill them in.
	scanf_s("%d", &numberOfCategories);
	vector<categories> myCategories;
	for (int i = 0; i < numberOfCategories; i++)
	{
		categories newCategory;
		std::string name;
		getline(cin, name);
		newCategory.category = name;
		app_info* a = new app_info;
		bst* bin = new bst;
		bin->record = *a;
		newCategory.root = bin;
		myCategories.push_back(newCategory);
	}

	int numberOfApps; // take in number of apps and fill in the bst's of categories
	scanf_s("%d", &numberOfApps);
	float k = 2 * numberofApps;
	while (!TestForPrime(k))// create hash table
		k++;
	hash_table_entry** hash_table;
	hash_table = (struct hash_table_entry**) malloc(k * sizeof(struct hash_table_entry*));
	for (i = 0; i < k; i++)
		hash_table[i] = NULL;

	for (int i = 0; i < numberOfApps; i++) // initialize everything for the apps
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
			app_info* a = new app_info;
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

			int sum = 0; // create hash table/fill hastable
			char str[50] = a.app_name;
			for (int s = 0; str[s] != '\0'; s++)
				sum = sum + str[s];
			if (hash_table[sum % k] != NULL)
			{
				hash_table_entry h = new hash_table_entry;
				h.app_name = a.app_name;
				h.app_node = newBin;
				h.next = hash_table[sum % k];
				hash_table[sum % k] = h;
			}
			else
			{
				hash_table_entry h = new hash_table_entry;
				h.app_name = a.app_name;
				h.app_node = newBin;
				h.next = NULL;
				hash_table[sum % k] = h;
			}
		}
	}

	int numberOfQueries; // take queries
	scanf_s("%d", &numberOfQueries);
	for (int i = 0; i < numberOfQueries;i++)
	{
		std::string input;
		getline(cin, input);

		std::vector<std::string> result;
		std::istringstream iss(input);
		for (std::string s; iss >> s; )
			result.push_back(s);

		if (result[0] == "delete") // delete
		{
			int sum = 0; // search for hash
			char str[50] = a.app_name;
			for (int s = 0; str[s] != '\0'; s++)
				sum = sum + str[s];
			hash_table_entry h = hash_table[sum % k];
			if (h.app_name == result[2])
				hash_table[sum % k] = h.next;
			else
				while (h.next != NULL)
				{
					if (h.next.app_name == result[2])
						h.next = h.next->next;
					h = h.next;
				}
			if (h.app_name != result[2])
				cout << "Application \"" << result[2] << "\" not found in category " << result[1] << "; unable to delete.";
			int index = -1;
			for (int j = 0; j < numberOfCategories; j++)
				if (myCategories[j].category == result[1])
					index = j;
			DeleteNode(myCategories[index].root, result[2]);
			cout << "Application \"" << result[2] << "\" from Category " << result[1] << " succesfully deleted.";
		}
		else if (result[0] == "find")
		{
			if (result[1] == "max")// find max price apps
			{
				int index = -1;
				for (int j = 0; j < numberOfCategories; j++)
					if (myCategories[j].category == result[4])
						index = j;
				if (index == -1)
					cout << "Category " << result[4] << " not found";
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
						cout << "Category " << result[4] << " no apps found";
			}
			else if (result[1] == "app") // find app
			{
				int sum = 0; // search for hash
				char str[50] = a.app_name;
				for (int s = 0; str[s] != '\0'; s++)
					sum = sum + str[s];
				hash_table_entry h = hash_table[sum % k];
				while (h.next != NULL && h.app_name != result[2])
					h = h.next;
				if (h.app_name != result[2])
					cout << "Application \"" << result[2] << "\" not found";
				else
				{
					app_info a = h.app_node.record;
					cout << "\tCategory: " << a.category;
					cout << "\tApp_name: " << a.app_name;
					cout << "\tVersion: " << a.version;
					cout << "\tSize: " << a.size;
					cout << "\tUnits: " << a.units;
					cout << "\tPrice: " << a.price;
				}
			}
			else if (result[1] = "price") // find price free
			{
				int index = -1;
				for (int j = 0; j < numberOfCategories; j++)
					if (myCategories[j].category == result[3])
						index = j;
				if (index == -1)
					cout << "Category " << result[3] << " not found";
				else
					if (myCategories[index].root->record.size != NULL)
					{
						cout << "Free apps in Category : " << result[3];
						PrintBSTFree(myCategories[index].root);
					}
					else
						cout << "Category " << result[3] << " no apps found";
			}
		}
		else if (result[0] == "range") //  range
		{
			if (result[2] == "price") // range price
			{
				int index = -1;
				for (int j = 0; j < numberOfCategories; j++)
					if (myCategories[j].category == result[1])
						index = j;
				if (index == -1)
					cout << "Category " << result[1] << " not found";
				else
					if (myCategories[index].root->record.size != NULL)
					{
						cout << "Applications in Price Range(" << result[3] << ", " << result[4] << "). in Category : " << result[1] << ".";
						if (!PrintRange(myCategories[index].root, std::stof(result[3]), std::stof(result[4])))
							cout << "No applications found in " << result[1] << "for the given price range(" << result[3] << ", " << result[4] << ").";
					}
					else
						cout << "Category " << result[1] << " no apps found";
			}
			else if (result[2] == "app") // range app
			{
				int index = -1;
				for (int j = 0; j < numberOfCategories; j++)
					if (myCategories[j].category == result[1])
						index = j;
				if (index == -1)
					cout << "Category " << result[1] << " not found";
				else
					if (myCategories[index].root->record.size != NULL)
					{
						cout << "Applications in Range(" << result[3] << ", " << result[4] << "). in Category : " << result[1] << ".";
						if (!PrintRangeApp(myCategories[index].root, result[3], result[4]))
							cout << "No applications found in " << result[1] << "for the given range(" << result[3] << ", " << result[4] << ").";
					}
					else
						cout << "Category " << result[1] << " no apps found";
			}
		}
		else if (result[0] == "print-apps") // print apps
		{
			int index = -1;
			for (int j = 0; j < numberOfCategories; j++)
				if (myCategories[j].category == result[2])
					index = j;
			if (index == -1)
				cout << "Category " << result[2] << " not found";
			else
				if (myCategories[index].root->record.size != NULL)
					PrintBST(*myCategories[index].root);
		}
		else if (result[0] == "report")
		{
			for (int c = 0; c < numberOfCategories; c++) // report binary tree
			{
				cout << myCategories[c].category;
				cout << BinarySearchTreeSize(myCategories[c].root);
				cout << BinarySearchTreeDepth(myCategories[c].root);
				if(myCategories[c].root->left == NULL)
					cout << "0"
				else
					cout << BinarySearchTreeDepth(myCategories[c].root.left);
				if (myCategories[c].root->right == NULL)
					cout << "0"
				else
					cout << BinarySearchTreeDepth(myCategories[c].root.right);
			}

			float total = 0f; // report hash
			for (int h = 0; h < k; h++)
			{
				hash_table_entry he = hash_table[h];
				int length = 0;
				while (he.next != NULL)
				{
					length++;
					total++;
					he = he.next;
				}
				cout << length;
			}
			cout << "Load factor: " << total / k;
			cout << "Number of entries (n): " << total;
			cout << "Number of buckets (m): " << k;

			std::string name = myCategories[0].root->record.app_name;
			auto start = high_resolution_clock::now();// report time
			int sum = 0; // search for hash
			char str[50] = name;
			for (int s = 0; str[s] != '\0'; s++)
				sum = sum + str[s];
			hash_table_entry h = hash_table[sum % k];
			while (h.next != NULL && h.app_name != name)
				h = h.next;
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "Time taken by Hash: " << duration.count() << " microseconds";

			start = high_resolution_clock::now();// report time
			for (int j = 0; j < numberOfCategories; j++)
				if (myCategories[j].category == h.app_node->record.category)
					index = j;
			BinarySearchTreeSearch(myCategories[index].root, h.app_name);
			stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "Time taken by Binary: " << duration.count() << " microseconds";
		}
		else if (result[0] == "no")
		{
			//no statistics
		}
	
	}
	free(hash_table);
	free(myCategories);
	return 0;
}