#include "MenuState.h"
#include "PlayState.h"

//======================================================================================================
bool MenuState::OnEnter()
{
	m_image.Load("Menu_1280x720.png", "Journeys.ogg");
	m_menu = std::make_unique<MenuKey>("Quikhand.ttf", MenuKey::Alignment::Bottom);
	m_menu->SetMenuText(MenuKey::Index::Index_1, "Play game");
	m_menu->SetMenuText(MenuKey::Index::Index_2, "Quit game");

	return true;
}
//======================================================================================================
GameState* MenuState::Update(int deltaTime)
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
bool MenuState::Render()
{
	m_image.Render();
	m_menu->Render();
	return true;
}
//======================================================================================================
void MenuState::OnExit()
{
	//Add shutdown tasks here
}