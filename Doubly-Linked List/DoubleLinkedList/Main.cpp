#include<iostream>
#include"DList.h"

using namespace std;
using namespace Frck;
using miterator = DList<int>::iterator<int>;

int main(void)
{
	DList<int> a;
	for (int i = 0; i < 8; i++)
		a.push_back(i);

	a.insert(a.get(5), 100);

	for (miterator iter = a.begin(); iter != a.end(); ++iter)
	{
		cout << *iter << endl;
	}

}