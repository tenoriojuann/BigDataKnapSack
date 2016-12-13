/*

	extra credit project output evaluator, ver 1.0

	usuage a.exe (or a.out) 50000
	
	5000 is the maximum weight allowed
	
	output data.txt
*/


#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main (int argc, char* argv [])
{
	int nItems;
	int nMaxTotalWeight;
		
	FILE* pInFile = fopen ("data.txt", "r+");	
	FILE* pResultFile = fopen ("result.txt", "r+");	
	
	fscanf (pInFile, "%d\n", &nItems);	
	fscanf (pInFile, "%d\n", &nMaxTotalWeight);	
	
	int i = 0;
	
	int nNextItemNo = 0;
	int nNextItemProfit = 0;
	int nNextItemWeight = 0;
	
	int nTotalProfit = 0;
	int nTotalWeight = 0;
	
	fscanf (pResultFile, "%d\n", &nNextItemNo);		
	
	for (i = 0; i < nItems && pResultFile != NULL; i++) {
		fscanf (pInFile, "%d\n", &nNextItemWeight);	
		fscanf (pInFile, "%d\n", &nNextItemProfit);	
			
		if (i == nNextItemNo) {
			printf ("%d (%d, %d) is considered\n", i, nNextItemWeight, nNextItemProfit);
			nTotalProfit += nNextItemProfit;
			nTotalWeight += nNextItemWeight;
			fscanf (pResultFile, "%d\n", &nNextItemNo);
		}		
	}
	
	fclose (pInFile);	
	fclose (pResultFile);	
	
	printf ("Total Profit Achieved: %d\n", nTotalProfit);
	printf ("Total Weight out of MaxWeight Allowed: %d / %d\n", nTotalWeight, nMaxTotalWeight);
	
	if (nTotalWeight <= nMaxTotalWeight) {
		printf ("Feasible Solution\n");
	} else {
		printf ("Not Feasible Solution\n");
	}

	std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
	std::cin.get();
		
	return 0;
}