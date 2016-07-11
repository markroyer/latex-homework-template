/**
 * @file sort.cpp
 *
 * This file contains a number of sorting routines from the textbook.  They
 * have been modified to sort on string vectors.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

// ****************************************************************************
// Start helper functions
// ****************************************************************************

/**
 * Displays the content of the list to standard output.
 *
 * @param list
 */
void displayList(const vector<string>& list) {
	cout << "[ ";
	for (unsigned i = 0; i < list.size(); ++i) {
		cout << list[i] << (i == list.size() - 1 ? " ]" : ", ");
	}
	cout << endl;
}

/**
 * Convert n to a string.
 *
 * @param n Some integer
 * @return String representation of the given integer.
 */
string toStr(int n) {
	stringstream ss;
	ss << n;
	return ss.str();
}

// ****************************************************************************
// End helper functions
// ****************************************************************************

/**
 * Sort the given list using the selection sort algorithm.
 *
 * @param list Comparable strings
 */
void selectionSort(vector<string>& list) {

	for (unsigned i = 0; i < list.size(); i++) {

		unsigned curMin = i;

		for (unsigned j = i + 1; j < list.size(); j++) {
			if (list[j] < list[curMin])
				curMin = j;
		}

		if (i != curMin) {
			string tmp = list[i];
			list[i] = list[curMin];
			list[curMin] = tmp;
		}
	}
}

/**
 * Sort the given list using the bubble sort algorithm.
 *
 * @param list Comparable strings
 */
void bubbleSort(vector<string>& list) {
	bool needNextPass = true;
	for (unsigned k = 1; k < list.size() && needNextPass; k++) {
		// Array may be sorted and next pass not needed
		needNextPass = false;
		for (unsigned i = 0; i < list.size() - k; i++) {
			if (list[i] > list[i + 1]) {
				// Swap list[i] with list[i + 1]
				string temp = list[i];
				list[i] = list[i + 1];
				list[i + 1] = temp;
				needNextPass = true; // Next pass still needed
			}
		}
	}
}

/**
 * Sort the given list using the insertion sort algorithm.
 *
 * @param list Comparable strings
 */
long insertionSort(vector<string>& list) {

	long result = 0;
	for (unsigned i = 1; i < list.size(); ++i) {
		// Find the smallest element and put in list[i]
		result++;
		for (int j = i; j > 0 && list[j - 1] > list[j]; j--) {
			result++;
			string tmp = list[j - 1];
			list[j - 1] = list[j];
			list[j] = tmp;
		}
	}
	return result;
}

// ****************************************************************************
// Start functions for merge sort.
// ****************************************************************************
/**
 * Merge list1 and list2 into temp.  This function assumes that list1 and list2
 * are sorted.  After the function is complete temp will contain all of the
 * elements of list1 and list2 in sorted order.
 *
 * @param list1 Sorted list of strings
 * @param list2 Sorted list of strings
 * @param temp Will contain the elements of list1 and list2 in sorted order
 */
void merge(vector<string>& list1, vector<string>& list2, vector<string>& temp) {

	unsigned current1 = 0; // Current index in list1
	unsigned current2 = 0; // Current index in list2
	unsigned current3 = 0; // Current index in temp

	while (current1 < list1.size() && current2 < list2.size()) {

		if (list1[current1] < list2[current2])
			temp[current3++] = list1[current1++];
		else
			temp[current3++] = list2[current2++];
	}
	while (current1 < list1.size())
		temp[current3++] = list1[current1++];
	while (current2 < list2.size())
		temp[current3++] = list2[current2++];
}

/**
 * Sort the list using the merge sort algorithm.
 *
 * @param list Comparable strings
 */
void mergeSort(vector<string>& list) {

	int n = list.size();

	if (n > 1) {
		// Merge sort the first half
		vector<string> firstHalf(list.begin(), list.begin() + (n / 2));
		mergeSort(firstHalf);
		// Merge sort the second half
		vector<string> secondHalf(list.begin() + (n / 2), list.end());
		mergeSort(secondHalf);
		// Merge firstHalf with secondHalf

		merge(firstHalf, secondHalf, list);
	}
}

// ****************************************************************************
// End functions for merge sort.
// ****************************************************************************

// ****************************************************************************
// Start functions for quick sort.
// ****************************************************************************

/**
 * Partition a subsection of the list into a left side containing elements <
 * the pivot and a right side containing elements > pivot.  The index of the
 * pivot element is returned.
 *
 * @param list The list to be partitioned
 * @param first Start the partitioning here
 * @param last End the partitioning here
 * @param count An estimate of the number operations
 * @return The index of the pivot element
 */
int partition(vector<string>& list, int first, int last, long& count) {
	string pivot = list[first]; // Choose the first element as the pivot
	int low = first + 1; // Index for forward search
	int high = last; // Index for backward search
	while (high > low) {
		count++;
		while (low <= high && list[low] <= pivot) { // Search forward from left
			low++;
			count++;
		}
		while (low <= high && list[high] > pivot) { // Search backward from right
			high--;
			count++;
		}
		if (high > low) { // Swap two elements in the list
			string temp = list[high];
			list[high] = list[low];
			list[low] = temp;
		}
	}
	while (high > first && list[high] >= pivot) {
		high--;
		count++;
	}
	if (pivot > list[high]) { // Swap pivot with list[high]
		list[first] = list[high];
		list[high] = pivot;
		return high;
	} else {
		return first;
	}
}

/**
 * Quick sort auxiliary function that recursively performs the sorting.
 *
 * @param list Comparable strings
 * @param first Partition start
 * @param last Partition end
 */
long quickSort(vector<string>& list, int first, int last) {

	long count = 0;
	if (last > first) {
		int pivotIndex = partition(list, first, last, count);
		count += quickSort(list, first, pivotIndex - 1);

		count += quickSort(list, pivotIndex + 1, last);

	}
	return count;
}

/**
 * Sort the list using the quick sort algorithm.
 *
 * @param list Comparable strings
 */
long quickSort(vector<string>& list) {
	return quickSort(list, 0, list.size() - 1);
}

// ****************************************************************************
// End functions for quick sort.
// ****************************************************************************


int main(int argc, char* argv[]) {

	if (argc != 4) {
		cerr << "usage: analyze SORT FILENAMEPREFIX NUM" << endl;
		return 1;
	}

	string sort(argv[1]);
	string filePrefix(argv[2]);
	int num = atoi(argv[3]);
	string outputFileName(sort + "-" + filePrefix + ".data");

	// TODO Create an output file

	vector<string> words;
	for (int i = 1; i <= num; ++i) {

	  // TODO Open the file filePrefix + i + ".txt"
	  // Sort using the specified sorting algorithm
	  // Write results to output file
	  // Make sure to close input file when done
	}

	// TODO Make sure to close output file

	return 0;
}
