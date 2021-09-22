#include "Input.h"
#include "MainMenu.h"
#include "Screen.h"
#include "Vector.h"

//======================================================================================================
MainMenu::MainMenu()
{
	m_menuOptionActive = 0;
	m_menuOptionChoice = -1;
}
//======================================================================================================
int MainMenu::GetMenuOption() const
{
	return m_menuOptionChoice;
}
//======================================================================================================
void MainMenu::SetMenuText(const std::string& string)
{
	Text menuText;
	menuText.SetFont("Menu_Font");
	menuText.SetColor(255, 255, 255);
	menuText.SetSize(string.size() * MENU_TEXT_CHAR_W, MENU_TEXT_CHAR_H);
	menuText.SetString(string);
	m_menuText.push_back(menuText);
}
//======================================================================================================
void MainMenu::Update(int deltaTime)
{
	static bool isKeyPressed = false;

	if (Input::Instance()->IsKeyPressed(HM_KEY_DOWN) && !isKeyPressed)
	{
		if (m_menuOptionActive == m_menuText.size() - 1)
		{
			m_menuOptionActive = 0;
		}

		else
		{
			m_menuOptionActive++;
		}
	}

	if (Input::Instance()->IsKeyPressed(HM_KEY_UP) && !isKeyPressed)
	{
		if (m_menuOptionActive == 0)
		{
			m_menuOptionActive = m_menuText.size() - 1;
		}

		else
		{
			m_menuOptionActive--;
		}
	}

	if (Input::Instance()->IsKeyPressed(HM_KEY_RETURN))
	{
		m_menuOptionChoice = m_menuOptionActive;
	}

	isKeyPressed = Input::Instance()->IsKeyPressed();

	for (auto& menuItem : m_menuText)
	{
		menuItem.SetColor(255, 255, 255);
	}

	m_menuText[m_menuOptionActive].SetColor(240, 0, 0);
}
//======================================================================================================
bool MainMenu::Render()
{
	Vector<int> resolution = Screen::Instance()->GetResolution();

	int posY = static_cast<int>((resolution.y - resolution.y / 4) -
		(m_menuText.size() / 2 * MENU_TEXT_CHAR_H));

	int count = 0;
	for (auto& menuItem : m_menuText)
	{
		menuItem.Render(static_cast<int>((resolution.x / 2) - menuItem.GetSize().x / 2),  //x
			static_cast<int>(posY + (count++) * MENU_TEXT_CHAR_H));  //y
	}

	return true;
}
//======================================================================================================
void MainMenu::Reset()
{
	m_menuOptionActive = 0;
	m_menuOptionChoice = -1;
}