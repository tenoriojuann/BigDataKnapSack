#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

// A utility function that returns maximum of two integers
int max(int a, int b) { return (a > b) ? a : b;}

int knapsack(int items, int capacity, int s[], int weight[], int value[]) {


	vector<vector<int> > m(items + 1, vector<int>(capacity + 1, 0));
	for (int jw = 0; jw <= capacity; jw++) m[0][jw] = 0;

	for (int i = 1; i <= items; i++) {
		for (int jw = 0; jw <= capacity; jw++) {

			// A case when the new item is more than the current weight limit
			if (weight[i - 1] > jw)
				m[i][jw] = m[i - 1][jw];

			// A case for weight[i] < jw
			else {
				m[i][jw] = max(m[i - 1][jw], value[i - 1] + m[i - 1][jw - weight[i - 1]]);
				s[jw] = i;
			}
		}
	}


	return m[items][capacity];
}

// Returns the maximum value that can be put in a knapsack of capacity W


int main() {

	if (!ifstream("data.txt")) {
		system("generator.exe 50 50");
	}

	std::ifstream infile("data.txt");


	int items, capacity;
	int a[10];
	int b[10];
	infile >> capacity;
	infile >> items;

	int *s = new int[capacity+1];

	vector<vector<int> > MaxValues(50, vector<int>(50,0));


	int counter = 0;
	int n = 1;
	int k = capacity;
	int position = 0;

	while (infile >> a[counter] && infile >> b[counter])	 // make sure it imports   the numbers into the program
	{
		



		if (counter == 9) {
			counter = 0;													  
			MaxValues[0][position] = ( knapsack(10, capacity, s, a, b) );
			k = capacity;
			n = 1;
			while (k) {
				cout << a[s[k] - 1] << " ";
				k = k - a[s[k] - 1];
			}

			
		}

		position++;
		counter++;
		
	}

	std::cout << "Press Enter to Quit";



	return 0;
}