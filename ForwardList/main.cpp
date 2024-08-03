#include <iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//	Adding elements:
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		
		Element* New = new Element(Data);
		Temp->pNext = New;
	}
	void pop_front()
	{
		Element* Temp = Head;
		Head = Temp->pNext;
		delete Temp;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Element* previous = Head;
		while (previous->pNext != Temp)
		{
			previous = previous->pNext;
		}
		previous->pNext = nullptr;
		delete Temp;
	}
	void insert(int Data, int index)
	{
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 1; i < index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}
	void erase(int index)
	{
		Element* Temp = Head;
		for (int i = 1; i < index; i++)
		{
			Temp = Temp->pNext;
		}
		Element* previous = Head;
		while (previous->pNext != Temp)
		{
			previous = previous->pNext;
		}
		previous->pNext = Temp->pNext;
		delete Temp;
	}

	//	Methods:
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		Element* Temp = Head;	//Temp - это итератор
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Element element(5);
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.push_back(123);
	list.print();

	list.pop_front();
	list.pop_back();
	list.print();

	int index;
	cout << "Введите индекс вставляемого элемента: "; cin >> index;
	list.insert(234, index);
	list.print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
}