#include <iostream>
#include <list>
using namespace std;

template <typename T>
void mergesort(list<T>&);

template <typename T>
list<T> divide_from(list<T>&);

template <typename T>
void merge(list<T>&, list<T>&);

template <typename T>
void display(const list<T>&);

int main()
{
	int n;
	cout << "Please enter the number of elements you want to sort: ";
	cin >> n;
	cout << "Please enter the elements:" << endl;
	list<int> a;
	int input;
	for (int i = 0; i < n; i++)
	{
		cin >> input;
		a.push_back(input);
	}
	mergesort(a);
	display(a);
	return 0;
}

template <typename T>
void mergesort(list<T>& head)
{//mergesort the list 'head'
	if (head.size() > 1)					
	{//head has more than one element, halve the list and merge the two half lists after mergesorting each of them
		list<T> second_half = divide_from(head);
		mergesort(head);
		mergesort(second_half);
		merge(head, second_half);
	}
}

template <typename T>
list<T> divide_from(list<T>& head)
{
	list<T> temp;
	list<T>::iterator mid = head.begin();
	list<T>::iterator end = head.begin();
	while (end != head.end() && ++end != head.end())
	{//find the middle position of the list using iterator end to move twice the speed of iterator mid to reach the end of the list
		end++;
		mid++;
	}
	/*following instructions to realize instruction below:	
		temp.splice(temp.begin(), head, mid, head.end()); 
	*/
	while (mid != head.end())
	{//copy the latter part of the list (after mid) to temp and then earse it
		temp.push_back(*mid);
		mid = head.erase(mid);
	}
	return temp;
}

template <typename T>
void merge(list<T>& first, list<T>& second)
{
	/*following instructions to realize instruction below:
		first.merge(second); 
	*/
	list<T>::iterator current1 = first.begin();
	list<T>::iterator current2 = second.begin();
	while (current2 != second.end())
	{//merge the second list to the first one
		while (current1 != first.end() && *current2 > *current1)	// *current1 will cause error if current1 reached at the end of first list so put the two conditions in such order
			current1++;												//find the first position that *current2 should insert to	
		first.insert(current1, *current2);							//accoring to definition of insert(): insert *current2 before current1 and current will not change
		current2++;													//point to next number in the second list waiting to be merged 
	} 
	
}

template <typename T>
void display(const list<T>& head)
{//display the list 'head'
	for (list<int>::const_iterator  current = head.begin(); current != head.end(); current++)
		cout << *current << " ";
	cout << endl;
}