#include<iostream>
#include"List.h"

using namespace std;

/**** Class SList Private Methods ****/

void SList::printError(ErrorCode _type)
{
	if (_type = ErrorCode::InvalidIndex)
		cout << "Error! :: Invalid Index." << endl;
}

/**** Class SList Public Methods ****/

SList::SList()
{
	head = new Node;
	head->next = nullptr;
	head->data = NULL;
}

SList::SList(int _data1)
{
	head = new Node;
	Node* first = new Node;

	first->data = _data1;
	first->next = nullptr;
	head->next = first;
	listLength++;
}

SList::~SList()
{
	Node* pivot = head;
	Node* target = head;

	//길이가 0일 때.
	if (listLength == 0)
		delete pivot;

	else
	{
		target = head->next;
		pivot = target->next;

		for (int i = 1; i < listLength; i++)
		{
			delete target;
			target = pivot;
			pivot = pivot->next;
		}
		delete pivot;
	}
}

int SList::len()
{
	return listLength;
}

int SList::length()
{
	return listLength;
}

void SList::append(int _data)
{
	Node* temp = head;
	Node* node = new Node;

	node->data = _data;
	node->next = nullptr;

	for (int i = 0; i < listLength; i++)
		temp = temp->next;

	temp->next = node;
	listLength++;
}

void SList::add(int _index, int _data)
{
	Node* temp = head;
	Node* temp2;
	Node* node = new Node;

	node->data = _data;
	
	for (int i = 0; i < _index; i++)
		temp = temp->next;

	temp2 = temp->next;
	temp->next = node;
	node->next = temp2;
	listLength++;
}

void SList::del(int _index)
{
	Node* temp = head;
	Node* temp2;

	for (int i = 0; i < _index; i++)
		temp = temp->next;

	temp2 = temp->next->next;
	delete temp->next;
	temp->next = temp2;
	listLength--;
}

int SList::index(int _data)
{
	Node* temp = head;

	for (int i = 0; i < listLength; i++)
	{
		temp = temp->next;
		if (temp->data == _data)
			return i;
	}
	return INT_MIN;
}

int SList::data(int _index)
{
	Node* temp = head;

	if (_index < 0 || _index > listLength)
	{
		printError(ErrorCode::InvalidIndex);
		return INT_MIN;
	}

	for (int i = 0; i < _index; i++)
		temp = temp->next;

	return temp->next->data;
}

bool SList::search(int _data)
{
	Node* temp = head;

	for (int i = 0; i < listLength; i++)
	{
		temp = temp->next;
		if (temp->data == _data)
			return true;
	}
	return false;
}

void SList::init()
{
	Node* pivot = head;
	Node* target = head;

	target = head->next;
	pivot = target->next;

	for (int i = 1; i < listLength; i++)
	{
		delete target;
		target = pivot;
		pivot = pivot->next;
	}
	head->next = nullptr;
}

/**** Class SList Operators ****/

int SList::operator[] (int _index)
{
	Node* temp = head;

	for (int i = 0; i < _index; i++)
		temp = temp->next;

	return temp->next->data;
}

SList& SList::operator+ (SList& _slist2)
{
	Node* temp = head;

	for (int i = 0; i < listLength; i++)
		temp = temp->next;

	temp->next = _slist2.head->next;
	listLength += _slist2.listLength;
	return *this;
}

bool SList::operator== (SList& _slist2)
{
	Node* temp = head;
	Node* temp2 = _slist2.head;

	if (listLength != _slist2.listLength)
		return false;
	else
	{
		for (int i = 0; i < listLength; i++)
		{
			temp = temp->next;
			temp2 = temp2->next;

			if (temp->data != temp2->data)
				return false;
		}
		return true;
	}
}

bool SList::operator!= (SList& _slist2)
{
	return !(*this == _slist2);
}