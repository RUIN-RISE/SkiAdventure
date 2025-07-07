#pragma once
#include"GameBoard.h"

class StartScreen : public Fl_Group{
    private:
    typedef Fl_Group BaseClass;

    public:
    StartScreen(int x,int y,int w,int h,const char *l = nullptr);
    ~StartScreen();

    void set_start_image(const std::unique_ptr<Fl_PNG_Image>* p) noexcept
    {
        start_image = p;
    }

    void set_start_game_callback(std::function<void()>&& cb){
        m_start_game_callback = std::move(cb);
    }

    protected:
    void draw() override;

    private :
    static void startButton_cb(Fl_Widget* w, void *user_data);

    static void exitButton_cb(Fl_Widget* w, void *user_data);

    Fl_Button* startButton;
    Fl_Button* exitButton;
    Fl_Box* Title_box;
    const std::unique_ptr<Fl_PNG_Image>* start_image;

    std::function<void()> m_start_game_callback;
};