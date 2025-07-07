#include "StartScreen.h"

StartScreen::StartScreen(int w,int h, const char *title)
    : Fl_Window(w,h,title), mainWindow(nullptr)
{
    color(FL_DARK3);
    box(FL_FLAT_BOX);
    begin();

    Title_box = new Fl_Box(0,h/6,w,h/8,"Ski Safari");
    Title_box->labelsize(FL_NORMAL_SIZE + 15);
    Title_box->labelcolor(FL_WHITE);
    Title_box->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);

    startButton = new Fl_Button(w/2-100,h/2,200,50,"开始游戏");
    startButton->labelsize(FL_NORMAL_SIZE + 5);
    startButton->labelcolor(FL_BLACK);
    startButton->color(FL_WHITE);
    startButton->callback(startButton_cb,this);

    exitButton = new Fl_Button(w / 2 - 100, h / 2 + 70 , 200, 50, "退出游戏");
    exitButton->labelsize(FL_NORMAL_SIZE + 5);
    exitButton->labelcolor(FL_BLACK);
    exitButton->color(FL_WHITE);
    exitButton->callback(exitButton_cb,this);

    end();
    show();
}

StartScreen::~StartScreen(){
}

void StartScreen::startButton_cb(Fl_Widget* w, void *user_data)
{
    StartScreen* self = static_cast<StartScreen*>(user_data);
    if(self && self->mainWindow)
    {
        self->hide();
        self->mainWindow->show();
    }
    else 
    {
        std::cerr << "Error: Main window not set or StartScreen instance is null." << std::endl;
    }
}


void StartScreen::exitButton_cb(Fl_Widget* w, void *user_data)
{
    return ;
}