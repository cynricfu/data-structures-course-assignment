#include <iostream>
#include <string>
#include "HashTable.h"
using namespace std;

struct examinee
{
	string name, ID;
	int age;
	char gender;
};

int hashFunc(const examinee & x)
{
	int hashVal = 0;
	for (int i = 0; i < x.ID.length(); i++)
		hashVal = 10 * hashVal + x.ID[i];
	return hashVal;
}

int main()
{
	HashTable<examinee> table(hashFunc);
	string line;
	while (true)
	{
		cout << "Please enter a command:" << endl;
		cin >> line;

		if (line == "Insert")
		{
			examinee in;
			cin >> in.name >> in.age >> in.gender >> in.ID;
			cout << (table.insert(in) ? "Succeed" : "Fail") << endl << endl;
		}
		else if (line == "Search")
		{
			examinee in;
			cin >> in.ID;
			table.search(in);
		}
		else if (line == "Remove")
		{
			examinee in;
			cin >> in.ID;
			cout << (table.remove(in) ? "Succeed" : "Fail") << endl << endl;
		}
		else if (line == "Clear")
		{
			table.makeEmpty();
			cout << endl;
		}
		else if (line == "Quit")
			break;
	}
}