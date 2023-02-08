#pragma once

#include "iview.h"
#include "model.h"

class Presenter:IViewEvents
{
public:
	Presenter(unique_ptr<IView>&, unique_ptr<Model>&);
	virtual ~Presenter();
	virtual void onWelcomeKeyPressed(char value);
	void startAnalyze();
private:
	unique_ptr<IView> view;
	unique_ptr<Model> model;
};

