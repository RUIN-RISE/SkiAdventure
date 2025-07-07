#include "app.h"

App::App() : m_main_wnd(700,1200 , "Ski Adventure")
{}

bool App::initialize(){
	if (!m_spirit_viewmodel.initialize())
		return false;
	//binding

	//properties
	
	m_main_wnd.get_board().set_curve(m_game_viewmodel.getVisibleCurve());
    // m_main_wnd.get_board().set_character_position(m_game_viewmodel.getPlayerPosition());
	m_main_wnd.get_board().set_player_instance(m_game_viewmodel.getPlayerInstance());
	m_main_wnd.get_board().set_stone_pos(m_game_viewmodel.getStonePosition());
	m_main_wnd.get_board().set_penguin_on(m_game_viewmodel.getPenguinOn());
	m_main_wnd.get_board().set_slide_pos(m_game_viewmodel.getSlidePosition());
	m_main_wnd.get_board().set_penguin_instance(m_game_viewmodel.getPenguinInstance());

	m_main_wnd.get_board().set_snow(m_spirit_viewmodel.get_snow());
	m_main_wnd.get_board().set_character(m_spirit_viewmodel.get_player());
	m_main_wnd.get_board().set_character_penguin(m_spirit_viewmodel.get_player_penguin());
	m_main_wnd.get_board().set_stone(m_spirit_viewmodel.get_stone());
	m_main_wnd.get_board().set_penguin(m_spirit_viewmodel.get_penguin());
	m_main_wnd.get_board().set_background(m_spirit_viewmodel.get_background());

	m_main_wnd.get_startscreen().set_start_image(m_spirit_viewmodel.get_start_image());

	//commands
	m_main_wnd.set_next_step_command(m_game_viewmodel.get_next_step_command());
	m_main_wnd.set_jump_command(m_game_viewmodel.get_jump_command());
	m_main_wnd.set_start_command(m_game_viewmodel.get_start_command());

	//notification
	m_game_viewmodel.add_notification(m_main_wnd.get_notification());

	//To debug
	// m_main_wnd.get_board().draw();

	return true;
}
