//include the required headers
#include<iostream>
#include<algorithm>
#include<vector>
#include<random>
#include<numeric>

template <typename weight_type,typename value_type,typename  fractional_type>

struct Object
{
	using Wtype = weight_type;
	using Vtype = value_type;
	using Ftype = fractional_type;

	Wtype weight;
	Vtype value;
	Ftype value_per_unit_weight;

	//the following operator overloads are to be used for sorting and I/O
	inline bool operator<(const Object<Wtype, Vtype, Ftype>& obj) const
	{
		
		return this->value_per_unit_weight < obj.value_per_unit_weight;
	}

	//the following overloads are to be used for sorting and I/O
	inline bool operator==(const Object<Wtype, Vtype, Ftype>& obj) const
	{
		return this->value_per_unit_weight == obj.value_per_unit_weight;
	}

	template <typename Wtype,typename Vtype,typename Ftype>
	friend std::ostream& operator<<(std::ostream& os, const Object<Wtype, Vtype, Ftype>& obj);
};

template <typename Wtype, typename Vtype, typename Ftype>
std::ostream& operator<<(std::ostream& os, const Object<Wtype, Vtype, Ftype>& obj)
{
	os << "Value: " << obj.value << "\t Weight: " << obj.weight << "\t Value /Unit/weight: " << obj.value_per_unit_weight;
	return os;
}


template <typename weight_type, typename value_type, typename  fractional_type>

auto fillKnackspack(std::vector<Object<weight_type, value_type, fractional_type>>& objects, weight_type knackspack_capacity)
{
	std::vector<Object<weight_type, value_type, fractional_type>> knackspack_content;
	knackspack_content.reserve(objects.size());

	//sorts objects in the decreasing order
	std::sort(objects.begin(), objects.end());
	std::reverse(objects.begin(), objects.end());

	//add the best objects to the knackspack
	auto current_object = objects.begin();
	weight_type curr_total_weight = 0;
	while (curr_total_weight <= knackspack_capacity && current_object != objects.end())
	{
		knackspack_content.push_back(*current_object);

		curr_total_weight += current_object->weight;
		current_object++;
	}

	//since the last object overflows the knackspack, adjust weight
	auto weight_of_last_object_to_remove = curr_total_weight - knackspack_capacity;
	knackspack_content.back().weight -= weight_of_last_object_to_remove;
	knackspack_content.back().value -= knackspack_content.back().value_per_unit_weight * weight_of_last_object_to_remove;
	return knackspack_content;
}

void test_the_knackspack(unsigned num_objects, unsigned knackspack_cap)
{
	using weight_type = unsigned;
	using value_type = double;
	using fractional_type = double;

	//intialize random number generator
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, num_objects);

	//create vector objects
	std::vector<Object<weight_type, value_type, fractional_type>> objects;
	objects.reserve(num_objects);
	for (auto i = 0; i < num_objects; i++)
	{
		auto weight = uniform_dist(rand);
		auto value = uniform_dist(rand);
		auto obj = Object<weight_type, value_type, fractional_type>{
			static_cast<weight_type>(weight),
			static_cast<value_type>(value),
			static_cast<fractional_type>(value) / weight
		};
		objects.push_back(obj);
	}

	//display the set of objects
	std::cout << "objects available: " << std::endl;
	for (auto& o : objects)
		std::cout << o << std::endl;
	std::cout << std::endl;
}

int main()
{
	test_the_knackspack(5, 13);
}