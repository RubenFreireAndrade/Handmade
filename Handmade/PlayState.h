#pragma once

/*===================================================================#
| 'Music' source files last updated on 19 May 2021                   |
#===================================================================*/

#include <memory>
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
	virtual bool Draw();
	virtual void OnExit();

private:

	std::unique_ptr<Background> m_image;
	std::vector<std::unique_ptr<GameObject>> m_gameObjects;

};