// ���߿� template ����Ͽ� ������ ���� Ÿ�� �ٲٱ�.
// operator + (SList&, int, or �� �ݴ�) �������� �ؼ� append �����ϵ���.

#pragma once

#ifndef __LIST_H__
#define __LIST_H__

enum ErrorCode
{
	InvalidIndex
};

class SList	//Singly-Linked List
{
private:
	struct Node
	{
		int data;
		Node* next;
	};
	int listLength = 0;					//head�� �������� ����.
	void printError(ErrorCode _type);	//���� ���

public:
	Node* head;

	SList();							//�⺻ ������ :: head�� �������.
	SList(int _data1);					//�����Ͱ� �� �� �Էµ� list ������.
	~SList();							//�Ҹ���. ��Ҹ� ��� �Ҵ� ���� �� list ����.

	int len();							//list�� ���� ����.
	int length();						//list�� ���� ����.
	void append(int _data);				//�� �ڿ� ��� �߰�.
	void add(int _index, int _data);	//�ش� index�� ��� �߰�.(index-1 �ڿ� �߰�)
	void del(int _index);				//�ش� index ��� ����.
	int index(int _data);				//data�� ã�� �ش��ϴ� index ����. (data�� �ߺ��� ��� index�� ���� �� ����.)
	int data(int _index);				//index�� �ش��ϴ� data ����.
	bool search(int _data);				//�ش� �����Ͱ� �����ϴ��� �˻�.
	void init();						//list �ʱ�ȭ. (��� ���� ����)

	int operator[] (int _index);		//�ش� index�� data ����. (=data�Լ� ȣ��)
	SList& operator+ (SList& _slist2);	//ù ��° list�� �� ��° list�� ����.
	bool operator== (SList& _slist2);	//�� list�� length �� ��� ��Ұ� ������.
	bool operator!= (SList& _slist2);	//== ȣ�� �� �ݴ�� ����.
};

#endif