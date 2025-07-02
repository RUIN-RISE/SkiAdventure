#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
// #include "GameViewModel.h"
// #include "GameView.h"

#include "widgets/GameBoard.h"

class MainWindow :public F1_Window
{
    public:
    MainWindow(int height,int width, const char* title = nullptr);
    MainWindow(const MainWindow&) = delete;
    ~MainWindow() noexcept;

    MainWindow& operator=(const MainWindow&) = delete;

    //commands
	void set_next_step_command(std::function<void(int)>&& pn) noexcept
	{
		m_next_step_command = std::move(pn);
	}

    PropertyNotification get_notification();
    BattleBoard& get_board() noexcept
	{
		return board;
	}
    protected:
    //callbacks
	static void timeout_cb(void*);

    private:
	GameBoard board;
}