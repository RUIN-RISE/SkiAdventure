#include "GameBoard.h"

Gameboard::Gameboard(int x, int y, int w, int h, const char *l): 
    // BaseClass(x,w,y,h,l),
    BaseClass(x,y,w,h,l),
	// m_character(BOX_PLANE_X, BOX_PLANE_Y, BOX_PLANE_W, BOX_PLANE_H),
    // m_character(x+w/2,y+h/2,75,75,nullptr),
    map_width(w),
    map_height(h)

{

    // std::cerr << "Gameboard Created" << std::endl;
    // std::cerr << x << ' ' << y << ' ' << w << ' ' << h << ' ' << std::endl;
    end();

    box(FL_NO_BOX);

    // m_character.box(FL_NO_BOX);
    character = nullptr;
    snow = nullptr;
    background = nullptr;
    m_img_stone = nullptr;
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

    double ch_x = character->getPosition().x;
    double ch_y = character->getPosition().y;

    const double view_left = ch_x - 0.5*screen_width;
    const double view_right = ch_x + 0.5*screen_width;
    const double view_top = ch_y + 0.5*screen_height;
    const double view_bottom = ch_y - 0.5*screen_height;

    const int num_points = 50;
    const double step = (view_right - view_left) / (num_points - 1);

    for (int i = 0; i < num_points; ++i) {
        double x = view_left + i * step;
        double y = game_curve->evaluate(x);
        points.emplace_back(x, y);
        // std::cerr << "logic x : " << x << ",y : " << y << std::endl ;
    }
    return points;
}

Vector Gameboard::logic_to_screen(const Vector& logic_pos, 
                                 double view_left, double view_top) const
{
    Vector screen_pos;
    screen_pos.x = logic_pos.x - view_left;
    screen_pos.y = - (logic_pos.y - view_top);
    return screen_pos;
}

//use screen pos of center to draw an img
void draw_img(int centerX,int centerY,const std::unique_ptr<Fl_PNG_Image> * m_img){
    if(m_img && *m_img)
    {
        int charX = centerX - (*m_img)->w()/2;
        int charY = centerY - (*m_img)->h()/2;
        (*m_img)->draw(charX,charY);
    }
}

#define pl_show (*penguin_on?m_character_penguin:m_character)
#define pl_hide (*penguin_on?m_character:m_character_penguin)

void Gameboard::draw()
{
    //To debug
    //std::cerr << "Drawing" << std::endl ;
    // fl_rectf(x(), y(), w(), h(), FL_RED);
    // return ;
    double ch_x = character->getPosition().x;
    double ch_y = character->getPosition().y;

    const double screen_width = w();
    const double screen_height = h();

    const double view_left = ch_x - 0.5*screen_width;
    const double view_right = ch_x + 0.5*screen_width;
    const double view_top = ch_y + 0.5*screen_height;
    const double view_bottom = ch_y - 0.5*screen_height;
    if (background){
        //std::cerr << "Background good." << std::endl ;
        (*background)->draw(x(), y(), w(), h());
        //std::cerr << "Draw end." << std::endl ;
    }
    else{
    fl_rectf(x(),y(),w(),h(),FL_CYAN);
    }
    std::vector<Vector> terrain_line = get_terrain();
    if(!terrain_line.empty() && snow && *snow)
    {
        // std::cerr << "Start TO Draw with Player: : " << character_position->x << std::endl ;
        fl_color(FL_WHITE);
        fl_begin_polygon();

        for(const auto& point : terrain_line)
        {
            Vector screen_point = logic_to_screen(point,view_left,view_top);
            // std::cerr << "screen x : " << x() + screen_point.x << ",y : " << y() + screen_point.y << std::endl ;
            fl_vertex(x() + screen_point.x, y() + screen_point.y);
        }
        fl_vertex(x()+w(),y()+h());
        fl_vertex(x(),y()+h());

        fl_end_polygon();
    }
    if(!terrain_line.empty() && snow && *snow)
    {
        // std::cerr << "Start TO Draw with Player: : " << character_position->x << std::endl ;
        for(int i= 0 ; i < 150; i++)
        {
            fl_color(fl_rgb_color(255-1*i,255-1.5*i,255));
            fl_begin_polygon();
            for(const auto& point : terrain_line)
            {
                Vector screen_point = logic_to_screen(point,view_left,view_top);
                // std::cerr << "screen x : " << x() + screen_point.x << ",y : " << y() + screen_point.y << std::endl ;
                fl_vertex(x() + screen_point.x, y() + screen_point.y+10*i);
            }

            for (int j = terrain_line.size() - 1; j >= 0; --j) {
                const auto& point = terrain_line[j];
                Vector screen_point = logic_to_screen(point, view_left, view_top);
                fl_vertex(x() + screen_point.x, y() + screen_point.y+10*i+10);
            }
            fl_end_polygon();
        }

        //fl_vertex(x()+w(),y()+h());
        //fl_vertex(x(),y()+h());

        //fl_end_polygon();
        }

    int stone_width = (*m_img_stone)->w();
    if(*stone_pos >= view_left-(stone_width/2) && *stone_pos <= view_right+(stone_width/2)){
        double stone_y = game_curve->evaluate(*stone_pos);
        Vector screen_point = logic_to_screen(Vector(*stone_pos,stone_y),view_left,view_top);
        draw_img(screen_point.x,screen_point.y,m_img_stone);
    }

    int penguin_width = (*m_img_penguin)->w();
    double penguin_pos = penguin->getPosition().x;
    if(penguin_pos >= view_left-(penguin_width/2) && penguin_pos <= view_right+(penguin_width/2)){
        Vector screen_point = logic_to_screen(penguin->getPosition(),view_left,view_top);
        draw_img(screen_point.x,screen_point.y,m_img_penguin);
    }

    // draw_img(x() + w()/2 , y() + h()/2,m_img_character);
    std::cerr << "Slide : " << *slide_pos << std::endl ;

    pl_hide->get()->hide();

    int centerX = x() + w()/2 ;
    int centerY = y() + h()/2 ;
    pl_show->get()->position(centerX,centerY);
    pl_show->get()->set_angle(-this->character->getAngle().deg()); //由于旋转的实现：逆时针为负方向，与常规意义相反，故此处取反
    pl_show->get()->draw();

    // std::cerr << "center x,y : " << centerX << ' ' << centerY << std::endl;

    int box_width = 150;
    int box_height = 40;
    int box_x = x() + w() - 230;
    int box_y = y() + 50;

    fl_color(fl_rgb_color(150,200,250)); 

    fl_font(FL_HELVETICA_BOLD, 15); 

    char ch_y_str[64];

     snprintf(ch_y_str, sizeof(ch_y_str), "Player Distance: %.2fm", ch_x/100);

    int text_width, text_height;
    fl_measure(ch_y_str, text_width, text_height, 0);
    fl_draw(ch_y_str, box_x + (box_width - text_width) / 2, box_y + (box_height - text_height) / 2 + fl_descent());

}
