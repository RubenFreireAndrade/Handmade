#pragma once

/*===================================================================#
| 'GameState' source files last updated on 11 May 2021               |
#===================================================================*/

class GameState
{

public:

	GameState() {}
	virtual ~GameState() = 0 {}

	virtual bool OnEnter() = 0;
	virtual GameState* Update(int deltaTime) = 0;
	virtual bool Draw() = 0;
	virtual void OnExit() = 0;

};