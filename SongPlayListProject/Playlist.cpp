#include<iostream>
#include<algorithm>

template <typename T>

struct music_play_list_node
{
	T* data;
	music_play_list_node *next, * prev;

	~music_play_list_node()
	{
		delete data;
	}
};

template <typename T>

struct music_play_list
{
public:
	using node = music_play_list_node<T>;
	using node_ptr = node*;
private:
	node_ptr head;
	size_t n;

public:
	music_play_list() : n(0)
	{
		head = new node{ NULL,NULL,NULL }; //dummy node -> having NULL data
		head->next = head;
		head->prev = head;
	}

	size_t size() const
	{
		return n;
	}

	void insert(const T& value)
	{
		node_ptr newNode = new node{ new T(value),NULL,NULL };
		auto dummy = head->prev;
		dummy->next = newNode;
		newNode->prev = dummy;

		if (head == dummy)
		{
			dummy->prev = newNode;
			newNode->next = dummy;
			head = newNode;
			return;
		}
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}

	void erase(const T& value)
	{
		auto cur = head, dummy = head->prev;
		while (cur != dummy)
		{
			if (*(cur->data) == value)
			{
				cur->prev->next = cur->next;
				cur->next->prev = cur->prev;
				if (cur == head)
					head = head->next;
				delete cur;
				n--;
				return;
			}
			cur = cur->next;
		}
	}
	//a basic structure for the required iterator
	struct playlist_iter
	{
	private:
		node_ptr ptr;
	public:
		//add members to access the actual data
		playlist_iter(node_ptr p) : ptr(p)
		{}
		T& operator*()
		{
			return *(ptr->data);
		}

		node_ptr get()
		{
			return ptr;
		}

		//increment-related operation
		playlist_iter& operator++()
		{
			ptr = ptr->next;
			return *this;
		}

		playlist_iter operator++(int)
		{
			playlist_iter iter = *this;
			++(*this);
			return iter;
		}

		//Decrement-related operation
		playlist_iter& operator--()
		{
			ptr = ptr->prev;
			return *this;
		}

		playlist_iter operator--(int)
		{
			playlist_iter iter = *this;
			--(*this);
			return iter;
		}

		//implement range based loop
		friend bool operator==(const playlist_iter& iter1, const playlist_iter& iter2)
		{
			return iter1.ptr == iter2.ptr;
		}

		friend bool operator!=(const playlist_iter& iter1, const playlist_iter& iter2)
		{
			return iter1.ptr != iter2.ptr;
		}

	};

		playlist_iter begin()
		{
			return playlist_iter(head);
		}

		playlist_iter begin() const
		{
			return playlist_iter(head);
		}

		playlist_iter end()
		{
			return playlist_iter(head->prev);
		}

		playlist_iter end() const
		{
			return playlist_iter(head->prev);
		}

		music_play_list(const music_play_list<T>& other) : music_play_list()
		{
			for (const auto& i : other)
				insert(i);
		}

		music_play_list(const std::initializer_list<T>& il) : head(NULL), n(0)
		{
			for (const auto& i : il)
				insert(i);
		}

		~music_play_list()
		{
			while (size())
			{
				erase(head->data);
			}
		}

};

//class for the music player's playlist
//instead of storing songs we will implement integer storage inicating the ID of the song
struct DopePlaylist
{
	music_play_list<int> list;

	void insert(int song)
	{
		list.insert(song);
	}

	void erase(int song)
	{
		list.erase(song);
	}

	//list all the songs
	void loopOnce()
	{
		for (auto& song : list)
			std::cout << song << " ";
		std::cout << std::endl;
	}
};

int main()
{
	DopePlaylist pl;
	pl.insert(1);
}

