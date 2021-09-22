#pragma once

/*===================================================================#
| 'PlayState' source files last updated on 31 May 2021               |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include <vector>
#include "Background.h"
#include "GameObject.h"
#include "GameState.h"

class PlayState : public GameState
{

public:

	PlayState() {}
	virtual ~PlayState() {}

	virtual bool OnEnter();
	virtual GameState* Update(int deltaTime);
	virtual bool Render();
	virtual void OnExit();

private:

	Background m_image;
	std::vector<GameObject> m_gameObjects;

};