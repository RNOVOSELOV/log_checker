#pragma once

#include "iview.h"

class ConsoleView :
    public IView
{
public:
    virtual ~ConsoleView();
    virtual void showWelcome(const std::string, const std::string);
    virtual void showHelp();
    virtual void waitAnotherCommand();
    virtual void showMessage(const std::string);

    void executeCommand(char value);
};

