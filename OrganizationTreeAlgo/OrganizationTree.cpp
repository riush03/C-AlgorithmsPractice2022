//required cpp headers
#include<iostream>
#include<queue>

//structure of a binary tree
struct node
{
	std::string position;
	node *first, *second; //the node have two links to the othe nodes
};

struct orgTree
{
	node *root;

	//static function to create the tree
	static orgTree create_org_structure(const std::string& pos)
	{
	orgTree tree;
	tree.root = new node{pos,NULL,NULL };
	return tree;

	
}
	//level order transversal
	static void levelOrder(node* start)
	{
		if (!start)
			return;
		std::queue<node*> q;
		q.push(start);

		while (!q.empty())
		{
			int size = q.size();

			for (int i = 0; i < size; i++)
			{
				auto current = q.front();
				q.pop();
				std::cout << current->position << ",";
				if (current->first)
					q.push(current->first);
				if (current->second)
					q.push(current->second);
			}
			std::cout << std::endl;
		}
	}

	//this function help us to find a particular node based on a value to make our insertion function easier
	static node* find(node* root, const std::string& value)
	{
		if (root == NULL)
			return NULL;
		if (root->position == value)
			return root;
		auto firstFound = orgTree::find(root->first, value);
		if (firstFound != NULL)
			return firstFound;
		return orgTree::find(root->second, value);
	}

	//insertion function
	bool addSubordinate(const std::string& manager, const std::string& subordinate)
	{
		auto managerNode = orgTree::find(root, manager);
		if (!managerNode)
		{
			std::cout << "No postion named " << manager << std::endl;
			return false;
		}
		if (managerNode->first && managerNode->second)
		{
			std::cout << manager << " already have 2 suboridnates." << std::endl;
			return false;
		}
		if (!managerNode->first)
			managerNode->first = new node{ subordinate,NULL,NULL };
		else
			managerNode->second = new node{ subordinate,NULL,NULL };
		return true;
	}
};

int main()
{
	auto tree = orgTree::create_org_structure("CEO");
	if (tree.addSubordinate("CEO", "Deputy director"))
		std::cout << "Added Deputy Director in the tree." << std::endl;
	else
		std::cout << "Could not add deputy director in the tree." << std::endl;

	
	if (tree.addSubordinate("Deputy Director", "IT Head"))
		std::cout << "Added IT Head in the tree." << std::endl;
	else
		std::cout << "Could not add IT head in the tree." << std::endl;

	if (tree.addSubordinate("Deputy director", "Marketing head"))
		std::cout << "Added Marketing head in the tree." << std::endl;
	else
		std::cout << "Could not add marketing head in the tree." << std::endl;

	
	if (tree.addSubordinate("IT Head", "App Developement head"))
		std::cout << "Added App development head in the tree." << std::endl;
	else
		std::cout << "Could not add App developemt head in the tree." << std::endl;

	if (tree.addSubordinate("Marketing head", "Logistics head"))
		std::cout << "Added Logistics head in the tree." << std::endl;
	else
		std::cout << "Could not add deputy director in the tree." << std::endl;

	if (tree.addSubordinate("Marketing head", "Public relations head"))
		std::cout << "Added Public relation headfr in the tree." << std::endl;
	else
		std::cout << "Could not add public relations head in the tree." << std::endl;

	if (tree.addSubordinate("Deputy director", "Finance head"))
		std::cout << "Added Finance head in the tree." << std::endl;
	else
		std::cout << "Could not add Finance head in the tree." << std::endl;
}