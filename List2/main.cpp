#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------------------\n"

template<typename T> class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
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
		const T& operator*()const
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
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)//Postfix increment
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
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
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}

		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};

	class ReverseIterator : public ConstReverseIterator 
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}

		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
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

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
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
	List(const std::initializer_list<T>& il) :List()
	{
		for (T const* it = il.begin(); it != il.end(); ++it)
			push_back(*it);
	}
	List(const List<T>& other) :List()
	{
		*this = other;
		cout << "LCopyConstructor:\t" << this << endl;
	}
	List(List<T>&& other)noexcept
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
	List<T>& operator=(const List<T>& other)
	{
		if (this == &other) return *this;

		while (Head)
			pop_front();

		/*for (Element* Temp = other.Head; Temp; Temp=Temp->pNext)
			push_back(Temp->Data);*/

		for (int i : other)
			push_back(i);

		cout << "LCopyAssignment:\t" << this << endl;

		return *this;
	}
	List<T>& operator=(List<T>&& other)
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
	void push_front(T Data)
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
	void push_back(T Data)
	{
		if (Head == nullptr && Tail == nullptr)
			Head = Tail = new Element(Data);
		else
		{
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		}
		size++;
	}
	void insert(T Data, int index)
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

template<typename T> List<T> operator+(const List<T>& left, const List<T>& right)
{
	cout << "Operator +:\t" << endl;

	List<T> buffer = left;
	
	for (int i : right)
		buffer.push_back(i);

	return buffer;
}

template<typename T> void Grow(List<T>& list)
{
	for (typename List<T>::Iterator it = list.begin(); it != list.end(); ++it)
		*it *= 10;
}

//#define BASE_CHECK
#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
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
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List<int> list = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89, 144, 233 };

	List<int> list3;// = std::move(list + list2);
	list3 = std::move(list + list2);

	list3.print();

	Grow(list3);

	list3.print();
	//list.reverse_print();

	/*for (int i : list)
		cout << i << tab;

	cout << endl;

	for (List::ConstReverseIterator it = list.rbegin(); it != list.rend(); ++it)
		cout << *it << tab;

	cout << endl;*/
#endif // ITERATORS_CHECK

}