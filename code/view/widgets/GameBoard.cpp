#include "GameBoard.h"

#define BOX_PLANE_X  (x + 10)
#define BOX_PLANE_Y  (y + 10)
#define BOX_PLANE_W  (90)
#define BOX_PLANE_H  (90)

Gameboard::Gameboard(int x, int y, int w, int h, const char *l): 
    BaseClass(x,w,y,h,l),
	m_character(BOX_PLANE_X, BOX_PLANE_Y, BOX_PLANE_W, BOX_PLANE_H),
    map_width(w),
    map_height(h)
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

std::vector<Vector> Gameboard::get_terrain()
{
    std::vector<Vector> points;

    if (!game_curve) {
        terrain_line.clear();
        return points;
    }

    terrain_line.clear();

    const double screen_width = w();
    const double screen_height = h();

    const double view_left = character_position.x - 0.5*screen_width;
    const double view_right = character_position.x + 0.5*screen_width;
    const double view_top = character_position.y - 0.5*screen_height;
    const double view_bottom = character_position.y + 0.5*screen_height;

    const int num_points = 20;
    const double step = (view_right - view_left) / (num_points - 1);

    for (int i = 0; i < num_points; ++i) {
        double x = view_left + i * step;
        double y = game_curve->evaluate(x);
        points.emplace_back(x, y);
    }
    
}

Vector Gameboard::logic_to_screen(const Vector& logic_pos, 
                                 double view_left, double view_top) const
{
    Vector screen_pos;
    screen_pos.x = logic_pos.x - view_left;
    screen_pos.y = logic_pos.y - view_top;
    return screen_pos;
}

void Gameboard::draw()
{
   const double screen_width = w();
    const double screen_height = h();

    const double view_left = character_position.x - 0.5*screen_width;
    const double view_right = character_position.x + 0.5*screen_width;
    const double view_top = character_position.y - 0.5*screen_height;
    const double view_bottom = character_position.y + 0.5*screen_height;
    fl_rectf(x(),y(),w(),h(),FL_CYAN);
    std::vector<Vector> terrain_line = get_terrain();
    if(!terrain_line.empty() && snow && *snow)
    {
        fl_begin_polygon();

        for(const auto& point : terrain_line)
        {
            Vector screen_point = logic_to_screen(point,view_left,view_right);
            fl_vertex(x() + screen_point.x, y() + screen_point.y);
        }

        fl_vertex(x()+w(),y()+h());
        fl_vertex(x(),y()+h());

        fl_end_polygon();

        fl_push_clip(x(),y(),w(),h());
        for(int ypos = y() ; ypos < y() +h() ; ypos += (*snow)-> h())
        {
            for(int xpos = x() ; xpos < x() +w() ; xpos += (*snow)-> w()){
                (*snow)->draw(xpos,ypos);
            }
        }
        fl_pop_clip();

    fl_color(FL_BLACK);
        fl_begin_line();
        for(const auto& point : terrain_line)
        {
            Vector screen_point = logic_to_screen(point,view_left,view_right);
            fl_vertex(x() + screen_point.x, y() + screen_point.y);
        }
        fl_end_line();
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