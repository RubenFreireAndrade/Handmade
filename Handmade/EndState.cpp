#include "EndState.h"
#include "Game.h"
#include "Input.h"
#include "PlayState.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
EndState::EndState()
{

	m_menu = nullptr;
	m_image = nullptr;

}
//------------------------------------------------------------------------------------------------------
//function that creates a new background screen object and menu
//------------------------------------------------------------------------------------------------------
bool EndState::OnEnter()
{

	m_menu = new MainMenu;
	m_menu->SetMenuText("PLAY AGAIN");
	m_menu->SetMenuText("QUIT GAME");

	m_image = new Background("Assets/Textures/End_1280x720.png", "Assets/Audio/End.ogg");

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that waits for a Q key to be pressed before ending all game states (the end!)
//------------------------------------------------------------------------------------------------------
bool EndState::Update(int deltaTime)
{

	//play the background music associated with the image
	//when the state transitions to the next state stop it
	m_image->PlayMusic();

	//update the main menu to determine which menu choice was made
	m_menu->Update(deltaTime);

	//if player wants to play again then return to the main playing state
	if (m_menu->GetMenuOption() == static_cast<int>(MenuOption::PLAY))
	{
		m_image->StopMusic();
		//m_isActive = m_isAlive = false;
		//m_gameHandle->ChangeState(new PlayState(m_gameHandle));
	}

	//if player chose to exit the game then quit altogether
	if (m_menu->GetMenuOption() == static_cast<int>(MenuOption::QUIT))
	{
		m_image->StopMusic();
		//m_isActive = m_isAlive = false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that renders the background splash image
//------------------------------------------------------------------------------------------------------
bool EndState::Draw()
{

	m_image->Draw();
	m_menu->Draw();

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that removes splash screen background object from memory
//------------------------------------------------------------------------------------------------------
void EndState::OnExit()
{

	delete m_image;
	delete m_menu;

}