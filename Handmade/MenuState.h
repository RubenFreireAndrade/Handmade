#pragma once

/*===================================================================#
| 'MenuState' source files last updated on 28 May 2021               |
#===================================================================*/

#include "Background.h"
#include "GameState.h"
#include "MainMenu.h"

class MenuState : public GameState
{

public:

	enum class MenuOption
	{
		PLAY,
		QUIT
	};

	MenuState() {}
	virtual ~MenuState() {}

	virtual bool OnEnter();
	virtual GameState* Update(int deltaTime);
	virtual bool Render();
	virtual void OnExit();

private:

	MainMenu m_menu;
	Background m_image;

};