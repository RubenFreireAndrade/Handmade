#pragma once

/*===================================================================#
| 'Game' source files last updated on 28 May 2021                    |
#===================================================================*/

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

	bool Run();
	void Shutdown();

private:

	int m_deltaTime;
	std::unique_ptr<GameState> m_gameState;

};