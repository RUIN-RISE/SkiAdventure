#pragma once

#include "../../common/Vector.h"

class Gameboard : public Fl_Group{
    private:
    typedef Fl_Group BaseClass;

    public:
    //地图，在坐标(x,y)处放置宽和高分别为w,h的地图
    Gameboard(int x,int y,int w,int h,const char *l = nullptr);
    ~Gameboard() noexcept;

    void setmap(const std::vector<Vector>& points) noexcept
    {
        terrain_line = points;
    }
    bool loadTexture(const std::string &filename);
    void set_character(const std::unique_ptr<Fl_PNG_Image>* p) noexcept
    {
        character = p;
		m_character.image(character->get());
    }
        void set_snow(const std::unique_ptr<Fl_PNG_Image>* p) noexcept
    {
        snow = p;
    }

    protected:
    void draw() override;

    private:
    Fl_Box m_character;

    private:
    std::vector<Vector> terrain_line;

    const std::unique_ptr<Fl_PNG_Image>* character;
    const std::unique_ptr<Fl_PNG_Image>* snow;
};