/*
Name: Caleb Keller
Class: CS317-02
Program Name: Project 1
Due Date: 03/02/2022
Project Description: Performs quicksort and mergesort on an array of size given as first integer value in input file, outputs number of comparisons for each algorithm as well
*/

#include <iostream>
#include <fstream>


using namespace std;

void QuickSort(double array[], int left, int right);
void MergeSort(double array[], int p, int r);
void Merge(double array[], int p, int q, int r);
bool LESS(double a, double b);
int Partition(double array[], int left, int right);
int comparisons;

int main()
{
	ifstream infile; // input file
	ofstream outfile; // output file
	int count = 0; // comparison counter

	int size; // first integer given in file that determines size of array to be read
	double nums; // numbers from file
	
	infile.open("input.txt");

	infile >> size; // getting first number from file that represents what array size needs to be

	double* array = new double[size]; // dynamically allocating array to be able to use given size of array from file

	while (infile.good())
	{
		if (infile.fail()) // if input file doesnt open, clear file buffer and close file safely
		{
			infile.clear();
			infile.close();
		}
		else
		{
			infile >> nums; // priming read to get first number from file
			for (int i = 0; i < size; i++)
			{
				infile.ignore(INT_MAX, '\n');
				array[i] = nums; // puts number into array
				infile >> nums; // gets next number and iterates
			}
		}
	}
	
	// begin quicksort and output quicksorted array
	outfile.open("caleb_quick.txt");
	QuickSort(array, 0, size - 1);
	for (int i = 0; i < size; i++)
	{
		outfile << array[i] << endl;
	}
	outfile << endl << "Comparisons performed: " << comparisons << endl;
	outfile.close(); // close file

	// begin mergesort and output mergesorted array
	outfile.open("caleb_merge.txt");
	MergeSort(array, 0, size - 1);
	for (int j = 0; j < size; j++)
	{
		outfile << array[j] << endl;
	}
	outfile << endl << "Comparisons performed: " << comparisons << endl;
	infile.close();
	outfile.close(); // close file
}

int Partition(double array[], int left, int right)
{
	int i = left + 1;
	int j = right;
	while (i <= j)
	{
		if (array[i] <= array[left])
		{
			i++;
			bool comp = LESS(array[i], array[left]);
		}
		else if (array[j] >= array[left])
		{
			j--;
			bool comp = LESS(array[j], array[left]);
		}
		else
		{
			swap(array[i], array[j]);
			i++;
			j--;

		}
	}
	swap(array[left], array[j]);
	return j;
}

void QuickSort(double array[], int left, int right)
{
	double pivot;
	if (left < right)
	{
		pivot = Partition(array, left, right);
		QuickSort(array, left, pivot - 1);
		QuickSort(array, pivot + 1, right);
	}
	return;
}

void Merge(double array[], int L, int M, int R)
{
	int left = (M - L) + 1; // right side
	int right = R - M; // left side
	int i, j, k; // loop values

	double* arr1 = new double[right];
	double* arr2 = new double[left];

	for (i = 0; i < left; i++)
	{
		arr1[i] = array[L + i];
	}
	for (j = 0; j < right; j++)
	{
		arr2[j] = array[M + j + 1];
	}

	i = 0; // initialize to reuse
	j = 0;
	k = L;

	while (i < left && j < right)
	{
		if (arr1[i] <= arr2[j])
		{
			array[k] = arr1[i];
			i++;
			bool comp = LESS(arr1[i], arr2[j]);

		}
		else
		{
			array[k] = arr2[j];
			j++;
		}
		k++;
	}
	while (i < left)
	{
		array[k] = arr1[i];
		i++;
		k++;
	}
	while (j < right)
	{
		array[k] = arr2[j];
		j++;
		k++;
	}
}

void MergeSort(double array[], int L, int R /* size */ )
{
	if (L < R)
	{
		int m = (L + R) / 2;
		MergeSort(array, L, m);
		MergeSort(array, m + 1, R);
		Merge(array, L, m, R);
	}
}


bool LESS(double a, double b)
{
	if (a < b)
	{
		comparisons++;
		return true;

	}
	else
	{
		return false;
	}

}
