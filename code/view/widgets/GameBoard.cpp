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

/*    int band_height = 50;  // 每条带的高度（可调）
int num_bands = h() / band_height;

// 顶部白色
int r_top = 255, g_top = 255, b_top = 255;
// 底部冷蓝色
int r_bottom = 100, g_bottom = 150, b_bottom = 255;

for (int i = 0; i < num_bands; ++i) {
    double t = static_cast<double>(i) / (num_bands - 1);
    int r = static_cast<int>(r_top * (1 - t) + r_bottom * t);
    int g = static_cast<int>(g_top * (1 - t) + g_bottom * t);
    int b = static_cast<int>(b_top * (1 - t) + b_bottom * t);
    fl_color(fl_rgb_color(r, g, b));
    
    int y_band = y() + i * band_height;
    fl_rectf(x(), y_band, w(), band_height);
}
std::vector<double> snow_top_y(w(), screen_height); // 存每个 x 像素对应雪坡顶部 y 坐标，初始为最底部

// Step 1: 记录雪坡顶部轮廓
for (const auto& point : terrain_line) {
    Vector screen_point = logic_to_screen(point, view_left, view_top);
    int x_pos = static_cast<int>(x() + screen_point.x);
    int y_pos = static_cast<int>(y() + screen_point.y);
    if (x_pos >= 0 && x_pos < w()) {
        snow_top_y[x_pos] = std::min(snow_top_y[x_pos], static_cast<double>(y_pos));
    }
}

// Step 2: 按条带渐变填充雪坡区域
for (int y_band = 0; y_band < h(); y_band += band_height) {
    double t = static_cast<double>(y_band) / h();  // 渐变比例
    int r = static_cast<int>(255 * (1 - t) + 100 * t);
    int g = static_cast<int>(255 * (1 - t) + 150 * t);
    int b = static_cast<int>(255 * (1 - t) + 255 * t);
    fl_color(fl_rgb_color(r, g, b));

    for (int x_pos = 0; x_pos < w(); ++x_pos) {
        if (y_band >= snow_top_y[x_pos]) {  // 雪坡区域内才填充
            fl_rectf(x() + x_pos, y() + y_band, 1, band_height);
        }
    }
}
*/

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

    // if(m_img_character && *m_img_character)
    // {
    //     int charX = centerX - (*m_img_character)->w()/2;
    //     int charY = centerY - (*m_img_character)->w()/2;
    //     (*m_img_character)->draw(charX,charY);
    // }
    // BaseClass::draw_children();
}
