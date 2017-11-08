#include"Vector.h"

#include<iostream>

using vector = Frck::Vector<int>;
using iterator = Frck::iterator<int>;

int main(void)
{
	vector vec;

	for (auto i : { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 })
		vec.push_back(i);

	for (iterator it = vec.begin(); it != vec.end(); ++it)
		*it += 1;

	for (iterator it = vec.begin(); it != vec.end();)
	{
		if (*it % 2 == 0)
			it = vec.erase(it);
		else
			++it;
	}
	for (auto i : vec)
		std::cout << i << ' ';
}