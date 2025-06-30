#include "GameBoard.h"

Gameboard::Gameboard(int x,int y,int w,int h) 
    : Fl_Widget(x,y,w,h);
{

}

Gameboard::~Gameboard(int x,int y,int w,int h) 
{
    id(textureData){
        stbi_image_free(textureData);
    }
}

//加载材质，成功返回1
bool Gameboard::loadTexture(const std::string& filename){
    if(textureData) stbi_image_free(textureData);
    textureData = stbi_load(filename.c_str(),texWidth,texHeight,texChannels,3);
    return textureData != nullptr;
}


void Gameboard::setmap(const std::vector<Fl_Point>& points){
    terrain_line = points;
    redraw();
    //调用draw
}

void Gameboard::draw(){

    //折线下方填充贴图
    if(!terrain_line.empty() && textureData)
    {
        for(int row = terrain_line.front().y ; row < h() ; ++row)
        {
            for(int column = 0 ; column < w() ; column += texWidth)
            {
                int drawWidth = std::min(texWidth,w()-column);
                int drawHeight = std::min(texHeight,h()-row);
                fl_draw_image(textureData,x()+column,y()+row,drawHeight,drawWidth,3);
            }
        }
    }

    //绘制一条黑色折线轮廓，确认正确后可以删掉
    fl_color(Fl_BLACK);
    fl_begin_line();
    for(const auto& pt = terrain_line)
        fl_vertex(x() + pt.x, y()+pt.y);
    fl_end_line();
}