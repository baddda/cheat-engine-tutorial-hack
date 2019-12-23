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
	int input = 0;
	std::cin >> input;
	presenter->handleInput(input);
}
