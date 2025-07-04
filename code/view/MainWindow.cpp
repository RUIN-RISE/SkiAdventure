#include "../common/property_ids.h"
#include "MainWindow.h"

#define BOARD_X (5)
#define BOARD_Y (5)
#define BOARD_W (width-5-5)
#define BOARD_H (height-50-BOARD_Y)
MainWindow::MainWindow(int height,int width, const char* title)
: Fl_Double_Window(width,height,title),board(BOARD_X,BOARD_Y,BOARD_W,BOARD_H)
{
	std::cerr << "Ctor Of MainWindow" << std::endl ;
	begin();
	add(board);
    end();
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
