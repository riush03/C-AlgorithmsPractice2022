//bloom filters are more efficient than hastables
#include<iostream>>
#include<vector>

class BloomFilterSample
{
	std::vector<bool> data;
	int nBits;

	//the required hashing fuctions
	int hash(int num, int key)
	{
		switch (num)
		{
		case 0:
			return key % nBits;
		case 1:
			return (key / 7) % nBits;
		case 2:
			return (key / 11) & nBits;
		}
		return 0;
	}

public:
	BloomFilterSample(int n) : nBits(n)
	{
		data = std::vector<bool>(nBits, false);
	}

	void lookup(int key)
	{
		bool result = data[hash(0, key)] & data[hash(1, key)] & data[hash(2, key)];

		if (result)
		{
			std::cout << key << " may be present " << std::endl;
		}
		else
		{
			std::cout << key << " is not present " << std::endl;
		}
	 }

	void insert(int key)
	{
		data[hash(0, key)] = true;
		data[hash(1, key)] = true;
		data[hash(2, key)] = true;
		std::cout << key << "inserted." << std::endl;
	}
};

int main()
{

	BloomFilterSample bloom(11);
	bloom.insert(100);
	bloom.insert(56);
	bloom.insert(67);
	bloom.insert(79);
	bloom.insert(8);
	bloom.insert(5);
	bloom.lookup(23);
	bloom.lookup(67);
	bloom.lookup(8);
	bloom.lookup(34);
	bloom.lookup(78);
}