#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <Windows.h>
using namespace std;

bool allNonPositive(const int[]);
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
	queue<int> line;									//Used to store arrival time of each customer
	int number[5];										//Customer number being served
	int serviceTime[5] = {0};							//Serving time left of each customer
	int serviceCount[5] = {0};							//Served customers count of each counter
	int maxNumber = 0;									//Maxnumber being served
	int sum = 0;										//Sum of all waiting time
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
			//The waiting queue has maximum room of 70 people
			if (newArrival + line.size() > 70)
				newArrival = 70 - line.size();
			//Store the arrival time in queue
			for (int k = 0; k < newArrival; k++)
				line.push(i);
		}
		for (int k = 0; k < 5; k++)
		{
			//If any counter finish serving, pop head of queue to the counter
			if (serviceTime[k] <= 0 && !line.empty())
			{
				maxNumber++;								
				number[k] = maxNumber;
				sum += i - line.front();
				cout << "Please No." << maxNumber << " >>> Counter " << k + 1 << "." << endl;	
				cout << "Waiting time: " << (i - line.front()) * 5 << "mins" << endl << endl;	//5 minutes 1 period
				line.pop();
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
		cout << "Number of waiting: " << line.size() << endl;
		cout << "Estimated waiting time: " << sum * 5 / maxNumber << " mins" << endl;
		cout << "Next number: No." << maxNumber + 1 << endl;
		cout << "-------------------------------------------" << endl;
		i++;
		Sleep(2500);								  //2.5s delay for seeing simulation result
	}
	cout << "-------------------------------------------" << endl;
	int min = sum * 5 / maxNumber;
	int sec = ceil(((float)sum * 5 / maxNumber - min) * 60);
	cout << "Average waiting time: " << min << " mins " << sec << " secs" << endl << endl << "Service count:" << endl;
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
