#pragma once

/*===================================================================#
| 'GameState' source files last updated on 11 May 2021               |
#===================================================================*/

//TODO - Add default screens fof each game state
//TODO - Cannot load resources in game states ctor
//TODO - Consider RAII to load/release resources in the ctor/dtor
//This would remove the need for OnEnter/OnExit?

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