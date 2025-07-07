#ifndef __APP_H__
#define __APP_H__

#include "../viewmodel/GameViewModel.h"
#include "../viewmodel/SpiritViewModel.h"
#include "../view/MainWindow.h"
#include "../view/StartScreen.h"

class App {
public:
	App();
	App(const App&) = delete;
	~App() noexcept {}

	App& operator=(const App&) = delete;

	bool initialize();

	void show_main_window() {
		std::cerr << "Show Main Window" << std::endl;
		m_main_wnd.show();
	}

private:
	MainWindow m_main_wnd;
	StartScreen m_start_screen;
	GameViewModel m_game_viewmodel;
	SpiritViewModel m_spirit_viewmodel;
};

#endif