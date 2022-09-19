/************************
* 
*   @properties of a binary tree
*     1.value of the parent node >= value of the left child
*     2.value of the parent child <= value of the right child
*    left child<=parent<=right child
* 
*      time complexity O(log n) =>Complete binary tree
**********/
#include<iostream>

struct node {
	int data;
	node* left, * right;
};

//wrapper to provide a clean interface for the node
struct bst {
	node* root = nullptr;

	//find function
	node* find(int value)
	{
		return find_impl(root, value);
	}

private:
	node* find_impl(node* current, int value)
	{
		if (!current)
		{
			std::cout << std::endl;
			return NULL;
		}
		if (current->data == value)
		{
			std::cout << "Found "<< std::endl;
			return current;
		}
		if (value < current->data)
		{
			std::cout << "Moving to the left from" << current->data << ",";
			return find_impl(current->left, value);
		}
		if (value > current->data)
		{
			std::cout << "Moving to the right from" << current->data << ",";
			return find_impl(current->right, value);
		}
	}
	//insertion function
public:
	void insert(int value)
	{
		if (!root)
			root = new node{ value,NULL,NULL };
		else
			insert_impl(root, value);
	}

private:
	void insert_impl(node* current, int value)
	{
		if (value < current->data)
		{
			if (!current->left)
				current->left = new node{ value,NULL,NULL };
			else
				insert_impl(current->left, value);
		}
		else
		{
			if (!current->right)
				current->right = new node{ value,NULL,NULL };
			else
				insert_impl(current->right, value);
		}
	}

	//inorder transversal function
public:
	void inorder()
	{
		inorder_impl(root);
	}

private:
	void inorder_impl(node* start)
	{
		if (!start)
			return;
		inorder_impl(start->left);  //move to the left sub tree
		std::cout << start->data << ""; //print out the current node
		inorder_impl(start->right);
	}

	//utility function to get the successor
public:
	node* successor(node* start)
	{
		auto current = start->right;
		while (current && current->left)
			current = current->left;
		return current;
	}

	//the delete function
	void deleteVal(int value)
	{
		root = delete_impl(root, value);
	}

private:
	node* delete_impl(node* start, int value)
	{
		if (!start)
			return NULL;
		if (value < start->data)
			start->left = delete_impl(start->left, value);
		else if (value > start->data)
			start->right = delete_impl(start->right, value);
		else
		{
			//the right part of the brain operate the left part
			if (!start->left)
			{
				auto tmp = start->right;
				delete start;
				return tmp;
			}
			if (!start->right)
			{
				auto tmp = start->left;
				delete start;
				return tmp;
			}

			auto succNode = successor(start);
			start->data = succNode->data;
			start->right = delete_impl(start->right, succNode->data);
		}
		return start;
	}
};

int main()
{
	bst tree;
	tree.insert(12);
	tree.insert(10);
	tree.insert(20);
	tree.insert(8);
	tree.insert(11);
	tree.insert(15);
	tree.insert(28);
	tree.insert(4);
	tree.insert(2);

	std::cout << "Inorder: ";
	tree.inorder();
	std::cout << std::endl;

	tree.deleteVal(12);
	std::cout << "Inorder after deleting: " << std::endl;
	tree.inorder();

	if (tree.find(12))
	{
		std::cout << "12 is in the tree " << std::endl;
	}
	else
	{
		std::cout << "12 is not in the tree " << std::endl;
	}
}