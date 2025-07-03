#include "App.h"

App::App() : m_main_wnd(1200, 700, "Ski Adventure") {}

bool App::initialize(){
	if (!m_spirit_viewmodel.initialize())
		return false;
	//binding

	//properties
	// m_main_wnd.get_board().

	//commands
	m_main_wnd.set_next_step_command(m_game_viewmodel.get_next_step_command());

	//notification
	m_game_viewmodel.add_notification(m_main_wnd.get_notification());

	return true;
}
