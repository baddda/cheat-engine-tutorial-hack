#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

class MainView;

class MainPresenter
{
private:
	MainView* view;

public:
	MainPresenter() {}
	void bind(MainView& view);
	void start();
	void handleInput();
};

#endif