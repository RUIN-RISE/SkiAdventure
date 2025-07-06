#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include"../common/frame.h"
#include "widgets/GameBoard.h"

class MainWindow :public Fl_Double_Window
{
    public:
    MainWindow(int height,int width, const char* title = nullptr);
    MainWindow(const MainWindow&) = delete;
    ~MainWindow() noexcept;

    MainWindow& operator=(const MainWindow&) = delete;

    //commands
	void set_next_step_command(std::function<void(int)>&& pn) noexcept
	{
        // std::cerr << "Set Next Step Command" << std::endl ;
		m_next_step_command = std::move(pn);
	}
    void set_jump_command(std::function<void()>&& pn) noexcept{
        m_jump_command = std::move(pn);
    }
    void set_start_command(std::function<bool()>&& pn)noexcept{
        m_start_command = std::move(pn);
    }

    PropertyNotification get_notification();
    
    Gameboard& get_board() noexcept
	{
		return board;
	}
    protected:
    //callbacks
	static void timeout_cb(void*);
    int handle(int event) override;

    private:
	Gameboard board;

    private:
    std::function<void(int)> m_next_step_command;
    std::function<void()> m_jump_command;
    std::function<bool()> m_start_command;
};

#endif