/*******************
*   Implement a graph representing a network of cities and demostrante how it can be stored in an adjacency matrix
*****/
#include<iostream>
#include<vector>

//enum class to store the name of the cities
enum class city : int
{
	Nakuru,
	Nairobi,
	Kampala,
	Kinshansha,
	Dodoma,
	lagos,
	Mombasa
};

//<< operator for the city enum
std::ostream& operator<<(std::ostream& os, const city c)
{
	switch (c)
	{
	case city::Nakuru:
		os << "Nakuru";
		return os;
	case city::Nairobi:
		os << "Nairobi";
		return os;
	case city::Kampala:
		os << "Kampala";
		return os;
	case city::Kinshansha:
		os << "Kinshasha";
		return os;
	case city::Dodoma:
		os << "Dodoma";
		return os;
	case city::lagos:
		os << "Lagos";
		return os;
	case city::Mombasa:
		os << "Mombasa";
		return os;
	default:
		return os;
	}
}

//struct graph to encapsulate our data
struct graph {
	std::vector<std::vector<int>> data;

	//a constructor to create an empty graph
	graph(int n)
	{
		data.reserve(n);
		std::vector<int> row(n);
		std::fill(row.begin(), row.end(), -1);
		for (int i = 0; i < n; i++)
		{
			data.push_back(row);
		}
	}

	void addEdge(const city c1, const city c2, int dist)
	{
		std::cout << "ADD: " << c1 << "-" << c2 << "=" << dist << std::endl;

		auto n1 = static_cast<int>(c1);
		auto n2 = static_cast<int>(c2);
		data[n1][n2] = dist;
		data[n2][n1] = dist;
	}

	void removeEdge(const city c1, const city c2)
	{
		std::cout << "REMOVE: " << c1 << "-" << c2 << std::endl;

		auto n1 = static_cast<int>(c1);
		auto n2 = static_cast<int>(c2);
		data[n1][n2] = -1;
		data[n2][n1] = -1;
	}
};

int main()
{
	graph g(7);
	g.addEdge(city::Nakuru, city::Mombasa, 900);
	g.addEdge(city::Nakuru, city::Nairobi, 500);
	g.addEdge(city::Nairobi, city::Mombasa, 800);
	g.addEdge(city::Kampala, city::lagos, 2500);
	g.addEdge(city::Kinshansha, city::Dodoma, 1100);
	g.addEdge(city::Dodoma, city::Nairobi, 1000);

	g.removeEdge(city::Mombasa, city::Nakuru);

	return 0;
}