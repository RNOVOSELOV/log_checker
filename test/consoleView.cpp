#include <iostream>
#include "consoleView.h"

ConsoleView::~ConsoleView()
{

}

void ConsoleView::showWelcome(const string input, const string output)
{
	cout << "Welcome to log explorer!\nInput directory: \"" << input << "\"; output directory: \"" + output + "\".\n>>";
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

void ConsoleView::executeCommand(char value)
{
	notifyPresenter(&IViewEvents::onWelcomeKeyPressed, value);
}
