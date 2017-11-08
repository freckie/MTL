// 나중에 template 사용하여 데이터 저장 타입 바꾸기.
// operator + (SList&, int, or 그 반대) 형식으로 해서 append 역할하도록.

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
	int listLength = 0;					//head는 포함하지 않음.
	void printError(ErrorCode _type);	//에러 출력

public:
	Node* head;

	SList();							//기본 생성자 :: head만 만들어짐.
	SList(int _data1);					//데이터가 한 개 입력된 list 생성자.
	~SList();							//소멸자. 요소를 모두 할당 해제 후 list 해제.

	int len();							//list의 길이 리턴.
	int length();						//list의 길이 리턴.
	void append(int _data);				//맨 뒤에 요소 추가.
	void add(int _index, int _data);	//해당 index에 요소 추가.(index-1 뒤에 추가)
	void del(int _index);				//해당 index 요소 삭제.
	int index(int _data);				//data를 찾아 해당하는 index 리턴. (data가 중복될 경우 index가 작은 거 리턴.)
	int data(int _index);				//index에 해당하는 data 리턴.
	bool search(int _data);				//해당 데이터가 존재하는지 검색.
	void init();						//list 초기화. (요소 전부 삭제)

	int operator[] (int _index);		//해당 index의 data 리턴. (=data함수 호출)
	SList& operator+ (SList& _slist2);	//첫 번째 list에 두 번째 list를 연결.
	bool operator== (SList& _slist2);	//두 list가 length 및 모든 요소가 같은지.
	bool operator!= (SList& _slist2);	//== 호출 후 반대로 리턴.
};

#endif