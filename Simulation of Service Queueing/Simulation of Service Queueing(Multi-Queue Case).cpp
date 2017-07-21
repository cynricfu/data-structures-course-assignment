#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <Windows.h>
using namespace std;

struct customer
{
	int number;
	int arrivalTime;
	customer(int a, int b)
	{
		number = a;
		arrivalTime = b;
	}
};

bool allNonPositive(const int[]);
int shortestLine(const queue<customer>[]);
void ServiceQueuingSimulation(int);

int main()
{
	int t;
	cout << "Please enter total service time(in hour): ";
	cin >> t;
	cout << "-------------------------------------------" << endl;
	cout << "-------------------------------------------" << endl;
	ServiceQueuingSimulation(t);
	return 0;
}

//The core simulation function
void ServiceQueuingSimulation(int totalTime)
{
	queue<customer> line[5];							//Used to store arrival time of each customer
	int number[5];										//Customer number being served
	int serviceTime[5] = { 0 };							//Serving time left of each customer 
	int serviceCount[5] = { 0 };						//Served customers count of each counter
	int maxNumber = 0;									//Maxnumber waiting in lines 
	int sum[5] = { 0 };									//Sum of all waiting time of each line
	int i = 0;
	srand(time(0));
	//The simulation continues when it's in serving duration or there is someone waiting
	while (i < totalTime * 12 || !allNonPositive(serviceTime))
	{
		//Sevice time has passed one period
		for (int k = 0; k < 5; k++)
			serviceTime[k]--;
		if (i < totalTime * 12)
		{
			int newArrival = rand() % 10 + 1;			//A random number of customers arrive
			int sumLine = 0;
			for (int k = 0; k < 5; k++)
				sumLine += line[k].size();
			//The waiting queue has maximum room of 70 people
			if (newArrival + sumLine > 70)
				newArrival = 70 - sumLine;				
			//Push arrival time and number in shortest line
			for (int k = 0; k < newArrival; k++)
				line[shortestLine(line)].push(customer(++maxNumber, i));
		}
		for (int k = 0; k < 5; k++)
		{
			//if any counter finish serving, pop head of queue to the counter
			if (serviceTime[k] <= 0 && !line[k].empty())
			{
				number[k] = line[k].front().number;
				sum[k] += i - line[k].front().arrivalTime;
				cout << "Please No." << number[k] << " >>> Counter " << k + 1 << "." << endl;
				cout << "Waiting time: " << (i - line[k].front().arrivalTime) * 5 << "mins" << endl << endl;	//5 minutes 1 period
				line[k].pop();
				serviceTime[k] = rand() % 4 + 1;
				serviceCount[k]++;
			}
		}
		for (int k = 0; k < 5; k++)
		{
			if (serviceTime[k] <= 0)
			{
				cout << "Counter " << k + 1 << ": Empty" << " | ";
			}
			else
			{
				cout << "Counter " << k + 1 << ": No." << number[k] << " | ";
			}
		}
		cout << endl;
		cout << "Number of waiting: " << endl;
		for (int k = 0; k < 5; k++)
			cout << "Counter " << k + 1 << ": " << line[k].size() << " | ";
		cout << endl;
		cout << "Estimated waiting time: " << endl;
		for (int k = 0; k < 5; k++)
			cout << "Counter " << k + 1 << ": " << (serviceCount[k] == 0 ? 0 : (sum[k] * 5 / serviceCount[k])) << " mins | ";
		cout << endl;
		cout << "-------------------------------------------" << endl;
		i++;
		Sleep(2500);								  //2.5s delay for seeing simulation result
	}
	cout << "-------------------------------------------" << endl;
	cout << "Average waiting time: " << endl;
	for (int k = 0; k < 5; k++)
	{
		int min = sum[k] * 5 / serviceCount[k];
		int sec = ceil(((float)sum[k] * 5 / serviceCount[k] - min) * 60);
		cout << "Counter " << k + 1 << ": " << min << " mins " << sec << " secs" << endl;
	}
	cout << "Service count:" << endl;
	for (int k = 0; k < 5; k++)
		cout << "Counter " << k + 1 << ": " << serviceCount[k] << " | ";
	cout << endl;
}

//Determine whether there is someone getting service or not
bool allNonPositive(const int serviceTime[])
{
	for (int i = 0; i < 5; i++)
	{
		if (serviceTime[i] > 0)
			return false;
	}
	return true;
}

//Return the index number of the shortest line
int shortestLine(const queue<customer> line[])
{
	int min = line[0].size();
	int index = 0;
	for (int i = 1; i < 5; i++)
	{
		if (line[i].size() < min)
		{
			min = line[i].size();
			index = i;
		}
	}
	return index;
}
