#include "AudioManager.h"
#include "Game.h"
#include "Input.h"
#include "MenuState.h"
#include "Screen.h"
#include "TextureManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Game::Game(GameState* initialGameState)
{

	m_deltaTime = 0;
	m_endGame = false;
	m_gameState = initialGameState;

}
//------------------------------------------------------------------------------------------------------
//function that initializes all sub-systems of the game
//------------------------------------------------------------------------------------------------------
bool Game::Initialize(const std::string& name, int screenWidth, int screenHeight, bool fullscreen)
{

	//initialise game screen with passed values and return false if error occured
	if (!Screen::Instance()->Initialize(name.c_str(), screenWidth, screenHeight, fullscreen))
	{
		return false;
	}

	//set the background rendering color
	Screen::Instance()->SetClearColor(100, 149, 237);

	//initialize audio sub-system and return false if error occured
	if (!(AudioManager::Instance()->Initialize()))
	{
		//not serious - game does not need to end
		//add your own outcome/messages here...
	}

	//initialize font sub-system and return false if error occured
	if (!TextureManager::Instance()->Initialize())
	{
		//not serious - game does not need to end
		//add your own outcome/messages here...
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that runs the main game loop and updates all components
//------------------------------------------------------------------------------------------------------
bool Game::Run()
{

	//GameState* state;

	//..
	m_gameState->OnEnter();

	//main game loop!
	//while (!m_endGame)
	{

		//current active state is always the front one
		//state = m_gameStates.front();

		//update and render all objects while the current state is active
		//each state will flag itself as inactive after which the loop breaks
		while (m_gameState)
		{

			//save time value to mark the start of the frame
			int startTime = SDL_GetTicks();

			//update screen by clearing SDL frame buffer
			Screen::Instance()->Update();

			//update input handling by listening for input events
			Input::Instance()->Update();

			//update the currently active state
			GameState* nextState = m_gameState->Update(m_deltaTime);

			//render the currently active state
			m_gameState->Draw();
			
			//swap the frame buffer
			Screen::Instance()->Draw();

			//..
			if (nextState != m_gameState)
			{
				m_gameState->OnExit();
				delete m_gameState;

				m_gameState = nextState;

				//..
				if (m_gameState)
				{
					m_gameState->OnEnter();
				}

			}

			//calculate time value passed for one frame call
			//if vsync is on this value should be around 16ms
			m_deltaTime = SDL_GetTicks() - startTime;
			
		}

		//if game state is also flagged as dead  
		//then completely remove all of its objects
		/*if (!state->IsAlive())
		{
			RemoveState();
		}*/

		//the main game loop will run as long there are game states available
		//m_endGame = m_gameStates.empty();

	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that closes down all sub-systems of the game
//------------------------------------------------------------------------------------------------------
void Game::ShutDown()
{

	//close down font and audio sub-systems
	TextureManager::Instance()->ShutDown();
	AudioManager::Instance()->ShutDown();

	//close down game screen 
	Screen::Instance()->ShutDown();

}