#pragma once
#include "stdafx.h"

#define tab "\t"

template<typename T> class ForwardList
{
	class Element
	{
		T Data;
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
			count--;
		}
		friend class ForwardList;
	} *Head;

	size_t size;
public:
	ForwardList();
	ForwardList(const std::initializer_list<T>& il);
	ForwardList(const ForwardList& other);
	ForwardList(ForwardList&& other)noexcept;
	~ForwardList();

	//	Operators:
	ForwardList<T>& operator=(const ForwardList<T>& other);
	ForwardList<T>& operator=(ForwardList<T>&& other)noexcept;

	class Iterator
	{
		Element* Iter;
	public:
		Iterator(Element* Iter) :Iter(Iter) {}
		~Iterator() {}

		Iterator operator++();
		T& operator*() const;
		bool operator!=(const Iterator& other) const;
	};

	class ConstIterator
	{
		Element* ConstIter;
	public:
		ConstIterator(Element* ConstIter) :ConstIter(ConstIter) {}
		~ConstIterator() {}

		ConstIterator operator++();
		const int operator*() const;
		bool operator!=(const ConstIterator& other) const;
	};

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;

	//	Adding/removing elements:
	void push_front(T Data);
	void push_back(T Data);
	void pop_front();
	void pop_back();
	void insert(T Data, int index);
	void erase(int index);

	//	Methods:
	void reverse();
	void print()const;
};


template<typename T> std::ostream& operator<<(std::ostream& os, const typename ForwardList<T>::Element& el);