#include "stdafx.h"
#include "Constants.h"
#include "List.h"
#include "List.cpp"

//#define BASE_CHECK
//#define ITERATORS_CHECK
#define DOUBLE_STRING_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	List<int> list;
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
	list3 = list + list2;

	list3.print();

	Grow(list3);

	list3.print();
	//list.reverse_print();

	for (int i : list)
		cout << i << tab;

	cout << endl;

	for (List<int>::ConstReverseIterator it = list.rbegin(); it != list.rend(); ++it)
		cout << *it << tab;

	cout << endl;
#endif // ITERATORS_CHECK

#ifdef DOUBLE_STRING_CHECK
	List<double> list = { 1.5, 2.6, 3.7 };

	List<std::string> list_str = { "string", "list" };
	list_str.print();
	for (double i : list)cout << i << tab; cout << endl;
	for (std::string i : list_str) cout << i << tab; cout << endl;
#endif // DOUBLE_STRING_CHECK

}