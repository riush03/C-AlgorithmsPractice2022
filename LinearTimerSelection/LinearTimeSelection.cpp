#include<iostream>
#include<vector>
#include<chrono>
#include<random>
#include<algorithm>
#include<numeric>

//a function to find the median element
template<typename T>
auto findMedian(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator last)
{
	//sort the array
	quick_sort<T>(begin, last);

	//return the middle element
	return begin + (std::distance(begin, last) / 2);
}

template<typename T>
auto partition_using_given_pivot(typename std::vector<T>::iterator begin, 
	typename std::vector<T>::iterator end,
	typename std::vector<T>::iterator pivot)
{
	//since the pivot is given
	//create two iterators pointing to the first and the last element of the vector respectively
	auto left_iter = begin;
	auto right_iter = end;

	while (true)
	{
		//starting from the first element of the vector find an element that is greater than the pivot
		while (*left_iter < *pivot && left_iter != right_iter)
			left_iter++;
		//starting from the end of the vector moving to the beginning, find an element hat is less than the pivot
		while (*right_iter >= *pivot &&  left_iter != right_iter)
			right_iter--;
		//if the left and right iterators meet, there are no elements left to swap
		if (left_iter == right_iter)
			break;
		//if else => swap the element pointed to by the left and right iterators
		else
			std::iter_swap(left_iter, right_iter);
	}
	if (*pivot > *right_iter)
		std::iter_swap(pivot, right_iter);
	return right_iter;
}

//implement the linear time search algorithm
template<typename T>
typename std::vector<T>::iterator linearTimeSelect(typename std::vector<T>::iterator begin, typename std::vector<T>iterator last, size_t i)
{
	auto size = std::distance(begin, last);

	if (size > 0 && i < size)
	{
		//get the number of input vector groups of 5 elements each
		auto num_vecs = (size + 4) / 5;
		size_t j = 0;

		//for each input vector , find the median and stre in vector m
		std::vector<T> M;
		for (; j < size / 5; j++)
		{
			auto b = begin + (j * 5);
			auto l = begin + (j * 5) + 5;

			M.push_back(*findMedian<T>(b, l));
		}
		if (j * 5 < size)
		{
			auto b = begin + (j * 5);
			auto l = begin + (j * 5) + (size % 5);

			M.push_back(*findMedian<T>(b, l));
		}
		//find the middle element q
		auto median_of_medians = (M.size() == 1) ? M.begin():
			linearTimeSelect<T>(M.begin(), M.end() - 1, M.size() / 2);
		//Apply the partition operation and find the correct position of k of pivot q
		auto partaition_iter = partition_using_given_pivot<T>(begin, last, median_of_medians);
		auto k = std::distance(begin, partaition_iter) + 1;

		if (i == k)
			retutn pertation_iter;
		else if (i < k)
			return linearTimeSelect<T>(begin, pertation_iter - 1, i);
		else(i > k)
			return linearTimeSelect<T>( pertation_iter +1,last, i-k);
	}
	else
	{
		return begin;
	}
}

