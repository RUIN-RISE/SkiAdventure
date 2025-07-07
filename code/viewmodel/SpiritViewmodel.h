
#ifndef __SPIRIT_VIEW_MODEL_H__
#define __SPIRIT_VIEW_MODEL_H__

#include "../common/Rotator.h"

class SpiritViewModel
{
public:
	SpiritViewModel() noexcept
	{
	}
	SpiritViewModel(const SpiritViewModel&) = delete;
	~SpiritViewModel() noexcept
	{
	}

	SpiritViewModel& operator=(const SpiritViewModel&) = delete;

//properties
	const std::unique_ptr<RotatableCharacter>* get_player() const noexcept
	{
		return &m_player;
	}
	const std::unique_ptr<Fl_PNG_Image>* get_snow() const noexcept
	{
		return &m_snow;
	}
	const std::unique_ptr<Fl_PNG_Image>* get_stone() const noexcept
	{
		return &m_stone;
	}
	const std::unique_ptr<Fl_PNG_Image>* get_penguin() const noexcept
	{
		return &m_penguin;
	}
	const std::unique_ptr<Fl_PNG_Image>* get_background() const noexcept
	{
		return &m_background;
	}
//methods
	bool initialize();

private:
//properties
	// std::unique_ptr<Fl_PNG_Image> m_player;
	std::unique_ptr<RotatableCharacter> m_player;
	std::unique_ptr<Fl_PNG_Image> m_snow;
	std::unique_ptr<Fl_PNG_Image> m_stone;
	std::unique_ptr<Fl_PNG_Image> m_penguin;
	std::unique_ptr<Fl_PNG_Image> m_background;
};

#endif
