#include "Editor.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	const string PROMPT = "Please enter a line:   ";
	const string COMMAND_START = "$";
	const string DONE_COMMAND = "$Quit";
	const string CLOSE_WINDOW_PROMPT = "Please press the Enter key to close this output window.";
	Editor editor;
	string result;
	string line;
	do
	{
		cout << PROMPT << endl;
		getline(cin, line);
		result = editor.parse(line);
		if (result.substr(0, 1) == COMMAND_START)
			cout << result.substr(1) << endl << endl;
		else cout << result << endl << endl;
	} while (line != DONE_COMMAND);
	cout << CLOSE_WINDOW_PROMPT;
	cin.get();
	return 0;
}
