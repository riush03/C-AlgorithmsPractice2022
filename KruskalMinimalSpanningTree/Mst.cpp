//required header
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>

template <typename T> class Graph;

//implementation of the disjoint set=> containing all the given vertices of the graph
template <typename T>
class GraphDisjointSet
{
private:
	struct Node
	{
		T data;
		Node(T _data) : data(_data)
		{}
		bool operator!=(const  Node& n) const
		{
			return this->data != n.data;
		}
	};
	//store the forest
	std::vector<Node> nodes; //numerical id
	std::vector<size_t> parent; // pointer to the parent
	std::vector<size_t> rank; //rank

	/******
	*  An implemenatation of makeset and  find operation
	* 
	*   Make-set => This intialize the data structure with N elements setting the rank of each element to 0
	*               and the parent pointer to itself
	*  find => starting from the given element this operation follows the parent pointer of elements until 
	*          the root of the tree is reached
	* 
	***/
public:
	GraphDisjointSet(size_t N)
	{
		nodes.reserve(N);
		parent.reserve(N);
		rank.reserve(N);
	}

	void add_set(const T& x)
	{
		nodes.emplace_back(x);
		parent.emplace_back(nodes.size() - 1); // the parent is the node itself
		rank.emplace_back(0); // the intial rank of all nodes is zero
	}

	auto find(T x)
	{
		//find the node that contains the element x
		auto node_f = std::find_if(nodes.begin(), nodes.end(), [x](auto n)
			{
				return n.data == x;
			});

		auto node_idx = std::distance(nodes.begin(), node_f);
		auto parent_idx = parent[node_idx];

		//Transverse the tree till we reach the root
		while (parent_idx != node_idx)
		{
			node_idx = parent_idx;
			parent_idx = parent[node_idx];
		}
		return parent_idx;
	}

	/***********
	*   Implemenatation of Union operation between two trees in the disjoint set
	* 
	*    Union => given two elements x and y this operation finds the roots of x and y
	****/
	void union_sets(T x, T y)
	{
		auto root_x = find(x);
		auto root_y = find(y);

		//if  x and y are the same do nothing and return
		if(root_x == root_y)
		{
			return;
		}

		//if x and y are in different sets, merge the set with lower rank into the set with the higher rank
		else if (rank[root_x] > rank[root_y])
		{
			parent[root_y] = parent[root_x];
			rank[root_x]++;
		}
		else
		{
			parent[root_x] = parent[root_y];
			rank[root_y]++;
		}
	}
};

// The graph implementation
template <typename T>
struct Edge {
	size_t src;
	size_t dest;
	T weight;

	//To compare edges only compare their weights
	inline bool operator<(const Edge<T>& e) const
	{
		return this->weight < e.weight;
	}

	inline bool operator>(const Edge<T>& e) const
	{
		return this->weight > e.weight;
	}

	//Allow the graph to be serial
};