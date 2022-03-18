#include "Input.h"
#include "MenuKey.h"
#include "Screen.h"
#include "Vector.h"

//======================================================================================================
MenuKey::MenuKey(const std::string& filename,
	Alignment alignment,
	int itemTotal,
	int charWidth,
	int charHeight,
	int padding) : m_fontID(filename), m_alignment(alignment)
{
	m_charDimension.x = charWidth;
	m_charDimension.y = charHeight;

	auto resolution = Screen::Instance()->GetResolution();

	//This will position the text dead centre in the middle of the screen
	//X - Divide screen width in half and subtract half the width of each text
	//Y - Divide screen height in half and subtract half of the menu's text heights
	if (alignment == Alignment::Centre)
	{
		m_position.x = resolution.x / 2;
		m_position.y = static_cast<int>((resolution.y / 2) - (itemTotal / 2.0f * charHeight));
	}

	//This will position the text in the bottom half of the screen, centered in X
	//X - Divide screen width in half and subtract half the width of each text
	//Y - Divide screen height in quarters and subtract half of the menu's text heights
	else if (alignment == Alignment::Bottom)
	{
		m_position.x = resolution.x / 2;
		m_position.y = static_cast<int>((resolution.y - resolution.y / 4) - (itemTotal / 2.0f * charHeight));
	}

	//This will position the text in the bottom half of the screen, aligned on the left
	//X - Position the origin on the very left and add on some padding based on passed value
	//Y - Divide the screen height in quarters and subtract half of the menu's text heights
	else if (alignment == Alignment::Left)
	{
		m_position.x += padding;
		m_position.y = static_cast<int>((resolution.y - resolution.y / 4) - (itemTotal / 2.0f * charHeight));
	}

	//this will position the text in the bottom half of the screen, aligned on the right
	//X - position the origin on the very right and add on some padding based on passed value
	//Y - divide the screen height in quarters and subtract half of the menu's text heights
	else if (alignment == Alignment::Right)
	{
		m_position.x = resolution.x - padding;
		m_position.y = static_cast<int>((resolution.y - resolution.y / 4) - (itemTotal / 2.0f * charHeight));
	}

	//pre-load text objects into memory
	for (int i = 0; i < itemTotal; i++)
	{
		m_menuItems.push_back(Text());
	}

	Text::Load(filename, "MenuFont");
}
//======================================================================================================
MenuKey::~MenuKey()
{
	m_menuItems.clear();
	Text::Unload("MenuFont");
}
//======================================================================================================
MenuKey::Index MenuKey::GetMenuChoice() const
{
	return m_menuChoice;
}
//======================================================================================================
void MenuKey::SetActiveColor(Uint8 r, Uint8 g, Uint8 b)
{
	m_activeColor = { r, g, b };
}
//======================================================================================================
void MenuKey::SetInactiveColor(Uint8 r, Uint8 g, Uint8 b)
{
	m_inactiveColor = { r, g, b };
}
//======================================================================================================
void MenuKey::SetMenuText(Index index, const std::string& text)
{
	m_menuItems[static_cast<int>(index)].SetFont("MenuFont");
	m_menuItems[static_cast<int>(index)].SetString(text);
	m_menuItems[static_cast<int>(index)].SetSize(text.size() * m_charDimension.x, m_charDimension.y);
	m_menuItems[static_cast<int>(index)].SetColor(m_inactiveColor.r, m_inactiveColor.g, m_inactiveColor.b);
}
//======================================================================================================
void MenuKey::Update(int deltaTime)
{
	//Flag to monitor if key is pressed so that when pressing UP/DOWN
	//key the selected menu option doesn't move at lightning speed
	static bool isKeyPressed = false;

	//Only if DOWN arrow key is pressed and key was not pressed before move one option down the menu
	//Also check if the last menu item has been reached, which means we need to loop back to the top
	if (Input::Instance()->IsKeyPressed(HM_KEY_DOWN) && !isKeyPressed)
	{
		if (m_menuActive == static_cast<Index>(m_menuItems.size() - 1))
		{
			m_menuActive = Index::Index_1;
		}

		else
		{
			m_menuActive = static_cast<Index>(static_cast<int>(m_menuActive) + 1);
		}

		m_isDirty = true;
	}

	//Only if UP arrow key is pressed and key was not pressed before move one option up the menu
	//Also check if the first menu item has been reached, which means we need to go to the bottom
	if (Input::Instance()->IsKeyPressed(HM_KEY_UP) && !isKeyPressed)
	{
		if (m_menuActive == Index::Index_1)
		{
			m_menuActive = static_cast<Index>(m_menuItems.size() - 1);
		}

		else
		{
			m_menuActive = static_cast<Index>(static_cast<int>(m_menuActive) - 1);
		}

		m_isDirty = true;
	}

	if (Input::Instance()->IsKeyPressed(HM_KEY_RETURN))
	{
		m_menuChoice = m_menuActive;
	}

	//Update state of key based on if it's pressed or not which will make sure the next time
	//the frame is called the above code will either move the menu option or keep it still
	isKeyPressed = Input::Instance()->IsKeyPressed();

	if (m_isDirty)
	{
		for (size_t i = 0; i < m_menuItems.size(); i++)
		{
			m_menuItems[i].SetColor(m_inactiveColor.r, m_inactiveColor.g, m_inactiveColor.b);
		}

		m_menuItems[static_cast<int>(m_menuActive)].SetColor(m_activeColor.r, m_activeColor.g, m_activeColor.b);

		m_isDirty = false;
	}
}
//======================================================================================================
bool MenuKey::Render()
{
	//Loop through all menu items and position them based on the x and y positional origin
	//Check what menu style is set so that we can determine where on-screen to render the text

	for (size_t i = 0; i < m_menuItems.size(); i++)
	{
		if (m_alignment == Alignment::Centre || m_alignment == Alignment::Bottom)
		{
			m_menuItems[i].Render(m_position.x - (m_menuItems[i].GetSize().x / 2),      //x
				m_position.y + (i * m_menuItems[i].GetSize().y));     //y
		}

		else if (m_alignment == Alignment::Left)
		{
			m_menuItems[i].Render(m_position.x,                                          //x
				m_position.y + (i * m_menuItems[i].GetSize().y));     //y
		}

		else if (m_alignment == Alignment::Right)
		{
			m_menuItems[i].Render(m_position.x - m_menuItems[i].GetSize().x,            //x
				m_position.y + (i * m_menuItems[i].GetSize().y));     //y
		}
	}

	return true;
}
//======================================================================================================
void MenuKey::Reset()
{
	m_menuActive = Index::Index_1;
	m_menuChoice = Index::None;
}