#pragma once
#include <string>
#include <vector>
#include "GameObject.h"
#include "Text.h"

class MenuKey : public GameObject
{

public:

	enum class Alignment
	{
		Centre,
		Bottom,
		Left,
		Right
	};

	enum class Index
	{
		Index_1,
		Index_2,
		Index_3,
		Index_4,
		Index_5,
		None = -1
	};

	MenuKey(const std::string& filename = "",
		Alignment alignment = Alignment::Centre,
		int itemTotal = 2,
		int charWidth = 25,
		int charHeight = 53,
		int padding = 10);

	virtual ~MenuKey();

	Index GetMenuChoice() const;

	void SetActiveColor(Uint8 r, Uint8 g, Uint8 b);
	void SetInactiveColor(Uint8 r, Uint8 g, Uint8 b);
	void SetMenuText(Index index, const std::string& text);

	void Update(int deltaTime) override;
	bool Render() override;

	void Reset();

private:

	std::string m_fontID;
	Alignment m_alignment;
	
	SDL_Color m_activeColor{ 240, 0, 0 };
	SDL_Color m_inactiveColor{ 255, 255, 255 };
	SDL_Point m_charDimension;

	std::vector<Text> m_menuItems;
	Index m_menuActive{ Index::Index_1 };
	Index m_menuChoice{ Index::None };

};