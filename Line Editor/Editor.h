#ifndef Editor_H
#define Editor_H
#include <string>
#include <list>
using namespace std;

class Editor
{
public:
	Editor();

	/*	If line is legal command, exeute it and return the result. If line is the text to be inserted,
	insert it and return the result. Otherwise,return illegal error code.	 */
	string parse(const string& line);

protected:
	/*	Post condition: Check the validity of line. If there exists no error,
	execute the command and return the result. Otherwise, return the error information.	*/
	string command_check(const string& line);

	/*	Post condition: If line was't too long, insert it into the editor and return an empty line,
	or return the error information.	*/
	string insert_command(const string& line);

	/*	Post condition: Delete the [k]th to the [m]th line if possible,
	or return the error information.	*/
	string delete_command(int k, int m);

	/*	Post condition: Turn the [m]th line into the current line if possible,
	or return the error information.	*/
	string line_command(int m);

	/*	Post condition: Print the [k]th to the [m]th line if possible,
	or return the error information.	*/
	string print_command(int k, int m);

	/*	Post condition: The editor runs to the end and returns the text.	*/
	string done_command();
	list<string> text;
	list<string>::iterator current;
	int currentLineNumber;
	bool inserting;
};//Editor

#endif
