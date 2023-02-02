#include "presenter.h"
#include "consoleView.h"
#include <iostream>

Presenter::Presenter(shared_ptr<IView> view, shared_ptr<Model> model)
	:	view(view),
		model (model)
{
	this->view->setListener(this);
}

Presenter::~Presenter()
{
	view->eraseListener();
}

void Presenter::startAnalyze()
{
	this->view->showWelcome(this->model->getInputDirectoryName(), this->model->getOutputDirectoryName());
}

void Presenter::onWelcomeKeyPressed(char value)
{
	if (value == 'S' || value == 's')
	{
		int count = model->startScan();
		view->showMessage("Scan finished." + std::to_string(count) + " error messages found.");
		view->waitAnotherCommand();
	}
	else if (value == 'c' || value == 'C')
	{
		if (model->cleanOutput())
		{
			view->showMessage("Output directory empty.");
		}
		else
		{
			view->showMessage("Error clear output directory.");
		}
		view->waitAnotherCommand();
	}
	else if (value == 'q' || value == 'Q')
	{
	}
	else if (value == 'h' || value == 'H')
	{
		view->showHelp();
	}
	else
	{
		view->showMessage("Unrecognized command!");
		view->waitAnotherCommand();
	}
}
