#include<iostream>
#include<vector>
#include<chrono>
#include<random>
#include<algorithm>
#include<numeric>

/******************************
*  linear search  =>works for all arrays || sorted or unsorted
****/
bool linear_search(int N, std::vector<int>& S)
{
	for (auto i : S)
	{
		if (i == N)
			return true; //element found
	}
	return false;
}

//binary search
bool binarySearch(int N, std::vector<int>& S)
{
	auto first = S.begin();
	auto last = S.end();

	while (true)
	{
	 //get the middle element of the current page
		auto range_length = std::distance(first, last);
		auto mid_element_index = first + std::floor(range_length / 2);
		auto mid_element = *(first,mid_element_index);

		//comapre the middle element of current range with N
		if (mid_element == N)
			return true;
		else if (mid_element > N)
			std::advance(last,  mid_element_index);
		if (mid_element < N)
			std::advance(first, mid_element_index);

		if (range_length == 1)
			return false;
	}
}

//functions to evaluate the perfomance of the binary search
void evalSmallSearchPerfomance()
{
	auto N = 2;
	std::vector<int> S{ 1,3,2,4,7,9,8,6 };

	std::sort(S.begin(), S.end());

	if (linear_search(N, S))
		std::cout << "Element found in set by linear search!" << std::endl;
	else
		std::cout << "Element not found." << std::endl;

	if (binarySearch(N, S))
		std::cout << "Element found in set by binary search!" << std::endl;
	else
		std::cout << "Element not found." << std::endl;
}

void evalLargePerfTest(int size,int N)
{
	std::vector<int> S;
	std::random_device rd;
	std::mt19937 rand(rd());

	//distribution in range [1, size]
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

	//insert random elements
	for (auto i = 0; i < size; i++)
		S.push_back(uniform_dist(rand));


	std::sort(S.begin(), S.end());

	//measure the time taken to start the clock
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	bool search_result = binarySearch(111, S);



	if (search_result)
		std::cout << "Element found in set! " << std::endl;
	else
		std::cout << "Element not found." << std::endl;
}

int main()
{
	evalSmallSearchPerfomance();

	return 0;
}