#include <iostream>
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
		friend class Queue;
	} *Head, *Tail;
	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}

		//				Comparison operators:
		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		//				Dereference operators:
		const int& operator*()const
		{
			return Temp->Data;
		}
	};

public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~ConstIterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}
		ConstIterator& operator++()	//Prefix increment
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)//Postfix increment
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
	};

	class ConstReverseIterator : public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
			cout << "RItConstructor:\t" << this << endl;
		}
		~ConstReverseIterator()
		{
			cout << "RItDestructor:\t" << this << endl;
		}

		//					Incremento/Decremento:
		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}

		int& operator*()
		{
			return Temp->Data;
		}
	};

	class ReverseIterator : public ConstReverseIterator 
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}

		int& operator*()
		{
			return Temp->Data;
		}
	};

	ConstIterator begin()const
	{
		return Head;
	}
	ConstIterator end()const
	{
		return nullptr;
	}

	ConstReverseIterator rbegin()const
	{
		return Tail;
	}
	ConstReverseIterator rend()const
	{
		return nullptr;
	}

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}

	//				Constructors:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			push_back(*it);
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "LCopyConstructor:\t" << this << endl;
	}
	List(List&& other)noexcept
	{
		*this = std::move(other);

		cout << "LMoveConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (Head) pop_front();
		while (Head) pop_back();
			
		cout << "LDestructor:\t" << this << endl;
	}

	//	Operators:
	List& operator=(const List& other)
	{
		if (this == &other) return *this;

		while (Head)
			pop_front();

		for (int i : other)
			push_back(i);

		cout << "LCopyAssignment:\t" << this << endl;

		return *this;
	}
	List& operator=(List&& other)noexcept
	{
		if (this == &other) return *this;

		while (Head)
			pop_front();

		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;

		other.size = 0;
		other.Tail = nullptr;
		other.Head = nullptr;

		cout << "LMoveAssignment:\t" << this << endl;

		return *this;
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
			Head = Head->pPrev = new Element(Data, Head);
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
			Head = Tail = new Element(Data);
		else
		{
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
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

	friend class Queue;
};

List operator+(const List& left, const List& right)
{
	cout << "Operator +:\t" << endl;

	List buffer = left;
	
	for (int i : right)
		buffer.push_back(i);

	return buffer;
}

void Grow(List& list)
{
	for (List::Iterator it = list.begin(); it != list.end(); ++it)
		*it *= 10;
}

class Queue
{
	List queue;
public:
	Queue() {}
	~Queue() 
	{
		while (queue.Head)
		{
			Dequeue();
		}
	}

	void Enqueue(int Data)
	{
		queue.push_back(Data);
	}
	void Dequeue()
	{
		queue.pop_front();
	}
	bool isEmpty()const
	{
		return queue.Head == nullptr && queue.Tail == nullptr;
	}
	int peek_front()const
	{
		return queue.Head->Data;
	}
	int peek_back()const
	{
		return queue.Tail->Data;
	}
	size_t size()const
	{
		return queue.size;
	}
};

void main()
{
	setlocale(LC_ALL, "");

	Queue qu;

	cout << qu.isEmpty() << endl;

	int n;
	cout << "Введите количество элементов: "; cin >> n;

	for (int i = 0; i < n; i++)
	{
		qu.Enqueue(rand() % 100);
		cout << qu.peek_back() << tab;
	}
	cout << endl;

	cout << "Size: " << qu.size() << endl;
	cout << "Top element: " << qu.peek_front() << endl;
	cout << "Last element: " << qu.peek_back() << endl;

	cout << "\nRemoving element\n" << endl;
	qu.Dequeue();

	cout << "Size: " << qu.size() << endl;
	cout << "Top element: " << qu.peek_front() << endl;
	cout << "Last element: " << qu.peek_back() << endl;

	cout << qu.isEmpty() << endl;

}