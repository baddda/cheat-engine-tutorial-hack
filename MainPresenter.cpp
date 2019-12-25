#include "MainPresenter.h"
#include "MainView.h"
#include "ProcessService.h"

void MainPresenter::bind(MainView& view)
{
	this->view = &view;
}

void MainPresenter::start()
{
	view->showText("Which step you want to solve?");
	view->waitForInput();
}

void MainPresenter::handleInput(int input)
{
	bool success = 0;
	ProcessService* processService = ProcessService::getInstance();
	switch (input)
	{
	case 2:
		processService->solveStep2();
	case 3:
		processService->solveStep3();
	case 4:
		processService->solveStep4();
	case 5:
		success = processService->solveStep5();
	case 6:
		processService->solveStep6();
	default:
		break;
	}

	if (success)
	{
		view->showText("Step solved");
	}
	else
	{
		view->showText("Step failed");
	}
	view->waitForInput();
}

