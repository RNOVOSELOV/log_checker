#pragma once

#include "iview.h"
#include "model.h"

class Presenter:IViewEvents
{
public:
	Presenter(std::unique_ptr<IView>&, std::unique_ptr<Model>&);
	virtual ~Presenter();
	virtual void onWelcomeKeyPressed(char value);
	void startAnalyze();
private:
	std::unique_ptr<IView> view;
	std::unique_ptr<Model> model;
};

