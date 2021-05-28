#include "MenuState.h"
#include "PlayState.h"

//======================================================================================================
bool MenuState::OnEnter()
{
	Text::Load("Assets/Fonts/Quikhand.ttf", "Menu_Font", Text::FontSize::SMALL);
	
	m_image.Load("Assets/Images/Menu_1280x720.png", "Assets/Music/Journeys.ogg");
	m_menu.SetMenuText("Play game");
	m_menu.SetMenuText("Quit game");

	return true;
}
//======================================================================================================
GameState* MenuState::Update(int deltaTime)
{
	m_image.PlayMusic();
	m_menu.Update(deltaTime);

	if (m_menu.GetMenuOption() == static_cast<int>(MenuOption::PLAY))
	{
		m_image.StopMusic();
		return new PlayState;
	}

	if (m_menu.GetMenuOption() == static_cast<int>(MenuOption::QUIT))
	{
		m_image.StopMusic();
		return nullptr;
	}

	return this;
}
//======================================================================================================
bool MenuState::Render()
{
	m_image.Render();
	m_menu.Render();
	return true;
}
//======================================================================================================
void MenuState::OnExit()
{
	Text::Unload("Menu_Font");
}