#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// A utility function that returns maximum of two integers
int max(int a, int b) { return (a > b) ? a : b;}

// Returns the maximum value that can be put in a knapsack of capacity W


int main() {

	if (!ifstream("data.txt")) {
		system("generator.exe 50 893");
	}

	std::ifstream infile("data.txt");


	int items, capacity;
	int a, b;
	infile >> capacity;
	infile >> items;

	int s[51];

	vector<vector<int> > bag(items + 1, vector<int>(capacity + 1, 0));


	while (infile >> a >> b)
	{

		for (int i = 1; i <= items; i++) {
			for (int jw = 0; jw <= capacity; jw++) {

				// A case when the new item is more than the current weight limit
				if (a > jw)
					bag[i][jw] = bag[i - 1][jw];

				// A case for weight[i] < jw
				else {
					bag[i][jw] = max(bag[i - 1][jw], b + bag[i - 1][jw - a]);
					s[jw] =  i;
				}
			}
		}
	}
	cout << bag[items][capacity];


	std::cout << "Press Enter to Quit";



	return 0;
}