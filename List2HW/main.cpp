#include <iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;
	Element* pPrev;
	Element* pNext;
public:
	Element(int Data, Element* pPrev = nullptr, Element* pNext = nullptr) :Data(Data), pPrev(pPrev), pNext(pNext) 
	{
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element() 
	{
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}

	friend class List;
};

class List
{
	Element* Head;
	Element* Tail;
	unsigned int size;
public:
	List()
	{
		Head = nullptr;
		Tail = nullptr;
		size = 0;

		cout << "LConstructor:\t" << this << endl;
	}
	~List() 
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//	Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr)
		{
			Head = new Element(Data);
			Tail = Head;
		}
		else
		{
			Element* Temp = Head;
			Head = new Element(Data, nullptr, Head);
			Temp->pPrev = Head;
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Tail == nullptr)
		{
			Tail = new Element(Data);
			Head = Tail;
		}
		else
		{
			Element* Temp = Tail;
			Tail = new Element(Data, Tail);
			Temp->pNext = Tail;
		}
		size++;
	}
	void pop_front()
	{
		if (Head == nullptr) return;
		Element* buffer = Head;
		Element* Temp = buffer->pNext;
		Head = Temp;
		Temp->pPrev = nullptr;
		delete buffer;
		size--;
	}
	void pop_back()
	{
		if (Tail == nullptr) return;
		Element* buffer = Tail;
		Element* Temp = buffer->pPrev;
		Tail = Temp;
		Temp->pNext = nullptr;
		delete buffer;
		size--;
	}
	void Head_insert(int Data, int index)
	{
		if (index > size) return;
		if (index == 0) return push_front(Data);

		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;

		Element* Temp_next = Temp->pNext;

		Temp->pNext = new Element(Data, Temp, Temp->pNext);
		Temp_next->pPrev = Temp->pNext;

		size++;
	}
	void Tail_insert(int Data, int index)
	{
		if (index > size) return;
		if (index == 0) return push_back(Data);

		Element* Temp = Tail;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pPrev;

		Element* Temp_prev = Temp->pPrev;

		Temp->pPrev = new Element(Data, Temp->pPrev, Temp);
		Temp_prev->pNext = Temp->pPrev;

		size++;
	}
	void Head_erase(int index)
	{
		if (index > size) return;
		if (index == 0) return pop_front();

		Element* Temp = Head;
		for(int i = 0; i < index; i++)
			Temp = Temp->pNext;

		Element* Temp_prev = Temp->pPrev;
		Element* Temp_next = Temp->pNext;

		Temp_prev->pNext = Temp_next;
		Temp_next->pPrev = Temp_prev;

		delete Temp;

		size--;
	}
	void Tail_erase(int index)
	{
		if (index > size) return;
		if (index == 0) return pop_front();

		Element* Temp = Tail;
		for (int i = 0; i < index; i++)
			Temp = Temp->pPrev;

		Element* Temp_prev = Temp->pPrev;
		Element* Temp_next = Temp->pNext;

		Temp_prev->pNext = Temp_next;
		Temp_next->pPrev = Temp_prev;

		delete Temp;

		size--;
	}


	//	Methods:
	void print()
	{
		cout << "Head:\t" << Head << endl;

		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "Tail:\t" << Tail<< endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()
	{
		cout << "Tail:\t" << Tail << endl;

		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp << tab << Temp->pNext << tab << Temp->Data << tab << Temp->pPrev << endl;

		cout << "Head:\t" << Head << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
};

#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;

	List list;

	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}

	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}

	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();

	int index;
	cout << "Введите номер добавляемого элемента с головы: "; cin >> index;
	list.Head_insert(123, index);
	list.print();
	cout << "Введите номер удаляемого элемента с головы: "; cin >> index;
	list.Head_erase(index);
	list.print();
	cout << "Введите номер добавляемого элемента с хвоста: "; cin >> index;
	list.Tail_insert(234, index);
	list.print();
	cout << "Введите номер удаляемого элемента с головы: "; cin >> index;
	list.Tail_erase(index);
	list.print();

	cout << endl;
	list.reverse_print();
#endif // BASE_CHECK

}