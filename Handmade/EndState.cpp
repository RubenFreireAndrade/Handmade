#include "EndState.h"
#include "PlayState.h"

//======================================================================================================
bool EndState::OnEnter()
{
	Text::Load("Assets/Fonts/Quikhand.ttf", "Menu_Font", Text::FontSize::SMALL);
	
	m_image.Load("Assets/Images/End_1280x720.png", "Assets/Music/Glory.ogg");
	m_menu.SetMenuText("Play again");
	m_menu.SetMenuText("Quit game");

	return true;
}
//======================================================================================================
GameState* EndState::Update(int deltaTime)
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