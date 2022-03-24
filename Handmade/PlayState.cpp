#include "EndState.h"
#include "Input.h"
#include "StartState.h"
#include "PlayState.h"

//======================================================================================================
bool PlayState::OnEnter()
{
	m_image.Load("Play_1280x720.png", "Aircord.ogg");
	return true;
}
//======================================================================================================
GameState* PlayState::Update(int deltaTime)
{
	m_image.PlayMusic();

	if (Input::Instance()->IsKeyPressed(HM_KEY_M))
	{
		m_image.StopMusic();
		return new StartState;
	}

	if (Input::Instance()->IsKeyPressed(HM_KEY_Q))
	{
		m_image.StopMusic();
		return new EndState;
	}

	for (auto& gameObject : m_gameObjects)
	{
		if (gameObject.IsActive())
		{
			gameObject.Update(deltaTime);
		}
	}

	return this;
}
//======================================================================================================
bool PlayState::Render()
{
	m_image.Render();

	for (auto& gameObject : m_gameObjects)
	{
		if (gameObject.IsActive() && gameObject.IsVisible())
		{
			gameObject.Render();
		}
	}

	return true;
}
//======================================================================================================
void PlayState::OnExit()
{
	m_gameObjects.clear();
}