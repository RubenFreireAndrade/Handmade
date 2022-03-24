#pragma once
#include <memory>
#include "Background.h"
#include "GameState.h"
#include "MenuKey.h"

class StartState : public GameState
{

public:

	enum class MenuOption
	{
		Play,
		Quit
	};

	StartState() {}
	virtual ~StartState() {}

	virtual bool OnEnter();
	virtual GameState* Update(int deltaTime);
	virtual bool Render();
	virtual void OnExit();

private:

	Background m_image;
	std::unique_ptr<MenuKey> m_menu;

};