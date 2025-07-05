#pragma once

#include "../../common/Vector.h"
#include "../../common/Curve.h"
#include "../../common/PhysicsEntity.h"

class Gameboard : public Fl_Group{
    private:
    typedef Fl_Group BaseClass;

    public:
    //地图，在坐标(x,y)处放置宽和高分别为w,h的地图
    Gameboard(int x,int y,int w,int h,const char *l = nullptr);
    ~Gameboard() noexcept;

    void set_curve(const Curve* curve) noexcept
    {
        game_curve = curve;
    }

    // void set_character_position(const Vector* pos) noexcept
    // {
    //     character_position = pos;
    // }

    void set_player_instance(const PhysicsEntity* pl) noexcept {
        character = pl ;
    }

    Vector logic_to_screen(const Vector& logic_pos,double view_left, double view_top) const ;
    std::vector<Vector> get_terrain();

    void set_character(const std::unique_ptr<Fl_PNG_Image>* p) noexcept
    {
        m_img_character = p;
		// m_character.image(m_img_character->get());
    }
    void set_snow(const std::unique_ptr<Fl_PNG_Image>* p) noexcept
    {
        snow = p;
    }
    void set_stone(const std::unique_ptr<Fl_PNG_Image>* p) noexcept
    {
        m_img_stone = p;
    }
    void set_background(const std::unique_ptr<Fl_PNG_Image>* p) noexcept
    {
        background = p;
    }

    void set_stone_pos(const double *sp){
        stone_pos = sp;
    }

    protected:
    void draw() override;

    private:
    // Fl_Box m_character;
    private:
    std::vector<Vector> terrain_line;

    const std::unique_ptr<Fl_PNG_Image>* m_img_character;
    const std::unique_ptr<Fl_PNG_Image>* snow;
    const std::unique_ptr<Fl_PNG_Image>* m_img_stone;
    const std::unique_ptr<Fl_PNG_Image>* background;

    // const Vector* character_position;
    const PhysicsEntity* character;
    int map_width,map_height;
    const Curve* game_curve = nullptr;

    const double *stone_pos;
};
