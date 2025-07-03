#include "GameBoard.h"

#define BOX_PLANE_X  (x + 10)
#define BOX_PLANE_Y  (y + 10)
#define BOX_PLANE_W  (90)
#define BOX_PLANE_H  (90)

Gameboard::Gameboard(int x, int y, int w, int h, const char *l): 
    BaseClass(x,w,y,h,l),
	m_character(BOX_PLANE_X, BOX_PLANE_Y, BOX_PLANE_W, BOX_PLANE_H)
{
    end();

    box(FL_NO_BOX);

    m_character.box(FL_NO_BOX);
    character = nullptr;
    snow = nullptr;

}

Gameboard::~Gameboard() noexcept
{

}

void Gameboard::draw(){

    fl_rectf(x(),y(),w(),h(),FL_CYAN);

    if(!terrain_line.empty() && snow && *snow)
    {
        fl_begin_polygon();

        for(const auto& point : terrain_line)
        {
            fl_vertex(x() + point.x, y() + point.y);
        }

        fl_vertex(x()+w(),y()+h());
        fl_vertex(x(),y()+h());
        fl_vertex(x(),y()+terrain_line.front().y);

        fl_end_polygon();

        fl_push_clip(x(),y(),w(),h());
        for(int ypos = y() ; ypos < y() +h() ; ypos += (*snow)-> h())
        {
            for(int xpos = x() ; xpos < x() +w() ; xpos += (*snow)-> w()){
                (*snow)->draw(xpos,ypos);
            }
        }
        fl_pop_clip();
    }
    
    int centerX = x() + w()/2 ;
    int centerY = y() + h()/2 ;
    m_character.position(centerX,centerY);

    if(character && *character)
    {
        int charX = centerX - (*character)->w()/2;
        int charY = centerY - (*character)->w()/2;
        (*character)->draw(charX,charY);
    }
}