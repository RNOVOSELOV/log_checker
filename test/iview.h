#pragma once

#include <string>
#include <vector>
#include <filesystem>

#include "iviewEvents.h"
#include "viewEventsNotifier.h"

class IView: public ViewEventsNotifier<IViewEvents>  {
public:
	virtual ~IView() = default;
	virtual void showWelcome(const std::string, const std::string) = 0;
	virtual void showHelp() = 0;
	virtual void showMessage(const std::string) = 0;
	virtual void waitAnotherCommand() = 0;
};
