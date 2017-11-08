#pragma once

namespace MTL
{
	template <typename T>
	void swap(T& x, T& y)
	{
		T temp = x; x = y;  y = temp;
	}

	enum Dir
	{
		left, right
	};

	template <typename T>
	class Set
	{
	private:
		template <typename T>
		struct Node
		{
			T data;
			Node* up;
			Node* left;
			Node* right;

			Node() : up(nullptr), left(nullptr), right(nullptr) {}
			//Node(T& data) : data(data), up(nullptr), left(nullptr), right(nullptr) {}
			Node(T& data, Node<T>* up = nullptr, Node<T>* left = nullptr, Node<T>* right = nullptr)
				: data(data), up(up), left(left), right(right) {}
		};

	private:
		Node<T>* root;

	private:
		Node<T>* find_parent(const T& data)
		{
			Node<T>* parent = root;
			Node<T>* temp = (data < root->data ? root->left : root->right);
			while (temp != nullptr)
			{
				parent = temp;
				temp = (data < temp->data ? temp->left : temp->right);
			}
			return parent;
		}

		template <typename Functor>
		void in_order(Functor func, Node<T>* node)
		{
			if (node == nullptr)
				return;

			in_order(func, node->left);
			func(node->data);
			in_order(func, node->right);
		}

		void clear(Node<T>* node)
		{
			if (node == nullptr)
				return;

			clear(node->left);
			clear(node->right);
			delete node;
		}

		void copy(Node<T>* newnode, Node<T>* up, Node<T>* rhs, Dir dir)
		{
			if (rhs == nullptr)
				return;

			newnode->data = rhs->data;
			newnode->up = up;
			if (up != nullptr)
			{
				if (dir == Dir::left)
					up->left = newnode;
				else
					up->right = newnode;
			}

			copy(new Node<T>, newnode, rhs->left, Dir::left);
			copy(new Node<T>, newnode, rhs->right, Dir::right);
		}

	public:
		Set()
		{
			root = nullptr;
		}

		Set(Set& set)
		{
			root = nullptr;
			copy(set);
		}

		~Set()
		{
			clear();
		}

		void insert(T _data)
		{
			Node<T>* node = new Node<T>(_data);

			if (root == nullptr)
			{
				root = node;
				return;
			}

			Node<T>* temp = root;

			while (temp->left != nullptr && temp->right != nullptr)
			{
				if(_data == temp->data)
					throw "Data already exist.";
				temp = (_data < temp->data ? temp->left : temp->right);
			}

			node->up = temp;
			(_data < temp->data ? temp->left : temp->right) = node;
		}

		bool is_exist(T _data)
		{
			if (root->data == _data)
				return true;
			Node<T>* temp = (_data < root->data ? root->left : root->right);
			while (temp != nullptr)
			{
				if (_data == temp->data)
					return true;
				temp = (_data < temp->data ? temp->left : temp->right);
			}
			return false;
		}

		Node<T>* find(T _data)
		{
			Node<T>* temp = root;
			while (temp != nullptr)
			{
				if (_data == temp->data)
					return temp;
				else
					temp = (_data < temp->data ? temp->left : temp->right);
			}
			throw "������ ����.";
		}

		void erase(Node<T>* target)
		{
			Node<T>* temp;
			// ���ʿ��� ��尡 ���� ��� (�������� Ž��)
			if (target->right == nullptr
				&& target->left != nullptr)
			{
				temp = target->left;
				while (temp->right != nullptr)
					temp = temp->right;
				erase_target(target, temp, Dir::left);
			}
			// �����ʿ��� ��尡 ���� ��� (���������� Ž��)
			else if (target->right != nullptr
				&& target->left != nullptr)
			{
				temp = target->right;
				while (temp->left != nullptr)
					temp = temp->left;
				erase_target(target, temp, Dir::right);
			}
			// ���� ������ ��尡 �Ѵ� ���� ���
			else
			{
				if (target->up->left == target)
					target->up->left = nullptr;
				else
					target->up->right = nullptr;
				delete target;
			}
		}

		// (������ ���, �ٲ��� ������ ���, Ž���� ����)
		void erase_target(Node<T>* target, Node<T>* succ, Dir dir)
		{
			if (dir == Dir::left)
			{
				swap<T>(target->data, succ->data);
				if (succ->up == target)
				{
					target->left = succ->left;
					if(succ->left != nullptr)
						succ->left->up = target;
				}
				else
				{
					succ->up->right = succ->left; //nullptr�̶� ����.
					if (succ->left != nullptr)
						succ->left->up = succ->up;
				}
			}

			else
			{
				swap<T>(target->data, succ->data);
				if (succ->up == target)
				{
					target->right = succ->right;
					if (succ->right != nullptr)
						succ->right->up = target;
				}
				else
				{
					succ->up->left = succ->right;
					if (succ->right != nullptr)
						succ->right->up = succ->up;
				}
			}
			delete succ;
		}

		template <typename Functor>
		void in_order(Functor func)
		{
			in_order(func, root);
		}

		void clear()
		{
			clear(root);
			root = nullptr;
		}

		void copy(Set<T>& rhs)
		{
			clear();
			root = new Node<T>;
			copy(root, nullptr, rhs.root, Dir::left);
		}

		Set<T>& operator=(Set<T>& rhs)
		{
			copy(rhs);
			return *this;
		}
	};
}