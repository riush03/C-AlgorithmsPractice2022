#include<iostream>
#include<vector>

class MyHashMap {
	//we use two tables
	std::vector<int> first_data;
	std::vector<int> second_data;
	int size;

	int firstHash(int key) const
	{
		return key % size;
	}

	int secondHash(int key) const
	{
		return(key / size) % size;
	}

public:
	MyHashMap(int n) : size(n)
	{
		first_data = std::vector<int>(size, -1);
		second_data = std::vector<int>(size, -1);
	}

	std::vector<int>::iterator lookup(int key)
	{
		//find the key in both tables
		auto first_hash = firstHash(key);
		if (first_data[first_hash] == key)
		{
			std::cout << "Found " << key << " in the first table " << std::endl;
			return first_data.begin() + first_hash;
		}

		auto second_hash = secondHash(key);
		if (second_data[second_hash] == key)
		{
			std::cout << "Found " << key << " in the first table " << std::endl;
			return second_data.begin() + second_hash;
		}
		return second_data.end();
	}

	void erase(int key)
	{
		auto position = lookup(key);
		if (position != second_data.end())
		{
			*position = -1;
			std::cout << "Removed element " << key << std::endl;
		}
		else
		{
			std::cout << "Key :" << key << " was not found." << std::endl;
		}
	}

	void insert(int key)
	{
		insert_impl(key, 0, 1);
	}

	void insert_impl(int key, int cnt, int table)
	{
		if (cnt >= size)
		{
			std::cout << "Cycle detected while inserting " << key << ". Rehashing required. " << std::endl;
			return;
		}

		if (table == 1)
		{
			int hash = firstHash(key);
			if (first_data[hash] == -1)
			{
				std::cout << "Inserted key " << key << " in table " << table << std::endl;
				first_data[hash] = key;
			}
			else
			{
				int old = first_data[hash];
				first_data[hash] = key;
				std::cout << "Inserted key " << key << " in table " << table << " by replacing " << old << std::endl;
				insert_impl(old, cnt + 1, 2);
			}
		}
		else
		{
			int hash = secondHash(key);
			if (second_data[hash] == -1)
			{
				std::cout << "Inserted key in table " << key << " in table " << table << std::endl;
				second_data[hash] = key;
			}
			else
			{
				int old = second_data[hash];
				second_data[hash] = key;
				std::cout << "Inserted key " << key << " in table " << table << " by replacing " << old << std::endl;
				insert_impl(old, cnt + 1, 2);
			}
		}
	}

	void print()
	{
		std::cout << "Index: ";
		for (int i = 0; i < size; i++)
			std::cout << i << "\t";
		std::cout << std::endl;

		std::cout << "First data: ";
		for (auto i : first_data)
			std::cout << i << "\t";
		std::cout << std::endl;

		std::cout << "Second data: ";
		for (auto i : second_data)
			std::cout << i << "\t";
		std::cout << std::endl;
	}
};

int main()
{
	MyHashMap hashMap(7);
	hashMap.print();
	
	//insert elements
	hashMap.insert(10);
	hashMap.insert(20);
	hashMap.insert(30);

	std::cout << std::endl;

	hashMap.insert(105);
	hashMap.insert(8);
	hashMap.insert(70);
	hashMap.insert(9);
	hashMap.insert(90);
	hashMap.insert(7);

	std::cout << std::endl;

	hashMap.print();

	std::cout << std::endl;

	hashMap.insert(5); //this will cause cycle
}