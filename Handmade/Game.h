#pragma once

/*===================================================================#
| 'Game' source files last updated on 11 May 2021                    |
#===================================================================*/

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
	GameState* m_gameState;

};