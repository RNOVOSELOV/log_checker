#pragma once

#include "iview.h"

class ConsoleView :
    public IView
{
public:
    virtual ~ConsoleView();
    virtual void showWelcome(const string, const string);
    virtual void showHelp();
    virtual void waitAnotherCommand();
    virtual void showMessage(const string);

    void executeCommand(char value);
};

