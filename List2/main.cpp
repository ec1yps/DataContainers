﻿#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------------------\n"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	} *Head, *Tail;
	size_t size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (Head) pop_front();
		while (Head) pop_back();
			
		cout << "LDestructor:\t" << this << endl;
	}

	//	Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			Element* New = new Element(Data);

			New->pNext = Head;
			Head = Head->pPrev = New;
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
			Head = Tail = new Element(Data);
		else
		{
			Element* New = new Element(Data);

			New->pPrev = Tail;
			Tail = Tail->pNext = New;
		}
		size++;
	}
	void insert(int Data, int index)
	{
		if (index < 0 || index > size) return;
		if (index == 0) return push_front(Data);
		if (index == size) return push_back(Data);

		Element* Temp = Head;

		if (index <= size / 2)
		{
			for (int i = 0; i < index - 1; i++)
				Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index; i++)
				Temp = Temp->pPrev;
		}

		Temp->pNext = Temp->pNext->pPrev = new Element(Data, Temp->pNext, Temp);
		
		size++;
	}

	//	Removing elements:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr) return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
		}
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr) return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
		}
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}
	void erase(int index)
	{
		if (index < 0 || index > size) return;
		if (index == 0) return pop_front();
		if (index == size - 1) return pop_back();

		Element* Temp = Head;

		if (index <= size / 2)
		{
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index; i++)
				Temp = Temp->pPrev;
		}

		Temp->pNext = Temp->pNext->pNext;
		delete Temp->pNext->pPrev;
		Temp->pNext->pPrev = Temp;

		size--;
	}

	//	Methods:
	void print()
	{
		cout << delimiter << endl;

		cout << "Head:\t" << Head << endl;

		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "Tail:\t" << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;

		cout << delimiter << endl;
	}
	void reverse_print()
	{
		cout << delimiter << endl;

		cout << "Tail:\t" << Tail << endl;

		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "Head:\t" << Head << endl;
		cout << "Количество элементов списка: " << size << endl;

		cout << delimiter << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	cout << "Введите номер вставляемого элемента: "; cin >> n;
	list.insert(123, n);
	list.print();
	cout << "Введите номер удаляемого элемента: "; cin >> n;
	list.erase(n);
	list.print();
}