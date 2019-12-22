#include "MainView.h"
#include "MainPresenter.h"

void MainView::bind(MainPresenter& presenter)
{
	this->presenter = &presenter;
}

void MainView::showText(std::string text)
{
	std::cout << text << std::endl;
}


void MainView::waitForInput()
{

	getchar();
	presenter->handleInput();
}
