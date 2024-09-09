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
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
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
	friend class ForwardList;
};

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
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		*this = other;

		cout << "LCopyConstructor: " << this << endl;
	}
	ForwardList(ForwardList&& other)noexcept
	{
		*this = std::move(other);

		cout << "LMoveConstructor: " << this << endl;
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
			push_front(Temp->Data);

		reverse();

		cout << "LCopyAssignment: " << this << endl;

		return *this;
	}
	ForwardList& operator=(ForwardList&& other)noexcept
	{
		if (this == &other) return *this;

		while (Head)
			pop_front();

		this->Head = other.Head;
		this->size = other.size;

		other.size = 0;
		other.Head = nullptr;

		cout << "LMoveAssignment: " << this << endl;

		return *this;
	}

	class Iterator
	{
		Element* Iter;
	public:
		Iterator(Element* Iter) :Iter(Iter) {}
		~Iterator() {}

		Iterator operator++()
		{
			Iter = Iter->pNext;
			return *this;
		}
		int operator*() const
		{
			return Iter->Data;
		}
		bool operator!=(const Iterator& other) const
		{
			return Iter != other.Iter;
		}
	};

	class ConstIterator
	{
		Element* ConstIter;
	public:
		ConstIterator(Element* ConstIter) :ConstIter(ConstIter) {}
		~ConstIterator() {}

		ConstIterator operator++()
		{
			ConstIter = ConstIter->pNext;
			return *this;
		}
		const int operator*() const
		{
			return ConstIter->Data;
		}
		bool operator!=(const ConstIterator& other) const
		{
			return ConstIter != other.ConstIter;
		}
	};

	Iterator begin()
	{
		return Iterator(Head);
	}
	Iterator end()
	{
		return Iterator(nullptr);
	}
	ConstIterator begin() const
	{
		return ConstIterator(Head);
	}
	ConstIterator end() const
	{
		return ConstIterator(nullptr);
	}

	//	Adding elements:
	void push_front(int Data)
	{
		Head = new Element(Data, Head);

		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);

		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;

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
		if (index > size) return;
		if (index == 0) return push_front(Data);

		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;

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
	void reverse()
	{
		ForwardList buffer;

		while (Head)
		{
			buffer.push_front(Head->Data);
			pop_front();
		}

		this->Head = buffer.Head;
		this->size = buffer.size;
		buffer.Head = nullptr;
	}
	void print()const
	{
		cout << "Head:\t" << Head << endl;

		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "Количество элементов списка: " << size << endl;
	}

	friend class Stack;
};

class Stack
{
	ForwardList list;
public:
	Stack() {}
	~Stack()
	{
		while (!isEmpty())
			pop();
	}
	void push(int Data)
	{
		list.push_front(Data);
	}
	void pop()
	{
		list.pop_front();
	}
	bool isEmpty()const
	{
		return list.Head == nullptr;
	}
	void peek()const
	{
		if (!isEmpty()) return;
		cout << "Top element: " << list.Head << endl;
	}
	void size()const
	{
		cout << "Size: " << list.size << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");

	int n;
	Stack st;

	cout << "Введите количество элементов: "; cin >> n;
	cout << st.isEmpty() << endl;
	for (int i = 0; i < n; i++)
	{
		st.push(rand() % 100);
	}
	st.size();
	st.peek();

	st.pop();
	st.size();
	st.peek();
	cout << st.isEmpty() << endl;
}