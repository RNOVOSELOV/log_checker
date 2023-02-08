#include "presenter.h"
#include "consoleView.h"
#include <iostream>

Presenter::Presenter(unique_ptr<IView>& view, unique_ptr<Model>& model)
	:	view(std::move(view)),
		model (std::move(model))
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
		view->showMessage("Scan finished. " + std::to_string(count) + " error messages are copied.");
		view->waitAnotherCommand();
	}
	else if (value == 'c' || value == 'C')
	{
		if (model->cleanOutput())
		{
			view->showMessage("Output directory is removed.");
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
		view->showHelp();
	}
}
