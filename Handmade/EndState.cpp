#include "EndState.h"
#include "PlayState.h"

//======================================================================================================
bool EndState::OnEnter()
{
	Text::Load("Quikhand.ttf", "Menu_Font", Text::FontSize::Small);
	
	m_image.Load("End_1280x720.png", "Glory.ogg");
	m_menu.SetMenuText("Play again");
	m_menu.SetMenuText("Quit game");

	return true;
}
//======================================================================================================
GameState* EndState::Update(int deltaTime)
{
	m_image.PlayMusic();
	m_menu.Update(deltaTime);

	if (m_menu.GetMenuOption() == static_cast<int>(MenuOption::Play))
	{
		m_image.StopMusic();
		return new PlayState;
	}

	if (m_menu.GetMenuOption() == static_cast<int>(MenuOption::Quit))
	{
		m_image.StopMusic();
		return nullptr;
	}

	return this;
}
//======================================================================================================
bool EndState::Render()
{
	m_image.Render();
	m_menu.Render();
	return true;
}
//======================================================================================================
void EndState::OnExit()
{
	Text::Unload("Menu_Font");
}