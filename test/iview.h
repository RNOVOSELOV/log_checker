#pragma once

#include <string>
#include <vector>
#include <filesystem>

#include "iviewEvents.h"
#include "viewEventsNotifier.h"

using namespace std;

class IView: public ViewEventsNotifier<IViewEvents>  {
public:
	virtual ~IView() = default;
	virtual void showWelcome(const string, const string) = 0;
	virtual void showHelp() = 0;
	virtual void showMessage(const string) = 0;
	virtual void waitAnotherCommand() = 0;
};
