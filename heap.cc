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

void HeapUp(vector<app_info> h, bst b) // heap up h, from binary search tree b
{
	if (b.left != NULL)
		HeapUp(h, *b.left);
	h.push_back(b.record);
	if (b.right != NULL)
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