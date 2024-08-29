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
	} *Head, *Tail;
	size_t size;
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}
		Iterator& operator++()	//Prefix increment
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)//Postfix increment
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		//				Comparison operators:
		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}

		//				Dereference operators:
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};

	class ReverseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "RItConstructor:\t" << this << endl;
		}
		~ReverseIterator()
		{
			cout << "RItDestructor:\t" << this << endl;
		}

		//					Incremento/Decremento:
		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		//			Comparison operators:
		bool operator==(const ReverseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		//			Dereference operators:
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	Iterator begin() const
	{
		return Head;
	}
	Iterator end() const
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

		/*for (Element* Temp = other.Head; Temp; Temp=Temp->pNext)
			push_back(Temp->Data);*/

		for (int i : other)
			push_back(i);

		cout << "LCopyAssignment:\t" << this << endl;

		return *this;
	}
	List& operator=(List&& other)
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
};

List operator+(const List& left, const List& right)
{
	cout << "Operator +:\t" << endl;

	List buffer = left;
	
	for (int i : right)
		buffer.push_back(i);

	return buffer;
}

//#define BASE_CHECK

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

	List list = { 3, 5, 8, 13, 21 };
	List list2 = { 34, 55, 89, 144, 233 };

	List list3;// = std::move(list + list2);
	list3 = std::move(list + list2);

	list3.print();
	//list.reverse_print();

	/*for (int i : list)
		cout << i << tab; 

	cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
		cout << *it << tab;

	cout << endl;*/
}