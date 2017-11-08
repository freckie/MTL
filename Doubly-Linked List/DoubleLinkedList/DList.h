#include<iostream>

namespace Frck
{

	template <typename U>
	struct Node
	{
		U data;
		Node<U>* prev;
		Node<U>* next;
	};

	/* 
		Doubly-Linked List "DList"
	*/
	template <typename T>
	class DList
	{
	private:

		Node<T>* head;
		Node<T>* tail;
		int listlen = 0;

	public:
		
		template <typename U>
		class iterator;

		DList();
		DList(DList<T>& _list);
		~DList();

		int len();

		void push_front(T _data);
		void pop_front();

		void push_back(T _data);
		void pop_back();

		T& front();
		T& back();

		void insert(int _idx, T _data);
		void erase(int _idx);
		void del(Node<T>* _node);

		void clear();	//초기화

		T& operator[] (int _index);
		DList<T>& operator=(DList<T>& _list);

		Node<T>* at(int _index);
		iterator<T> get(int _index);
		iterator<T> begin();
		iterator<T> end();

		iterator<T> insert(iterator<T> _idx, T _data);
		iterator<T> erase(iterator<T> _idx);

	public:

		template <typename U>
		class iterator
		{
		private:
			Node<U>* node;

		public:

			iterator(Node<U>* _node) : node(_node) {}

			auto& operator*()
			{
				return node->data;
			}

			auto& const operator->()
			{
				return &(node->data);
			}

			iterator<U> operator++()		//전위
			{
				node = node->next;
				return *this;
			}

			iterator<U> operator++(int)	//후위
			{
				iterator<U> temp(node);
				node = node->next;
				return temp;
			}

			iterator<U> operator--()		//전위
			{
				node = node->prev;
				return *this;
			}

			iterator<U> operator--(int)	//후위
			{
				iterator<U> temp(node);
				node = node->prev;
				return temp;
			}

			bool operator==(iterator<U>& rhs)
			{
				return (this->node == rhs.node);
			}

			bool operator!=(iterator<U>& rhs)
			{
				return (this->node != rhs.node);
			}
		};

	};

	template <typename T>
	DList<T>::DList()
	{
		head = new Node<T>;
		head->prev = nullptr;
		head->next = tail;
		head->data = NULL;

		tail = new Node<T>;
		tail->data = NULL;
		tail->next = nullptr;
		tail->prev = head;
	}

	template <typename T>
	DList<T>::DList(DList<T>& _list)
	{
		*this = _list;
	}

	template <typename T>
	DList<T>::~DList()
	{
		clear();
		delete head;
		delete tail;
	}

	template<typename T>
	int DList<T>::len()
	{
		return listlen;
	}

	template<typename T>
	void DList<T>::push_front(T _data)
	{
		Node<T>* temp = head->next;
		Node<T>* node = new Node<T>;

		node->data = _data;

		if (listlen == 0)
		{
			head->next = node;
			node->prev = head;
			node->next = tail;
			tail->prev = node;
			listlen++;
			return;
		}

		node->prev = head;
		node->next = temp;
		temp->prev = node;
		head->next = node;

		listlen++;
	}

	template<typename T>
	void DList<T>::push_back(T _data)
	{
		Node<T>* temp = tail->prev;
		Node<T>* node = new Node<T>;

		node->data = _data;

		if (listlen == 0)
		{
			head->next = node;
			node->prev = head;
			node->next = tail;
			tail->prev = node;
			listlen++;
			return;
		}

		node->next = tail;
		node->prev = temp;
		temp->next = node;
		tail->prev = node;

		listlen++;
	}

	template<typename T>
	void DList<T>::pop_front()
	{
		Node<T>* temp = head->next->next;

		temp->prev = head;
		delete head->next;
		head->next = temp;
		listlen--;
	}

	template<typename T>
	void DList<T>::pop_back()
	{
		Node<T>* temp = tail->prev->prev;
		delete temp->next;
		temp->next = tail;
		tail->prev = temp;
		listlen--;
	}

	template<typename T>
	T& DList<T>::front()
	{
		return head->next->data;
	}

	template<typename T>
	T& DList<T>::back()
	{
		return tail->prev->data;
	}

	template<typename T>
	void DList<T>::insert(int _idx, T _data)
	{
		Node<T>* node = new Node<T>;
		Node<T>* temp = head;

		node->data = _data;

		for (int i = 0; i < _idx; i++)
			temp = temp->next;

		node->next = temp->next;
		temp->next->prev = node;
		temp->next = node;
		node->prev = temp;
		listlen++;
	}

	template<typename T>
	void DList<T>::erase(int _idx)
	{
		Node<T>* temp = head;
		Node<T>* target;
		for (int i = 0; i < _idx; i++)
			temp = temp->next; //before the target
		target = temp->next;
		temp->next = target->next;
		target->next->prev = temp;
		delete target;
		listlen--;
	}

	template <typename T>
	void DList<T>::del(Node<T>* _node)
	{
		Node<T>* temp = _node->prev;
		_node->next->prev = temp;
		temp->next = _node->next;
		delete _node;
		listlen--;
	}

	template<typename T>
	void DList<T>::clear()
	{
		if (listlen == 0)
			return;

		Node<T>* temp = head->next;

		for (int i = 0; i < listlen; i++)
			pop_back();

		head->next = tail;
		tail->prev = head;

		listlen = 0;
	}

	template <typename T>
	T& DList<T>::operator[] (int _index)
	{
		Node<T>* temp;

		if (_index >= (listlen / 2))
		{
			temp = tail;
			for (int i = listlen; i > _index; i--)
				temp = temp->prev;
		}
		else
		{
			temp = head;
			for (int i = 0; i <= _index; i++)
				temp = temp->next;
		}
		return temp->data;
	}

	template <typename T>
	DList<T>& DList<T>::operator=(DList<T>& _list)
	{
		clear();
		for (int i = 0; i < _list.listlen; i++)
			push_back(_list[i]);
		return *this;
	}

	template <typename T>
	Node<T>* DList<T>::at(int _index)
	{
		Node<T>* temp = head;
		for (int i = 0; i < _index; i++)
			temp = temp->next;
		return temp;
	}

	template <typename T>
	DList<T>::iterator<T> DList<T>::get(int _index)
	{
		Node<T>* temp = head;
		for (int i = 0; i < _index; i++)
			temp = temp->next;
		iterator<T> tmpit(temp);
		return tmpit;
	}

	template <typename T>
	DList<T>::iterator<T> DList<T>::begin()
	{
		return iterator<T>(head->next);
	}

	template <typename T>
	DList<T>::iterator<T> DList<T>::end()
	{
		return iterator<T>(tail);
	}

	template<typename T>
	DList<T>::iterator<T> DList<T>::insert(iterator<T> _idx, T _data)
	{
		int count = 0;
		for (DList<T>::iterator<T> it = begin(); it != _idx; ++it)
			count++;
		insert(count, _data);
		return ++_idx;
	}

	template<typename T>
	DList<T>::iterator<T> DList<T>::erase(iterator<T> _idx)
	{
		int count = 0;
		for (DList<T>::iterator<T> it = begin(); it != _idx; ++it)
			count++;
		erase(count);
		return ++_idx;
	}
};
