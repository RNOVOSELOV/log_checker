#include <iostream>
#include "consoleView.h"
#include "presenter.h"
#include "negativeLogsCheckerModel.h"

int main(int argc, char * argv[])
{
	setlocale(LC_ALL, "Russian");
	unique_ptr<IView> view = make_unique <ConsoleView>();
    if (argc <= 1 || argc > 5)
    {
		view->showMessage("Error! Number of arguments error! Use:\n ./analyser -I [INPUT DIRECTORY] -O [OUTPUT DIRECTORY]\n");
        return 1;
    }

	unique_ptr<Model> model = make_unique<NegativeLogsCheckerModel>();
	for (int i = 1; i < argc; ++i)
	{
		string value = *(argv + i);
		if (value == "-I" && i != argc - 1)
		{
			string directory = *(argv + ++i);
			auto isValid{ model->setInputFilesDirectory(directory) };
			if (!isValid)
			{
				view->showMessage("Error! Input directory not exist.\n");
				return 2;
			}
		}
		else if (value == "-O" && i != argc - 1)
		{
			string directory = *(argv + ++i);
			auto isValid{ model->setOutputFilesDirectory(directory) };
			if (!isValid)
			{
				view->showMessage("Error! Output directory not exist.\n");
				return 3;
			}
		}
		else
		{
			view->showMessage("WARNING! Incorrect option is entered!");
		}
	}

	if (!model->inputDirectoryIsValid())
	{
		view->showMessage("Error! Input directory not exist on filesystem.\n");
		return 4;
	}

	if (!model->outputDirectoryIsValid())
	{
		view->showMessage("Error! Output directory not exist on filesystem.\n");
		return 5;
	}

	cout << "Hello" << endl;
	unique_ptr presenter = make_unique<Presenter>(move(view), move(model));
    presenter->startAnalyze();


	cout << "Hello" << endl;
    return 0;
}
