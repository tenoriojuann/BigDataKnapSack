#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>



int MAX(int a, int b) { return (a > b) ? a : b; }

int knapsack(int weights[], int values[], std::vector<std::vector<int>> &matrix, std::vector<std::vector<int>> &picks, int nItems, int size) {
	int i, j;

	for (i = 1; i <= nItems; i++) {
		for (j = 0; j <= size; j++) {
			if (weights[i - 1] <= j) {
				matrix[i][j] = MAX(matrix[i - 1][j], values[i - 1] + matrix[i - 1][j - weights[i - 1]]);
				if (values[i - 1] + matrix[i - 1][j - weights[i - 1]]>matrix[i - 1][j])
					picks[i][j] = 1;
				else
					picks[i][j] = -1;
			}
			else {
				picks[i][j] = -1;
				matrix[i][j] = matrix[i - 1][j];
			}
		}
	}

	return matrix[nItems][size];

}

void printPicks(int item, int size, int *weights, std::vector<std::vector<int>> &picks) {

	std::string filename = "output.txt";
	std::ofstream output(filename.c_str());

	while (item>0) {
		if (picks[item][size] == 1) {
			output << item - 1 << std::endl;
			item--;
			size -= weights[item];
		}
		else {
			item--;
		}
	}

	return;
}


int main() {

	if (!std::ifstream("data.txt")) {
		system("generator.exe 20003 100000");
	}

	std::ifstream infile("data.txt", std::ios_base::in);

	int n=0;

	int items, capacity;
	

	infile >> n;   // total number of items in the txt file
	items = 5000;  // we will contemplate 5,000 digits at a time
	infile >> capacity;	// capacity of the bag

	std::cout << "total size: " << n << " capacity: " << capacity << std::endl;
	std::cout << "items at a time " << items << std::endl;



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


	std::vector<std::vector<int> > m(std::vector<std::vector<int>>(items + 1,  std::vector<int>(capacity + 1, 0)));  	// m[n+1][W+1]
	std::vector<std::vector<int> > picks(std::vector<std::vector<int>>(items + 1,  std::vector<int>(capacity + 1, 0)));// m[n+1][W+1]
	std::vector<std::vector<int> > picks2(std::vector<std::vector<int>>(items + 1, std::vector<int>(capacity + 1, 0)));
	std::vector<std::vector<int> > m2(std::vector<std::vector<int>>(items + 1,  std::vector<int>(capacity + 1, 0)));  	// m[n+1][W+1]



	// temp value for Max_value
	int tmp = 0;

	// pointer vector<vecotr<int>> to point to either table (m,m2)
	// we start with pointing it to the second table

	std::vector<std::vector<int> > *tmpvector = &m2;




	while (READ < (n/items)) {



		// inputting the 5000 items into the weights and values array.
		// depending on which vector is the pointer pointing to.


		if (tmpvector == &m2) {


			while (counter < items) {  	


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


		// FIrst time calculating the knapsack
		if (READ == 0) {
			MAX_VALUE = knapsack(weights1, values1, m,picks, items,capacity);
			tmpvector = &m;

		}

		else {

			if (tmpvector == &m) {
				tmp = knapsack(weights2, values2, m2,picks2,items, capacity);
				MAX_VALUE = MAX(MAX_VALUE, tmp);

				if (MAX_VALUE == tmp) {
					tmpvector = &m2;
				}

			}
			else if (tmpvector == &m2) {
				 tmp = knapsack(weights1, values1,m2 ,picks2,items, capacity);
				 MAX_VALUE = MAX(MAX_VALUE, tmp);

				 if (MAX_VALUE == tmp) {
					 tmpvector = &m;
				 }

			}

		}




		std::cout << "\r" << (double)((READ+1)/((double)n/items))*100 << "% completed: ";

		std::cout << std::string(((READ + 1) / ((double)n / items)) * 100, '|');

		std::cout.flush();


		counter = 0;  // we have to reset this to start the count again
		               //  Also because it is being used for indeces 

		READ++;
	}



	std::cout << "\nMaximum value that can be fitted :: " << MAX_VALUE << std::endl;
	printf("Picks were: \n");

	if (tmpvector == &m2) {
		
		
		printPicks(items, capacity, weights2, picks2);

	}
	else {
		
		printPicks(items, capacity, weights1, picks);
	}

	// Clearing memory
	delete[] weights1, values1;
	delete[] weights2, values2;
	std::vector<std::vector<int>>(0, std::vector<int>()).swap(m);
	std::vector<std::vector<int>>(0, std::vector<int>()).swap(m2);
	std::vector<std::vector<int>>(0, std::vector<int>()).swap(picks);
	std::vector<std::vector<int>>(0, std::vector<int>()).swap(picks2);

	//Reading the output list and getting the sum

	std::cout << "Do you want to see the list of the weights used?" << std::endl;

	std::string answer;

	std::cin >> answer;

	if (answer == "Y" || answer == "y") {
		std::ifstream check("output.txt", std::ios_base::in);
		int sum = 0;
		int s = 0;
		while (check) {
			check >> s;
			std::cout << s << std::endl;
			sum += s;
		}

		std::cout << "\n\n\n SUM: " << sum << std::endl;
		std::cout << std::endl;
	}


	std::string exit;
	std::cin >> exit;



	return 0;
}
