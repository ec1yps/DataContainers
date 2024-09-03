#pragma once
#include "stdafx.h"
#include "Constants.h"

template<typename T> class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	} *Head, * Tail;
	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr);
		~ConstBaseIterator();

		//				Comparison operators:
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;

		//				Dereference operators:
		const T& operator*()const;
	};

public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};

	class ConstReverseIterator : public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();

		//					Incremento/Decremento:
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr);
		~Iterator();

		T& operator*();
	};

	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr);
		~ReverseIterator();

		T& operator*();
	};

	ConstIterator begin()const;
	ConstIterator end()const;

	Iterator begin();
	Iterator end();

	ConstReverseIterator rbegin()const;
	ConstReverseIterator rend()const;

	ReverseIterator rbegin();
	ReverseIterator rend();

	//				Constructors:
	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	List(List<T>&& other)noexcept;
	~List();

	//	Operators:
	List<T>& operator=(const List<T>& other);
	List<T>& operator=(List<T>&& other);

	//	Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int index);

	//	Removing elements:
	void pop_front();
	void pop_back();
	void erase(int index);

	//	Methods:
	void print();
	void reverse_print();
};

template<typename T> List<T> operator+(const List<T>& left, const List<T>& right);
template<typename T> void Grow(List<T>& list);