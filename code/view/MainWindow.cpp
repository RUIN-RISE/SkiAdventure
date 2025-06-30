#include "../common/property_ids.h"

#include"MainWindow.h"

#define BOARD_X (5)
#define BOARD_Y (5)
//#define BOARD_W (w-5-5)
//#define BOARD_H (h-50-BOARD_Y)
MainWindow::MainWindow(int height,int width, const char* title): F1_Double_Window(w,h,title),m_board(BOARD_X,BOARD_Y)
{
    end();
    //开始定时器，每秒刷新10次
    Fl::add_timeout(1.0 / 10.0, TimerCallback, this);

}

MainWindow::~MainWindow() noexcept
{

}
//返回一个 Lambda 回调函数，根据 id 判断是否需要更新界面，如果 ID 是 PROP_ID_MAP则重绘
PropertyNotification MainWindow::get_notification()
{
	return [this](uint32_t id)->void
		{
			switch (id) {
			case PROP_ID_MAP:
				m_board.redraw();
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
	Fl::repeat_timeout(0.2, &timeout_cb, pThis);
}
