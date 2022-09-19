#include<iostream>
#include<vector>

//the hash_map class
using uint = unsigned int;
class hash_map
{

	std::vector<int> data;
public:

	hash_map(size_t n)
	{
		data = std::vector<int>(n, -1);
	}

	//insetion function
	void insert(uint values)
	{
		int n = data.size();
		data[values % n] = values;
		std::cout << "Inserted " << values << std::endl;
	}

	//a look-up function to see whether an element is present in the map or not
	bool find(uint values)
	{
		int n = data.size();
		return (data[values % n] == values);
	}

	void remove(uint value)
	{
		int n = data.size();
		if (data[value % n] == value)
		{
			data[value % n] = -1;
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