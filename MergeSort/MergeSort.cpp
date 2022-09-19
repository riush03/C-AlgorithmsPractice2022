#include<iostream>
#include<vector>
#include<chrono>
#include<random>
#include<algorithm>
#include<numeric>

template <typename T>
std::vector<T> merge(std::vector<T>& first_array, std::vector<T>& second_array)
{
	std::vector<T> merged;

	auto iter1 = first_array.begin();
	auto iter2 = second_array.begin();

	while (iter1 != first_array.end() && iter2 != second_array.end())
	{
		if (*iter1 < *iter2)
		{
			merged.emplace_back(*iter1);
			iter1++;
		}
		else
		{
			merged.emplace_back(*iter2);
			iter2++;
		}
	}

	if (iter1 != first_array.end())
	{
		for (; iter1 != first_array.end(); iter1++)
			merged.emplace_back(*iter1);
	}
	else
	{
		for (; iter2 != second_array.end(); iter2++)
			merged.emplace_back(*iter2);
	}
	return merged;
}


template <typename T>
std::vector<T> mergeSort(std::vector<T> arr)
{
	if (arr.size() > 1)
	{
		auto mid = size_t(arr.size() / 2);
		auto left_half = mergeSort<T>(std::vector<T>(arr.begin(), arr.begin() + mid));
		auto right_half = mergeSort<T>(std::vector<T>(arr.begin() + mid,arr.end()));

		return merge<T>(left_half, right_half);
	}
	return arr;
}

//add the following function to print the vector
template <typename T>
void printVector(std::vector<T> arr)
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
	printVector<int>(S1);
	printVector<float>(S2);
	printVector<double>(S3);
	printVector<char>(C);
	std::cout << std::endl;

	auto sorted_s1 = mergeSort<int>(S1);
	auto sorted_s2 = mergeSort<float>(S2);
	auto sorted_s3 = mergeSort<double>(S3);
	auto sorted_s4 = mergeSort<char>(C);

	std::cout << " Arrays sorted using marge sort: " << std::endl;
	printVector<int>(sorted_s1);
	printVector<float>(sorted_s2);
	printVector<double>(sorted_s3);
	printVector<char>(sorted_s4);
	std::cout << std::endl;
}

int main()
{
	runMergeSortTest();
	return 0;
}