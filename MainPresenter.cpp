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
	ProcessService* processService = ProcessService::getInstance();
	switch (input)
	{
	case 2:
		processService->solveStep2();
	case 3:
		processService->solveStep3();
	case 4:
		processService->solveStep4();
	default:
		break;
	}

	view->showText("Step solved");
	view->waitForInput();
}

