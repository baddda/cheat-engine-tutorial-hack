#include "MainPresenter.h"
#include "MainView.h"
#include "ProcessService.h"

void MainPresenter::bind(MainView& view)
{
	this->view = &view;
}

void MainPresenter::start()
{
	view->showText("Press a enter to start...");
	view->waitForInput();
}

void MainPresenter::handleInput()
{
	view->showText("Solving step");
	ProcessService* processService = ProcessService::getInstance();
	processService->solveStep2();
	view->waitForInput();
}

