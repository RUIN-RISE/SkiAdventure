#include "../common/property_ids.h"
#include "MainWindow.h"

#define BOARD_X (0)
#define BOARD_Y (0)
#define BOARD_W (width)
#define BOARD_H (height)
MainWindow::MainWindow(int height,int width, const char* title)
: Fl_Double_Window(width,height,title),board(BOARD_X,BOARD_Y,BOARD_W,BOARD_H),
  startscreen(BOARD_X,BOARD_Y,BOARD_W,BOARD_H)
{
	std::cerr << "Ctor Of MainWindow" << std::endl ;
	begin();
	add(startscreen);
    end();

	board.hide();
	startscreen.set_start_game_callback([this]() {
		std::cerr<< "Start Game button pressed!" << std::endl;
		this->startscreen.hide();
		if (!this->find(this->board.window())){
		 this->add(this->board);
		 std::cerr << "GameBoard added to MainWindow." << std::endl;
		}
		this->board.show();

		this->redraw();

	});
    //开始定时器，每秒刷新60次
    Fl::add_timeout(deltaTime, &timeout_cb, this);

}

MainWindow::~MainWindow() noexcept
{

}
//返回一个 Lambda 回调函数，根据 id 判断是否需要更新界面，如果 ID 是 PROP_ID_MAP则重绘
PropertyNotification MainWindow::get_notification()
{
	return [this](uint32_t id)->void
		{
			// std::cerr << id << std::endl;
			switch (id) {
			case PROP_ID_MAP:
				// std::cerr << "Redraw" << std::endl;
				board.redraw();
				break;
			default:
				break;
			}
		};
}

//callbacks

void MainWindow::timeout_cb(void* pv)
{
	MainWindow* pThis = (MainWindow*)pv;
	static int l_turn = 0;
	if (pThis->m_next_step_command != nullptr) {
		pThis->m_next_step_command(l_turn);
		++ l_turn;
	}
	Fl::repeat_timeout(deltaTime, &timeout_cb, pThis);
}

int MainWindow::handle(int event) {
    switch (event) {
        case FL_KEYDOWN: {
			if(m_start_command){
				//游戏结束时只有R键可以重开
				if(m_start_command(Fl::event_key() == 'r')){
					return 1 ;
				}
			}
			// 检查按下的键是否是空格键
            if (Fl::event_key() == ' ') {
				std::cerr << "Read a space" << std::endl ;
                // 确保 ViewModel 已经被设置
                if (m_jump_command) {
					std::cerr << "Execute m_jump_command" << std::endl;
                    // 获取并执行 ViewModel 中的 jump_command
                    m_jump_command(); // 直接调用 std::function
                    return 1; // 返回 1 表示事件已被处理，不再传递给其他 widget
                }
            }
            break;
        }
        // 如果需要处理按键释放或其他事件，可以在这里添加 case FL_KEYUP 等
    }

    // 调用基类的 handle 方法，以便处理其他未被当前 handle 方法处理的事件
    return Fl_Double_Window::handle(event);
}

