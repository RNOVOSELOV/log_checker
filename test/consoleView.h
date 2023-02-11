#pragma once

#include "iview.h"

class ConsoleView final:
    public IView
{
public:
    virtual ~ConsoleView();
    virtual void showWelcome(const std::string, const std::string) override;
    virtual void showHelp() override;
    virtual void waitAnotherCommand() override;
    virtual void showMessage(const std::string) override;
};

