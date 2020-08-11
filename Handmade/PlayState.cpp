#include "EndState.h"
#include "Input.h"
#include "MenuState.h"
#include "PlayState.h"

//======================================================================================================
PlayState::PlayState()
{
	m_image = nullptr;
}
//======================================================================================================
bool PlayState::OnEnter()
{
	m_image = new Background("Assets/Images/Play_1280x720.png", "Assets/Music/Play.ogg");	
	return true;
}
//======================================================================================================
GameState* PlayState::Update(int deltaTime)
{
	m_image->PlayMusic();

	if (Input::Instance()->IsKeyPressed(HM_KEY_M))
	{
		m_image->StopMusic();
		return new MenuState;
	}

	if (Input::Instance()->IsKeyPressed(HM_KEY_Q))
	{
		m_image->StopMusic();
		return new EndState;
	}

	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if ((*it)->IsActive())
		{
			(*it)->Update(deltaTime);
		}
	}

	return this;
}
//======================================================================================================
bool PlayState::Draw()
{
	m_image->Draw();

	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if ((*it)->IsActive() && (*it)->IsVisible())
		{
			(*it)->Draw();
		}
	}
	
	return true;
}
//======================================================================================================
void PlayState::OnExit()
{
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		delete (*it);
	}

	m_gameObjects.clear();
	delete m_image;
}