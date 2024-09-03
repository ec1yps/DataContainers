#include "stdafx.h"
#include "ForwardList.h"
#include "ForwardList.cpp"

//#define BASE_CHECK
//#define PERFOMANCE_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	//Element element(5);
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	ForwardList<int> list;
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

#ifdef PERFOMANCE_CHECK
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

	//ForwardList list2 = list;
	ForwardList list2 = std::move(list);
	//ForwardList list2;
	//list2 = list;
	//list2 = std::move(list);
	list2.print();
#endif // PERFOMANCE_CHECK


#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21, 34, 55, 89, 144 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;

	Print(arr);
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList<int> list = {3, 5, 8, 13, 21};

	//list.print();
	
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST
}