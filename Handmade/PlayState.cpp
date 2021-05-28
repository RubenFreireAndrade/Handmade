#include "EndState.h"
#include "Input.h"
#include "MenuState.h"
#include "PlayState.h"

//======================================================================================================
bool PlayState::OnEnter()
{
	m_image.Load("Assets/Images/Play_1280x720.png", "Assets/Music/Aircord.ogg");
	return true;
}
//======================================================================================================
GameState* PlayState::Update(int deltaTime)
{
	m_image.PlayMusic();

	if (Input::Instance()->IsKeyPressed(HM_KEY_M))
	{
		m_image.StopMusic();
		return new MenuState;
	}

	if (Input::Instance()->IsKeyPressed(HM_KEY_Q))
	{
		m_image.StopMusic();
		return new EndState;
	}

	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if ((*it).IsActive())
		{
			(*it).Update(deltaTime);
		}
	}

	return this;
}
//======================================================================================================
bool PlayState::Render()
{
	m_image.Render();

	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if ((*it).IsActive() && (*it).IsVisible())
		{
			(*it).Render();
		}
	}

	return true;
}
//======================================================================================================
void PlayState::OnExit()
{
	m_gameObjects.clear();
}