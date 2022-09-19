#include<iostream>
#include<vector>
#include<vector>
#include<random>
#include<chrono>
#include<algorithm>
#include<numeric>

//create an array with random elements
void transform_test(size_t size)
{
	std::vector<int> S, Tr;
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

	//insert andom elements
	for (auto i = 0; i < size; i++)
		S.push_back(uniform_dist(rand));

	std::cout << "Orginal array, S:";
	for (auto i : S)
		std::cout << i << " ";
	std::cout << std::endl;

	//std::transform()  => f(x) = x^2
	std::transform(S.begin(), S.end(), std::back_inserter(Tr),[](int x) {return std::pow(x, 2.0);});

	std::cout << "Transformed array, Tr:";
	for (auto i : Tr)
		std::cout << i << " ";
	std::cout << std::endl;

	/****
	using for each
	std::for_each(S.begin(), S.end(), [](int &x) {x = std::pow(x, 2.0);});

	std::cout << "After applting for each in S: ";
	for (auto i : S)
		std::cout << i << " ";
	std::cout << std::endl;
	****/
}

void reduce_test(size_t size)
{
	std::vector<int> S;
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

	//insert andom elements
	for (auto i = 0; i < size; i++)
		S.push_back(uniform_dist(rand));

	std::cout << "Reduce test:" << std::endl << "Orginal array, S:";
	for (auto i : S)
		std::cout << i << " ";
	std::cout << std::endl;

	//accumalate
	std::cout << "Using accumalte :";
	std::accumulate(S.begin(), S.end(), [](int acc, int x) {return acc + x;});
    
}

int main()
{
	transform_test(10);
	reduce_test(10);
	return 0;
}