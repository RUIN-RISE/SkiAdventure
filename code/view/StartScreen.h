#pragma once

#include"MainWindow.h"
#include<memory>

class StartScreen : public Fl_Window{
    public:
    StartScreen(int w,int h,const char* title);
    ~StartScreen();

    void setMainWindow(MainWindow *main_win)
    {
        mainWindow = main_win;
    }

    void set_start_image(const std::unique_ptr<Fl_PNG_Image>* p) noexcept
    {
        start_image = p;
    }

    private :
    static void startButton_cb(Fl_Widget* w, void *user_data);

    static void exitButton_cb(Fl_Widget* w, void *user_data);

    Fl_Button* startButton;
    Fl_Button* exitButton;
    Fl_Box* Title_box;
    const std::unique_ptr<Fl_PNG_Image>* start_image;

    MainWindow* mainWindow;

};