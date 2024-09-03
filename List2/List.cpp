#include "List.h"

//	class Element
template <typename T> List<T>::Element::Element(T Data, List<T>::Element* pNext, List<T>::Element* pPrev) :Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
}
template <typename T> List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
}

//	class ConstBaseIterator
template <typename T> List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) :Temp(Temp) {}
template <typename T> List<T>::ConstBaseIterator::~ConstBaseIterator() {}

template <typename T> bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template <typename T> bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}

template <typename T> const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}

//	class ConstIterator
template<typename T> List<T>::ConstIterator::ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
{
	cout << "ItConstructor:\t" << this << endl;
}
template<typename T> List<T>::ConstIterator::~ConstIterator()
{
	cout << "ItDestructor:\t" << this << endl;
}
template<typename T>typename List<T>::ConstIterator::ConstIterator& List<T>::ConstIterator::operator++()	//Prefix increment
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator::ConstIterator List<T>::ConstIterator::operator++(int)//Postfix increment
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

// class ConstReverseIterator
template<typename T> List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
{
	cout << "RItConstructor:\t" << this << endl;
}
template<typename T> List<T>::ConstReverseIterator::~ConstReverseIterator()
{
	cout << "RItDestructor:\t" << this << endl;
}

template<typename T>typename List<T>::ConstReverseIterator::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverseIterator::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

//	class Iterator
template<typename T> List<T>::Iterator::Iterator(Element* Temp) :ConstIterator(Temp) {}
template<typename T> List<T>::Iterator::~Iterator() {}

template<typename T> T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

//	class ReverseIterator
template<typename T> List<T>::ReverseIterator::ReverseIterator(Element* Temp) :ConstReverseIterator(Temp) {}
template<typename T> List<T>::ReverseIterator::~ReverseIterator() {}

template<typename T> T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}


template<typename T>typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}

template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}

template<typename T>typename List<T>::ConstReverseIterator List<T>::rbegin()const
{
	return Tail;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rend()const
{
	return nullptr;
}

template<typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

template<typename T> List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T> List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
		push_back(*it);
}
template<typename T> List<T>::List(const List<T>& other) : List()
{
	*this = other;
	cout << "LCopyConstructor:\t" << this << endl;
}
template<typename T> List<T>::List(List<T>&& other)noexcept
{
	*this = std::move(other);

	cout << "LMoveConstructor:\t" << this << endl;
}
template<typename T> List<T>::~List()
{
	//while (Head) pop_front();
	while (Head) pop_back();

	cout << "LDestructor:\t" << this << endl;
}

//	Operators:
template<typename T> List<T>& List<T>::operator=(const List<T>& other)
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
template<typename T> List<T>& List<T>::operator=(List<T>&& other)
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
template<typename T> void List<T>::push_front(T Data)
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
template<typename T> void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
		Head = Tail = new Element(Data);
	else
	{
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	}
	size++;
}
template<typename T> void List<T>::insert(T Data, int index)
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
template<typename T> void List<T>::pop_front()
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
template<typename T> void List<T>::pop_back()
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
template<typename T> void List<T>::erase(int index)
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
template<typename T> void List<T>::print()
{
	cout << delimiter << endl;

	cout << "Head:\t" << Head << endl;

	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

	cout << "Tail:\t" << Tail << endl;
	cout << "Количество элементов списка: " << size << endl;

	cout << delimiter << endl;
}
template<typename T> void List<T>::reverse_print()
{
	cout << delimiter << endl;

	cout << "Tail:\t" << Tail << endl;

	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

	cout << "Head:\t" << Head << endl;
	cout << "Количество элементов списка: " << size << endl;

	cout << delimiter << endl;
}



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