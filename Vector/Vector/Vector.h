#pragma once

#include<iostream>

namespace Frck
{
	template <typename T>
	class iterator;

	template <typename T>
	class Vector
	{
	private:
		T* head;
		int size;
		int capacity;
		int factor;	//더해질 사이즈

	public:
		Vector(int _factor = 10)
			: capacity(_factor), head(new T[_factor]), size(0), factor(_factor) {}

		Vector(Vector<T>& vec)
		{
			capacity = vec.capacity;
			factor = vec.factor;
			size = vec.size;
			head = new T[capacity];

			for (int i = 0; i < size; i++)
				head[i] = vec.head[i];
		}

		~Vector()
		{
			delete[] head;
		}

		bool isFull() const
		{
			return size == capacity;
		}

		int get_size()
		{
			return size;
		}

		void push_front(T _data)
		{
			if (isFull())
			{
				capacity += factor;
				T* temp = head;
				head = new T[capacity];
				for (int i = size - 1; i >= 0; i--)
					head[i + 1] = temp[i];
				head[0] = _data;
				delete[] temp;
				size++;
			}
			else
			{
				for (int i = size - 1; i >= 0; i--)
					head[i + 1] = head[i];
				head[0] = _data;
				size++;
			}
		}

		void push_back(T _data)
		{
			if (isFull())
			{
				capacity += factor;
				T* temp = head;
				head = new T[capacity];
				for (int i = 0; i < size; i++)
					head[i] = temp[i];
				head[size++] = _data;
				delete[] temp;
			}
			else
			{
				head[size++] = _data;
			}
		}

		void pop_front()
		{
			if (size == 0)
				throw "Can't Pop from Empty Vector";
			for (int i = 0; i < size - 1; i++)
				head[i] = head[i + 1];
			size--;
			if(capacity - size > factor)
				shrink_to_fit();
		}

		void pop_back()
		{
			if (size == 0)
				throw "Can't Pop from Empty Vector";
			size--;
			if (capacity - size > factor)
				shrink_to_fit();
		}

		void insert(int _idx, T _data)
		{
			if (isFull())
				capacity += factor;

			T* temp = head;
			head = new T[capacity];
			for (int i = 0; i < _idx; i++)
				head[i] = temp[i];

			head[_idx] = _data;

			for (int i = _idx; i < size; i++)
				head[i + 1] = temp[i];
			size++;
			delete[] temp;
		}

		void erase(int _idx)
		{
			T* temp = head;
			head = new T[capacity];
			for (int i = 0; i < _idx; i++)
				head[i] = temp[i];

			for (int i = _idx; i < size - 1; i++)
				head[i] = temp[i + 1];
			size--;
			delete[] temp;
			if (capacity - size > factor)
				shrink_to_fit();
		}

		void shrink_to_fit()
		{
			T* temp = head;
			head = new T[size];
			for (int i = 0; i < size; i++)
				head[i] = temp[i];
			capacity = size;
			delete[] temp;
		}

		T& front()
		{
			return head[0];
		}

		T& back()
		{
			return head[size - 1];
		}

		T& at(int _idx)
		{
			return head[_idx];
		}

		T& operator[](int _idx)
		{
			return head[_idx];
		}

		Vector<T>& operator=(Vector<T>& vec)
		{
			delete[] head;
			capacity = vec.capacity;
			factor = vec.factor;
			size = vec.size;
			head = new T[capacity];

			for (int i = 0; i < size; i++)
				head[i] = vec.head[i];
			return *this;
		}

		bool operator==(Vector<T>& rhs)
		{
			if ((capacity != rhs.capacity || size != rhs.size))
				return false;
			else
				for (int i = 0; i < size; i++)
					if (head[i] != rhs.head[i])
						return false;
		}

		bool operator!=(Vector<T>& rhs)
		{
			return this == rhs;
		}

		iterator<T> begin()
		{
			return iterator<T>(head);
		}

		iterator<T> end()
		{
			return iterator<T>(head + size);
		}

		iterator<T> it_at(int _idx)
		{
			return iterator<T>(head + _idx);
		}

		iterator<T> insert(iterator<T> pos, T _data)
		{
			int count = pos.refer - head;
			insert(count, _data);
			return it_at(count);
		}

		iterator<T> erase(iterator<T> pos)
		{
			int count = pos.refer - head;
			erase(count);
			return it_at(count);
		}
	};

	template <typename T>
	class iterator
	{
	private:
		T* refer;
	public:
		iterator(T* refer) : refer(refer) {}

		T& operator*()
		{
			return *refer;
		}

		T* const operator-> ()
		{
			return refer;
		}

		iterator<T> operator++()
		{
			++refer;
			return *this;
		}

		iterator<T> operator++(int)
		{
			iterator<T> temp(--refer);
			return temp;
		}

		iterator<T> operator--()
		{
			--refer;
			return *this;
		}

		iterator<T> operator--(int)
		{
			iterator<T> temp(--refer);
			return temp;
		}

		bool operator==(iterator<T>& rhs)
		{
			return (this->refer == rhs.refer);
		}

		bool operator!=(iterator<T>& rhs)
		{
			return (this->refer != rhs.refer);
		}

		friend Vector<int>;
	};
}