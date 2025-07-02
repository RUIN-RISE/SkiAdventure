#include "../viewmodel/GameViewModel.h"

#include "../view/MainWindow.h"

class App {
public:
	App();
	App(const App&) = delete;
	~App() noexcept
	{
	}

	App& operator=(const App&) = delete;

	bool initialize();

	void show_main_window()
	{
		m_main_wnd.show();
	}

private:
	MainWindow m_main_wnd;
	GameViewModel m_game_viewmodel;
};