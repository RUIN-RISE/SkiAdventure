#include "StartScreen.h"

StartScreen::StartScreen(int x,int y,int w,int h, const char *title)
    : BaseClass(x,y,w,h,title),
        startButton(nullptr),
        exitButton(nullptr),
        Title_box(nullptr),
        start_image(nullptr)
{
    show();

    Title_box = new Fl_Box(0,h/6,w,h/8,"Ski Adventure");
    Title_box->labelsize(FL_NORMAL_SIZE + 60);
    Title_box->labelfont(FL_HELVETICA_ITALIC);
    Title_box->labelcolor(FL_WHITE);
    Title_box->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);

    startButton = new Fl_Button(w/2-100,h/2,200,50,"Start game");
    startButton->labelsize(FL_NORMAL_SIZE + 5);
    startButton->labelcolor(FL_BLACK);
    startButton->color(FL_WHITE);
    startButton->callback(startButton_cb,this);

    exitButton = new Fl_Button(w / 2 - 100, h / 2 + 70 , 200, 50, "Exit game");
    exitButton->labelsize(FL_NORMAL_SIZE + 5);
    exitButton->labelcolor(FL_BLACK);
    exitButton->color(FL_WHITE);
    exitButton->callback(exitButton_cb,this);

    end();
}

StartScreen::~StartScreen(){
    delete Title_box;
    delete startButton;
    delete exitButton;
}

void StartScreen::draw(){
    if(start_image && start_image->get()){
        start_image->get()->draw(0,0,w(),h());
    }  else {
        fl_color(FL_DARK_BLUE);
        fl_rectf(0,0,w(),h());
    }

    Fl_Group::draw();
}

void StartScreen::startButton_cb(Fl_Widget* w, void *user_data)
{
    StartScreen* screen = static_cast<StartScreen*>(user_data);
    if( screen && screen -> m_start_game_callback){
        screen -> m_start_game_callback();
    }
}


void StartScreen::exitButton_cb(Fl_Widget* w, void *user_data)
{
    Fl::delete_widget(w);
    exit(0);
}