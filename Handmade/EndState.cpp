#include "EndState.h"
#include "PlayState.h"

//======================================================================================================
bool EndState::OnEnter()
{
	m_image.Load("End_1280x720.png", "Glory.ogg");
	m_menu = std::make_unique<MenuKey>("Quikhand.ttf", MenuKey::Alignment::Bottom);
	m_menu->SetMenuText(MenuKey::Index::Index_1, "Play again");
	m_menu->SetMenuText(MenuKey::Index::Index_2, "Quit game");

	return true;
}
//======================================================================================================
GameState* EndState::Update(int deltaTime)
{
	m_image.PlayMusic();
	m_menu->Update(deltaTime);

	if (m_menu->GetMenuChoice() == static_cast<MenuKey::Index>(MenuOption::Play))
	{
		m_image.StopMusic();
		return new PlayState;
	}

	if (m_menu->GetMenuChoice() == static_cast<MenuKey::Index>(MenuOption::Quit))
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
	m_menu->Render();
	return true;
}
//======================================================================================================
void EndState::OnExit()
{
	//Add shutdown tasks here
}