#include <iostream>
#include "consoleView.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

ConsoleView::~ConsoleView()
{

}

void ConsoleView::showWelcome(const string input, const string output)
{
	cout << "Welcome to log explorer!\nInput directory: \"" << input << "\"; output directory: \"" + output + "\".\n\n>>";
	showHelp();
}

void ConsoleView::showHelp()
{
	cout << "Enter \'s\' for start scan, \'c\' for clean output directory, \'h\' for this help or \'q\' for quit.\n>>";
	char value;
	cin >> value;
	executeCommand(value);
}

void ConsoleView::waitAnotherCommand()
{
	cout << ">>";
	char value;
	cin >> value;
	executeCommand(value);
}

void ConsoleView::showMessage(const string message)
{
	cout << message << endl;
}
