#include"Set.h"
#include<iostream>

using namespace MTL;

int main(void)
{
	Set<int> set1;
	set1.insert(3);
	set1.insert(1);
	set1.insert(5);
	set1.insert(0);
	set1.insert(2);
	set1.insert(4);
	set1.insert(6);
	set1.erase(set1.find(3));

	std::cout << "set1 : ";
	set1.in_order([](int num) { std::cout << num << ' '; });
	std::cout << std::endl;

	Set<int> set2(set1);

	std::cout << "set2 : ";
	set2.in_order([](int num) { std::cout << num << ' '; });
	std::cout << std::endl;

}