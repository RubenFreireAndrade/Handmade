#pragma once

/*===================================================================#
| 'Game' source files last updated on 6 October 2021                 |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include <deque>
#include <memory>
#include <string>
#include "GameState.h"

class Game
{

public:

	Game(GameState* initialGameState);

	bool Initialize(const std::string& name,
		int screenWidth,
		int screenHeight,
		bool fullscreen = false);

	void AddState(GameState* state);
	void ChangeState(GameState* state);

	bool Run();
	void Shutdown();

private:

	void RemoveState();

	int m_deltaTime;
	//std::deque<GameState*> m_gameStates;
	std::unique_ptr<GameState> m_gameState;

};