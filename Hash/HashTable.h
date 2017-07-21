#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

template <class HashedObj>
class HashTable
{
public:
	HashTable(int(*h)(const HashedObj & x)) : hash(h) {}
	void search(const HashedObj & x)
	{
		int i = 0;
		int hashVal,hashValue = hash(x);
		while (i < 10007 && occupied[hashVal])
		{
			if (theArray[hashVal].ID == x.ID && !deleted[hashVal])
			{
				cout << theArray[hashVal].name << ' ' << theArray[hashVal].age << ' ' << theArray[hashVal].gender << ' ' << theArray[hashVal].ID << endl << endl;
				return;
			}
		i++;
		hashVal = (hashValue + i) % 10007;
		}
		cout << "Not found" << endl << endl;
	}

	void makeEmpty()
	{
		for (int i = 0; i < 10007; i++)
		{
				occupied[i] = false;
				deleted[i] = false;
		} 
	}

	bool insert(const HashedObj & x)
		//Insert key x  if x is not in the table and return true. Otherwise, return false and do nothing. 
	{
		//insert here.      You use myhash to compute hash addresses.    
		if (full)
			return false;
		int i, hashVal;
		int hashValue = hash(x);
		for (i = 0; i < 10007; i++)
		{
			hashVal = (hashValue + i) % 10007;
			if (!occupied[hashVal] || deleted[hashVal])
			{
				theArray[hashVal].name = x.name;
				theArray[hashVal].age = x.age;
				theArray[hashVal].gender = x.gender;
				theArray[hashVal].ID = x.ID;
				occupied[hashVal] = true;
				deleted[hashVal] = false;
				return true;
			}
			else if (theArray[hashVal].ID == x.ID)
					return false;
		}
		if (i == 10007)
		{
			full = true;
			return false;
		}
	}

	bool remove(const HashedObj & x)
		//If x is present in the table, remove it and return true. Otherwise, return false. 
	{
		//insert here.         You  use myhash to compute hash addresses.    
		int i = 0;
		int hashVal,hashValue = hash(x);
		while (i < 10007 && occupied[hashVal])
		{
		 	if (theArray[hashVal].ID == x.ID && !deleted[hashVal])
			{
				deleted[hashVal] = true;
				return true;
			}
		i++;
		hashVal = (hashValue + i) % 10007;	
		}
		return false;
	}

private:
	HashedObj theArray[10007];   // The array of Lists
	bool occupied[10007] = { false };
	bool deleted[10007] = { false };
	bool full = false;
	int(*hash)(const HashedObj & x); //hash function
	
	/*bool contains(const HashedObj & x, int i) const
	{
		int hashValue = (hash(x) + i) % 10007;
		if (theArray[hashVal].ID == x.ID && !deleted[hashVal])
			return true;
		return false; 
	}*/
};
#endif
