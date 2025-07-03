
#ifndef __SPIRIT_VIEW_MODEL_H__
#define __SPIRIT_VIEW_MODEL_H__

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
	const std::unique_ptr<Fl_PNG_Image>* get_player() const noexcept
	{
		return &m_player;
	}
//methods
	bool initialize();

private:
//properties
	std::unique_ptr<Fl_PNG_Image> m_player;
};

#endif
