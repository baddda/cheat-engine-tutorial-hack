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
	ProcessService* processService = ProcessService::getInstance();
	processService->solveStep3();
	view->showText("Step solved");
	view->waitForInput();
}

