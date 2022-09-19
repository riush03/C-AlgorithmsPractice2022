#include<iostream>
#include<algorithm>
#include<vector>
#include<random>
#include<numeric>

/*****************
* 
*     >>>>> A bad day on the bank
*   bank queue
*   amount of time a1 ------------------------- 
*                     |9| 8| 5| 4| 3| 2| 2| 1|      
*                     -------------------------
*  person p1          O     O      O      O     O
*                    /|\   /|\    /|\    /|\   /|\
*                    / \   / \    / \    / \   / \
* 
*  consider 10 people are in the queue try maximizing the average waiting time for all of them
*    
average waiting time W1 ------------------------------------------
****/

template <typename T>
auto compute_waiting_time(std::vector<T>& service_times)
{
	std::vector<T> w(service_times.size());
	w[0] = 0;

	for (auto i = 1; i < service_times.size(); i++)
		//i-1people
		w[i] = w[i - 1] + service_times[i - 1];

	return w;
}

//generic function to print a vector
template <typename T>
void printVector(std::vector<T>& V)
{
	for (auto& i : V)
		std::cout << i << " ";
	std::cout << std::endl;
}

template <typename T>
void computeWaitingTimes(std::vector<T>& service_times)
{
	auto waiting_times = compute_waiting_time<int>(service_times);

	std::cout << "Service time : " << std::endl;
	printVector<T>(service_times);

	std::cout << "Waiting tim : " << std::endl;
	printVector<T>(waiting_times);

	std::cout << "Average waiting time = " << std::accumulate(waiting_times.begin(), waiting_times.end(), 0.0) / waiting_times.size();
	std::cout << std::endl;
}

//drive code
void Sjsf(size_t size)
{
	std::vector<int> service_times;
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

	service_times.reserve(size);
	for (auto u = 0; u < size; u++)
		service_times.push_back(uniform_dist(rand));

	computeWaitingTimes<int>(service_times);

	//Re-order the elements in the queue
	std::sort(service_times.begin(), service_times.end());

	computeWaitingTimes<int>(service_times);
}

int main(int argc,char * argv[])
{
	Sjsf(10);
}