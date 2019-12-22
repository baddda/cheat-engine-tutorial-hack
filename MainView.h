#ifndef MAIN_PRESENTER_H
#define MAIN_PRESENTER_H
#include <iostream>

class MainPresenter;

class MainView
{
private:
	MainPresenter* presenter;

public:
	MainView() {}

	void bind(MainPresenter& presenter);
	void showText(std::string);
	void waitForInput();
};

#endif MAIN_PRESENTER_H