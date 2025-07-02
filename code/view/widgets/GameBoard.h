#pragma once

// #include "../../common/air_map.h"
//折线点
struct Fl_Point{
    int x;
    int y;
};

class Gameboard : public Fl_Widget{
    public:
    //地图，在坐标(x,y)处放置宽和高分别为w,h的地图
    Gameboard(int x,int y,int w,int h);
    ~Gameboard() noexcept;

    void setmap(const std::vector<Fl_Point>& points) noexcept;
    bool loadTexture(const std::string &filename);

    protected:
    void draw() override;

    private:
    std::vector<Fl_Point> terrain_line;

    //贴图
    unsigned char *textureData = nullptr;
    int texWidth = 0, texHeight = 0, texChannels = 0;
};