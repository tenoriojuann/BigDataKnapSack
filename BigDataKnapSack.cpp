#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <Windows.h>
#include<stack>


struct Pair
{
	long int index = 0;
	long int weight = 0;
	long int value = 0;

};


const unsigned short MSB = 0x8000;


bool listenKeyPress(short p_key)
{
	//if p_key is pushed, the MSB will be set at 1
	if (GetAsyncKeyState(p_key) & MSB)
	{
		return true;
	}

	else return false;
}


int MAX(long int a, long int b) { return (a > b) ? a : b; }


int KnapSack(std::vector<Pair> &pair, std::vector<std::vector<long int>> &matrix, long int nItems, long int size) {


	long int i, j;

	for (i = 1; i <= nItems; i++) {
		for (j = 0; j <= size; j++) {
			if ((j - pair[i].weight)< 0)
				matrix[i][j] = matrix[i - 1][j];
			else
				matrix[i][j] = MAX(matrix[i - 1][j], matrix[i - 1][j - pair[i].weight] + pair[i].value);
		}
	}

	return matrix[nItems][size];

}


void saveToFile(long int item, long int size, std::vector<Pair> &pair, std::vector<std::vector<long int>> &matrix) {

	std::string filename = "output.txt";
	std::ofstream output(filename.c_str());
	long int j1, i;
	j1 = size;

	int Saved = 1;
	std::cout << "Saving to file...." << std::endl;
	for (i = item; i > 0; i--)
	{

		std::cout << pair[i].index;


		if (matrix[i][j1] != matrix[i - 1][j1] && (matrix[i][j1] == matrix[i - 1][j1 - pair[i].weight] + pair[i].value))
		{

			
			output << pair[i].index << " " << pair[i].weight << " " << pair[i].value << std::endl;
			std::cout << "\r" << std::floor(((((double)Saved) / (double)item) * 100)+0.5) << "% completed: ";

			std::cout << std::string(((((double)Saved ) / (double)item) * 100), '|');

			std::cout.flush();
			j1 = j1 - pair[i].weight;
			
		}
		Saved++;

	}
	std::cout << std::endl;
}



int main() {

	//if (!std::ifstream("data.txt")) {
	//	system("generator.exe 20003 100000");
	//}

	std::ifstream infile("data.txt", std::ios_base::in);


	long int items, capacity,n;
	

	long int counter = 0; // Counter for the Pair[]

	int READ = 0; // Variable used for the progress bar

	long int MAX_VALUE = 0; // Maximum value of all of the knapsack calculations

	infile >> n;   // total number of items in the txt file
	items = n;  
	infile >> capacity;	// capacity of the bag

	std::cout << "total size: " << n << " capacity: " << capacity << std::endl;
	std::cout << "items at a time " << items << std::endl;




	// Dynamic arrays to hold the Pair structs
	// This was better, since we can use heap memory
	// which holds more memory than stack
								
	std::vector<Pair> pair(items);
	std::vector<Pair> pair2(items);

	// 2D Vectors for the tables
	std::vector<std::vector<long int> > matrix(std::vector<std::vector<long int>>(items + 1, std::vector<long int>(capacity + 1, 0)));  	
	std::vector<std::vector<long int> > matrix2(std::vector<std::vector<long int>>(items + 1,  std::vector<long int>(capacity + 1, 0)));  	

	// temp value for Max_value
	long int tmp = 0;

	// pointer vector<vecotr<int>> to point to either table (m,m2)
	// we start with pointing it to the second table

	std::vector<std::vector<long int> > *tmpvector = &matrix2;



	long int index = 0;
	// Loop to have a progress bar
	while (READ < (n/items) && !listenKeyPress(VK_ESCAPE)) {




		// inputting the 5000 items into the weights and values array.
		// depending on which vector is the pointer pointing to.


		if (tmpvector == &matrix2) {


			while (counter < items) {  	


				infile >> pair[counter].weight >> pair[counter].value;
				pair[counter].index = index;
				counter++;
				index++;
				
			}

		}

		else {						
			while (counter < items) {
				infile >> pair2[counter].weight >> pair2[counter].value;
				pair[counter].index = index;
				counter++;
				index++;
			}
		}


		// FIrst time calculating the knapsack
		if (READ == 0) {
			MAX_VALUE = KnapSack(pair, matrix, items,capacity);
			tmpvector = &matrix;

		}

		else {

			if (tmpvector == &matrix) {
				tmp = KnapSack(pair2,matrix2,items, capacity);
				MAX_VALUE = MAX(MAX_VALUE, tmp);

				if (MAX_VALUE == tmp) {
					tmpvector = &matrix2;
				}

			}
			else if (tmpvector == &matrix2) {
				 tmp = KnapSack(pair,matrix,items, capacity);
				 MAX_VALUE = MAX(MAX_VALUE, tmp);

				 if (MAX_VALUE == tmp) {
					 tmpvector = &matrix;
				 }

			}

		}




		std::cout << "\r" << (double)((READ+1)/((double)n/items))*100<< "% completed: ";

		std::cout << std::string(((READ + 1) / ((double)n / items)) * 100, '|');

		std::cout.flush();


		counter = 0;  // we have to reset this to make use one fo the matrices again 

		READ++;
	}



	std::cout << "\nMaximum value that can be fitted : " << MAX_VALUE << std::endl;
	

	if (tmpvector == &matrix2) {
		
		
		saveToFile(items,capacity, pair2,matrix2);

	}
	else {
		
		saveToFile(items, capacity, pair,matrix);
	}

	// Clearing memory

	std::vector<std::vector<long int>>(0, std::vector<long int>()).swap(matrix);
	std::vector<std::vector<long int>>(0, std::vector<long int>()).swap(matrix2);
	std::vector<Pair>().swap(pair);
	std::vector<Pair>().swap(pair2);


	//Reading the output list and getting the sum

	std::cout << "\n\nDo you want to see the list of the weights and values used?(Y/N)" << std::endl;

	std::string answer;

	std::cin >> answer;

	if (answer == "Y" || answer == "y") {
		std::ifstream check("output.txt", std::ios_base::in);
		std::string name = "result.txt";
		std::ofstream result(name.c_str());
		std::stack<int> itemStack,weightStack,valueStack;
		int sum = 0;
		int item;
		int weights;
		int values;
		printf("\nPicks were: \n");
		printf("\nItem in picked matrix \t weight \t value\n");
		printf("\n-----------------------------------------------------------------------------\n");
		while (check.good()) {
			check >> item >> weights >> values;
			if (check.eof()) break;
			std::cout << item << " \t" << weights << " \t " << values << std::endl;
			itemStack.push(item);
			weightStack.push(weights);
			valueStack.push(values);
			sum += weights;
		}

		while (itemStack.size() > 0) {
			result << itemStack.top() << std::endl;
			itemStack.pop();

		}

		std::cout << "\n\n\nSum of the weights: " << sum << std::endl;
		std::cout << std::endl;
		std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
		std::cin.get();
	}

	else

		exit(0);

	return 0;
}
