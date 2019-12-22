#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include "Util.h"
#include "ProcessService.h"
#include "MainPresenter.h"
#include "MainView.h"

int main()
{
	ProcessService* processService = ProcessService::getInstance();
	processService->attach();

	MainPresenter mainPresenter;
	MainView mainView;
	mainPresenter.bind(mainView);
	mainView.bind(mainPresenter);

	mainPresenter.start();

	return 0;
}
