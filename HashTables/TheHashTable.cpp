// std::hash<std::string>(std::string) => used to generate hash values of string => contains an inbuilt algorithm
//std::unordered_set<key>  => store only a set of keys
//std::unordered_set<key> => store the keys and their values
//rows in a hash are known as buckets
// rehash() => for rehashing manually

#include<iostream>
#include<unordered_set>
#include<unordered_map>

//a display function to make our main function more readable
void display(const std::unordered_set<int>& container)
{
	for (const auto& element : container)
		std::cout << element << " ";
	std::cout << std::endl;
	
}

void display(const std::unordered_map<int,int>& container)
{
	for (const auto& element : container)
		std::cout << element.first << " :" << element.second << ",";
	std::cout << std::endl;

}

//unable to solve the error
void find(const std::unordered_set<int>& container, const auto& element)
{
	if (container.find(element) == container.end())
		std::cout << element << " not found " << std::endl;
	else
		std::cout << element << " found " << std::endl;
}

void find(const std::unordered_map<int,int>& container, const auto& element)
{
	auto it = container.find(element);
	if (it == container.end())
		std::cout << element << " not found " << std::endl;
	else
		std::cout << element << " found with value " << it->second <<std::endl;
}

int main()
{

}