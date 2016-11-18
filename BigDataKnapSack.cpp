#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>



int MAX(int a, int b) { return (a > b) ? a : b; }

int knapsack(int W, int weight[], int value[], int n, std::vector<std::vector<int>> &m)
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

	if (!std::ifstream("data.txt")) {
		system("generator.exe 20000 100000");
	}

	std::ifstream infile("data.txt", std::ios_base::in);

	int n=0;

	int items, capacity;
	

	infile >> n;   // total number of items in the txt file
	items = 5000;  // we will contemplate 5,000 digits at a time
	infile >> capacity;	// capacity of the bag

	std::cout << "items: " << n << " capacity: " << capacity << std::endl;



	int counter = 0;

	int READ=0;

	int MAX_VALUE =0;

	// Dynamic arrays to hold the weights and values
	// This was better, since we can use heap memory
	// which holds more memory than stack

	int *weights1 = new int[items];
	int *weights2 = new int[items];
	int *values1 = new int[items];
	int *values2 = new int[items];


	std::vector<std::vector<int> > m(std::vector<std::vector<int>>(items + 1, *new std::vector<int>(capacity + 1, 0)));  	// m[n+1][W+1]

	std::vector<std::vector<int> > m2(std::vector<std::vector<int>>(items + 1, *new std::vector<int>(capacity + 1, 0)));  	// m[n+1][W+1]



	int tmp = 0;

	// pointer vector<vecotr<int>> to point to either table (m,m2)
	// we start with pointing it to the second table

	std::vector<std::vector<int> > *tmpvector = &m2;
	int *tmpweights = weights1;



	while (READ < (n/items)) {



		if (tmpvector == &m2) {


			while (counter < items) {  	 // inputting the 5000 items into the weights and values array.


				infile >> weights1[counter] >> values1[counter];
				counter++;
			}

		}

		else {
			while (counter < items) {
				infile >> weights2[counter] >> values2[counter];
				counter++;
			}
		}


		if (READ == 0) {
			MAX_VALUE = knapsack(capacity, weights1, values1, items, m);
			tmpvector = &m;

		}

		if (READ > 0) {

			if (tmpvector == &m) {
				tmp = knapsack(capacity, weights2, values2, items, m2);
				MAX_VALUE = MAX(MAX_VALUE, tmp);

				if (MAX_VALUE == tmp) {
					tmpvector = &m2;
				}

			}
			else if (tmpvector == &m2) {
				 tmp = knapsack(capacity, weights1, values1, items, m);
				 MAX_VALUE = MAX(MAX_VALUE, tmp);

				 if (MAX_VALUE == tmp) {
					 tmpvector = &m;
				 }

			}

		}

		counter = 0;
		READ++;
	}


	int i = items;
	int W = capacity;
	int num = 0;

	std::cout << "MAX Value: " << MAX_VALUE<< std::endl;


	// Printing the weights

		std::cout << "Weights: " << std::endl;
		while (W > 0) {
			if (tmpvector == &m) {
				if (m[i][W] != m[i - 1][W]) {
					std::cout << weights1[i - 1] << " " << std::endl;
					i--;
					W = W - weights1[i];
					num++;

				}
				else {
					i--;
				}
			}


			else {

				if (m2[i][W] != m2[i - 1][W]) {
					std::cout << weights2[i - 1] << " " << std::endl;
					i--;
					W = W - weights2[i];
					num++;

				}
				else {
					i--;
				}
			}
	}





	std::cout << "Number of items used: " << num;

	int exit;
	std::cin >> exit;



	return 0;
}