#pragma once

/*===================================================================#
| 'EndState' source files last updated on 19 May 2021                |
#===================================================================*/

#include <memory>
#include "Background.h"
#include "GameState.h"
#include "MainMenu.h"

class EndState : public GameState
{

public:

	enum class MenuOption
	{
		PLAY,
		QUIT
	};

	EndState() {}
	virtual ~EndState() {}

	virtual bool OnEnter();
	virtual GameState* Update(int deltaTime);
	virtual bool Draw();
	virtual void OnExit();

private:

	std::unique_ptr<MainMenu> m_menu;
	std::unique_ptr<Background> m_image;

};