#include <iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		count++;
	}
	~Element()
	{
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
	}
	friend class ForwardList;
};
int Element::count = 0;

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other):ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/

		*this = other;

		cout << "LCopyConstructor: " << this << endl;
	}
	~ForwardList()
	{
		while (Head) pop_front();
		pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//	Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other) return *this;

		while (Head)
			pop_front();

		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);

		cout << "LCopyAssignment: " << this << endl;

		return *this;
	}

	//	Adding elements:
	void push_front(int Data)
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;*/

		Head = new Element(Data, Head);

		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);

		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;

		/*Element* New = new Element(Data);
		Temp->pNext = New;*/

		Temp->pNext = new Element(Data);
		size++;
	}
	void pop_front()
	{
		if (Head == nullptr) return;
		Element* Temp = Head;
		Head = Head->pNext;
		delete Temp;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr || Head->pNext == nullptr) return pop_front();

		Element* Temp = Head;
		while (Temp->pNext->pNext)
			Temp = Temp->pNext;

		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void insert(int Data, int index)
	{
		if (index > Head->count) return;
		if (index == 0) return push_front(Data);

		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;

		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/

		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	void erase(int index)
	{
		if (index > size) return;
		if (index == 0) return pop_front();

		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;

		Element* errased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete errased;

		size--;
	}

	//	Methods:
	void print()const
	{
		cout << "Head:\t" << Head << endl;

		/*Element* Temp = Head;	//Temp - это итератор
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/

		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов списка: " << Element::count << endl;
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
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
#endif // BASE_CHECK

	int n;
	cout << "Введите количество элементов: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//if (i % (1024*1024) == 0) cout << i << tab;
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
	cout << "List filled" << endl;
	list.print();

	ForwardList list2 = list;
	/*ForwardList list2;
	list2 = list;*/
	list2.print();
}