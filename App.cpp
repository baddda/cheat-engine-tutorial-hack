#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include "Util.h"
#include "ProcessService.h"
#include "MainPresenter.h"
#include "MainView.h"

/*
TODO
- Add error handling and error logs for all solve step methods.
- Make one method for all the steps that have a similar solution.
*/

int main()
{
	Clog2VisualStudioDebugOutput c2v;

	ProcessService* processService = ProcessService::getInstance();
	if (processService->attach())
	{
		MainPresenter mainPresenter;
		MainView mainView;
		mainPresenter.bind(mainView);
		mainView.bind(mainPresenter);
		mainPresenter.start();
	}
	else {
		std::clog << "Could not attach to process" << std::endl;
	}

	return 0;
}
