#include<iostream>
#include<vector>
#include<chrono>
#include<random>
#include<algorithm>
#include<numeric>

template <typename T>
auto partion(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator last)
{
	//create a 3 iterators
	auto pivot_val = *begin;
	auto left_iter = begin + 1;
	auto right_iter = last;

	while (true)
	{
		//starting from the first element of the vector find an element that is greater than the pivot
		while (*left_iter <= pivot_val && std::distance(left_iter, right_iter) > 0)
			left_iter++;
		//starting from the end of the vector moving to the beginning, find an element hat is less than the pivot
		while (*right_iter > pivot_val && std::distance(left_iter, right_iter) > 0)
			right_iter--;
		//if the left and right iterators meet, there are no elements left to swap
		if (left_iter == right_iter)
			break;
			//if else => swap the element pointed to by the left and right iterators
		else
			std::iter_swap(left_iter, right_iter);
	}
	if (pivot_val > *right_iter)
		std::iter_swap(begin, right_iter);
	return right_iter;
}

template <typename T>

void quickSort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator last)
{
	//incase there are more than 1 element in the vector apply the partitiopn operation
	if (std::distance(begin, last) >= 1)
	{
		auto pertation_iter = partion<T>(begin, last);

		//recursively sort the vectors created by the pertition operation
		quickSort<T>(begin, pertation_iter - 1);
		quickSort<T>(pertation_iter, last);
	}
}

template <typename T>
void printVec(std::vector<T> arr)
{
	for (auto i : arr)
		std::cout << i << " ";
	std::cout << std::endl;
}


void runMergeSortTest()
{
	std::vector<int> S1{ 45,56,7,8,1,3,67,23,89,2,4,5,6,10,11 };
	std::vector<float> S2{ 45.6f,1.0f,3.8f,1.0f,2.2f,3.9f,45.3f,5.5f,1.0f };
	std::vector<double> S3{ 45.6,1.0,3.9,56.9,45.0,3.0,7.0,2.0,56.0,21.0,22.0,14.0 };
	std::vector<char> C{ 'b','z','a','e','f','t','q','u','y' };

	std::cout << "Unsorted arrays " << std::endl;
	printVec<int>(S1);
	printVec<float>(S2);
	printVec<double>(S3);
	printVec<char>(C);
	std::cout << std::endl;

	quickSort<int>(S1.begin(), S1.end() - 1);
	quickSort<float>(S2.begin(), S2.end() - 1);
	quickSort<double>(S3.begin(), S3.end() - 1);
	quickSort<char>(C.begin(), C.end() - 1);

	std::cout << " Arrays sorted using quick sort: " << std::endl;
	printVec<int>(S1);
	printVec<float>(S2);
	printVec<double>(S3);
	printVec<char>(C);
	std::cout << std::endl;
}

int main()
{
	runMergeSortTest();
	return 0;
}