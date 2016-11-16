#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;


int MAX(int a, int b) { return (a > b) ? a : b; }

int knapsack(int W, int weight[], int value[], int n, vector<vector<int>> &m)
{

	/* m[i][w] to be the maximum value that can be attained
	with weight less than or equal to w using items up to i*/


	for (int jw = 0; jw <= W; jw++) m[0][jw] = 0;

	for (int i = 1; i <= n; i++) {
		for (int jw = 1; jw <= W; jw++) {

			// A case when the new item is more than the current weight limit
			if (weight[i - 1] > jw)
				m[i][jw] = m[i - 1][jw];

			// A case for weight[i] < jw
			else {
				m[i][jw] = MAX(m[i - 1][jw], value[i - 1] + m[i - 1][jw - weight[i - 1]]);
			}
		}
	}
	return m[n][W];
}
int main() {

	if (!ifstream("data.txt")) {
		system("generator.exe 50 155");
	}

	std::ifstream infile("data.txt", std::ios_base::in);



	int items, capacity;
	

	infile >> items;
	infile >> capacity;

	cout << "items: " << items << " capacity: " << capacity << endl;


	int *weights = new int[items];
	int *values = new int[items];


	int counter = 0;
	while (infile >>weights[counter]>>values[counter])	{
		counter++;
	}

	vector<vector<int> > m(items + 1, vector<int>(capacity + 1, 0));  	// m[n+1][W+1]


	cout << "Max value: " << (knapsack( capacity, weights, values, items, m)) << endl;



	int i = items;
	int W = capacity;
	while (W>0 && i>1) {
		if (m[i][W] != m[i - 1][W]) {
			cout << "Weights: " <<  weights[i-1] << " " << endl;
			i--;
			W = W - weights[i];

			
		}
		else {
			i--;
		}
	}


	int exit;
	std::cin >> exit;



	return 0;
}