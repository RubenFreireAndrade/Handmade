#include "EndState.h"
#include "Game.h"
#include "Input.h"
#include "MenuState.h"
#include "PlayState.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all defaults
//------------------------------------------------------------------------------------------------------
PlayState::PlayState(Game* gameHandle, GameState* previousState) : GameState(gameHandle, previousState)
{

	m_image = nullptr;
	
}
//------------------------------------------------------------------------------------------------------
//function that creates all game objects for the state
//------------------------------------------------------------------------------------------------------
bool PlayState::OnEnter()
{

	m_image = new Background("Assets/Textures/Play_1280x720.png", "Assets/Audio/Play.ogg");	
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that reads key presses, mouse clicks and updates all game objects in scene
//------------------------------------------------------------------------------------------------------
bool PlayState::Update(int deltaTime)
{

	//play the background music associated with the image
	//when the state transitions to the next state stop it
	m_image->PlayMusic();

	//read keyboard state
	const Uint8* keys = Input::Instance()->GetKeyStates();

	//the M key moves to the main menu
	if (keys[SDL_SCANCODE_M])
	{
		m_image->StopMusic();
		m_isActive = m_isAlive = false;
		m_gameHandle->ChangeState(new MenuState(m_gameHandle, this));
	}

	//the Q key moves to the ending state
	if (keys[SDL_SCANCODE_Q])
	{
		m_image->StopMusic();
		m_isActive = m_isAlive = false;
		m_gameHandle->ChangeState(new EndState(m_gameHandle, this));
	}

	//loop through all game objects in vector and update them only if they are active
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if ((*it)->IsActive())
		{
			(*it)->Update(deltaTime);
		}
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that renders all game objects in scene
//------------------------------------------------------------------------------------------------------
bool PlayState::Draw()
{

	//render the background image
	m_image->Draw();

	//loop through all game objects in vector and 
	//display them only if they are active and visible
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{

		if ((*it)->IsActive() && (*it)->IsVisible())
		{
			(*it)->Draw();
		}
	}
	
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that removes all game objects from memory
//------------------------------------------------------------------------------------------------------
void PlayState::OnExit()
{

	//loop through all game objects in vector and remove them from memory
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		delete (*it);
	}

	//clear the game object vector
	m_gameObjects.clear();

	//destroy all individual game objects
	delete m_image;

}