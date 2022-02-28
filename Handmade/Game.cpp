#include "Game.h"
#include "Input.h"
#include "Music.h"
#include "Screen.h"
#include "Text.h"
#include "Utility.h"

//======================================================================================================
Game::Game(GameState* initialGameState)
{
	m_gameState.reset(initialGameState);
}
//======================================================================================================
bool Game::Initialize(const std::string& name, int screenWidth, int screenHeight, bool fullscreen)
{
	if (!Screen::Instance()->Initialize(name.c_str(), screenWidth, screenHeight, fullscreen))
	{
		return false;
	}

	Screen::Instance()->SetClearColor(100, 149, 237);

	if (!(Music::Initialize()))
	{
		//Not serious - game does not need to end
		//Add your own outcome/messages here...
	}

	if (!Text::Initialize())
	{
		//Not serious - game does not need to end
		//Add your own outcome/messages here...
	}

	Utility::SetWindowHandle(Screen::Instance()->GetWindowHandle());
	return true;
}
//======================================================================================================
void Game::AddState(GameState* state)
{
	//TODO - Fix this later
	//state->OnEnter();
	//m_gameStates.push_front(state);
}
//======================================================================================================
void Game::ChangeState(GameState* state)
{
	//TODO - Fix this later
	//state->OnEnter();
	//m_gameStates.push_back(state);
}
//======================================================================================================
bool Game::Run()
{
	m_gameState->OnEnter();

	while (m_gameState)
	{
		//TODO - Fix this later
		//The current active state is always the front one
		//state = m_gameStates.front();

		int startTime = SDL_GetTicks();

		Screen::Instance()->Clear();
		Input::Instance()->Update();

		GameState* nextState = m_gameState->Update(m_deltaTime);

		m_gameState->Render();

		Screen::Instance()->Present();

		if (nextState != m_gameState.get())
		{
			m_gameState->OnExit();
			m_gameState.reset(nextState);

			if (m_gameState)
			{
				m_gameState->OnEnter();
			}
		}

		m_deltaTime = SDL_GetTicks() - startTime;

		//TODO - Fix this later
		//The main game loop will run as long there are game states available
		//m_endGame = m_gameStates.empty();
	}

	//TODO - Fix this later
	//If game state is also flagged as dead  
	//then completely remove all of its objects
	/*if (!state->IsAlive())
	{
		RemoveState();
	}*/

	return true;
}
//======================================================================================================
void Game::Shutdown()
{
	Text::Shutdown();
	Music::Shutdown();
	Screen::Instance()->Shutdown();
}
//======================================================================================================
void Game::RemoveState()
{
	//TODO - Fix this later
	/*m_gameStates.front()->OnExit();
	delete m_gameStates.front();
	m_gameStates.pop_front();*/
}