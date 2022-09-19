/**************************
* O(n log n) =>sorting
* 
*   Aplication of heap => machine learning
******/
#include<iostream>
#include<vector>
#include<queue>

//a container to store received data
struct median {
	//data is store among two heaps => one min heap and one max heap
	std::priority_queue<int> max_heap;
	std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

	//insert function to insert the newly arrived data
	void insert(int data)
	{
		//first element
		if (max_heap.size() == 0)
		{
			max_heap.push(data);
			return;
		}

		if (max_heap.size() == min_heap.size())
		{
			if (data <= get())
				max_heap.push(data);
			else
				min_heap.push(data);
			return;
		}

		if (max_heap.size() < min_heap.size())
		{
			if (data > get())
			{
				max_heap.push(min_heap.top());
				min_heap.pop();
				min_heap.push(data);
			}
			else
				max_heap.push(data);
			return;
		}
		if (data < get())
		{
			min_heap.push(max_heap.top());
			max_heap.pop();
			max_heap.push(data);
		}
		else
			min_heap.push(data);
	}

	//get function to get the median from the containers
	double get()
	{
		if (max_heap.size() == min_heap.size())
			return (max_heap.top() + min_heap.top()) / 2.0;
		if (max_heap.size() < min_heap.size())
			return min_heap.top();
		return max_heap.top();
	}
};

int main()
{
	median med;
	med.insert(1);
	std::cout << "Median after insert 1:" << med.get() << std::endl;

	med.insert(5);
	std::cout << "Median after insert 5:" << med.get() << std::endl;

	med.insert(2);
	std::cout << "Median after insert 2:" << med.get() << std::endl;

	med.insert(40);
	std::cout << "Median after insert 40:" << med.get() << std::endl;

	return 0;
}