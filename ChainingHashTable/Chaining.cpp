#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
//we use chaining to avoid collision
//the hash_map class
using uint = unsigned int;
class hash_map
{

	std::vector<std::list<int>> data;
public:

	hash_map(size_t n)
	{
		data.resize(n);
	}

	//insetion function
	void insert(uint values)
	{
		int n = data.size();
		data[values % n].push_back(values);
		std::cout << "Inserted " << values << std::endl;
	}

	//a look-up function to see whether an element is present in the map or not
	bool find(uint values)
	{
		int n = data.size();
		auto& entries = data[values % n];
		return std::find(entries.begin(), entries.end(), values) != entries.end();
	}

	void remove(uint value)
	{
		int n = data.size();
		auto& entries = data[value % n];
		auto iter = std::find(entries.begin(), entries.end(), value);
		if (iter != entries.end())
		{
			entries.erase(iter);
			std::cout << "Removed " << value << std::endl;
		}
	}
};

int main()
{
	hash_map map(7);

	//lamda function to print the status of the lookup
	auto display = [&](int value)
	{
		if (map.find(value))
			std::cout << value << "found in the hash map.";
		else
			std::cout << value << "not found in the hashmap.";
		std::cout << std::endl;
	};

	map.insert(2);
	map.insert(25);
	map.insert(290);

	display(25);
	display(100);

	map.insert(100);
	display(100);
	map.remove(25);
}