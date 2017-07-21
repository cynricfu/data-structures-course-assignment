#include "Editor.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>
using namespace std;

const string COMMAND_START = "$";
	
	//Default constructor.
	Editor::Editor()
	{
		currentLineNumber = -1; //-1 indicates that the text is empty.
		inserting = false;
	}

	//Used to receive entered line.
	string Editor::parse(const string& line)
	{
		if (line == "$Quit")
			return "";
		else if (line.substr(0, 1) == COMMAND_START)
			return command_check(line.substr(1));
		else if (inserting)
			return insert_command(line);
		else
			return "***Error: The line entered is invalid.";
	}

	//Check which command it is.
	string Editor::command_check(const string& line) {
		if (line == "Insert")
		{
			inserting = true;
			return "";
		}
		else if (line.substr(0, 6) == "Delete")
		{
			if (line.find('.') != string::npos)
				return "***Error: The command is not followed by two integers.";
			int spaceIndex = line.find_last_of(' ');
			return delete_command(atoi(line.substr(7, spaceIndex - 7).c_str()), atoi(line.substr(spaceIndex + 1).c_str()));
		}
		else if (line.substr(0, 4) == "Line")
		{
			if (line.find('.') != string::npos)
				return "***Error: The command is not followed by an integer.";
			return line_command(atoi(line.substr(5).c_str()));
		}
		else if (line.substr(0, 5) == "Print")
		{
			if (line.find('.') != string::npos)
				return "***Error: The command is not followed by two integers.";
			int spaceIndex = line.find_last_of(' ');
			return print_command(atoi(line.substr(6, spaceIndex - 6).c_str()), atoi(line.substr(spaceIndex + 1).c_str()));
		}
		else if (line == "Done")
		{
			inserting = false;
			if (text.empty())
				return "";
			return done_command();
		}
		else
			return "***Error: Invalid command.";
	}

	//Insert entered line text.
	string Editor::insert_command(const string& line) {
		if (line.size() > 80)
			return "***Error: The line to be inserted is too long (over 80 letters).";
		else
		{//difference of iterator position of push_back() and insert() 
			if (currentLineNumber == -1)
			{
				text.push_back(line);
				current = text.begin();
			}
			else if (currentLineNumber == text.size() - 1)
			{
				text.push_back(line);
				current++;
			}
			else
				current = text.insert(++current, line);//insert() returns the iterator points at position inserted
			currentLineNumber++;
		}
		return "\n";
	}

	//Delete the kth to the mth line. 
	string Editor::delete_command(int k, int m) {
		if (k > m)
			return "***Error: The first line number > the second.";
		else if (k < 0)
			return "***Error: The first line number < 0.";
		else if (m > text.size() - 1)
			return "***Error: The second line number > the last line number.";
		else
		{//difference of currenLineNumber in [k,m] or not
			inserting = false;
			list<string>::iterator itr = text.begin();
			if (currentLineNumber > k - 1 && currentLineNumber < m + 1)
			{
				if (k == 0)
				{
					for (int i = k; i < m + 1; i++)
						itr = text.erase(itr);//erase() returns the iterator points position of the one after the earsed one 
					currentLineNumber = 0;
					current = text.begin();
				}
				else
				{
					for (int i = 0; i < k; i++)
					{
						if (i == k - 1)
							current = itr;
						itr++;
					}
					for (int i = k; i < m + 1; i++)
						itr = text.erase(itr);//same idea of iterator operation
					currentLineNumber = k - 1;
				}
			}
			else
			{
				for (int i = 0; i < k; i++)
					itr++;
				for (int i = k; i < m + 1; i++)
					itr = text.erase(itr);//same idea
				if (currentLineNumber > m)
					currentLineNumber -= m - k + 1;
			}
			return "";
		}
	}

	//Change the current line to the mth line.
	string Editor::line_command(int m) {
		if (m < 0)
			return "***Error: The desired line number < 0.";
		else if (m > text.size() - 1)
			return "***Error: The desired line number > the last line number.";
		else
		{
			inserting = false;
			currentLineNumber = m;
			current = text.begin();
			for (int i = 0; i < m; i++)
				current++;
			return "";
		}
	}

	//Print the kth to the mth line.
	string Editor::print_command(int k, int m) {
		if (k > m)
			return "***Error: The first line number > the second.";
		else if (k < 0)
			return "***Error: The first line number < 0.";
		else if (m > text.size() - 1)
			return "***Error: The second line number > the last line number.";
		else
		{
			inserting = false;
			list<string>::iterator itr = text.begin();
			for (int i = 0; i < k; i++)
				itr++;
			for (int i = k; i < m + 1; i++)
			{
				cout << (i == currentLineNumber ? '>' : ' ') << i << ' ' << *itr;
				if (i != m)
					cout << endl;
				itr++;
			}
			return "";
		}
	}

	//End edit, print all the lines.
	string Editor::done_command() {
		cout << "Here is the final text:" << endl << endl;
		return print_command(0, text.size() - 1);
	}
