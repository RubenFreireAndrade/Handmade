#pragma once

/*===================================================================#
| 'MainMenu' source files last updated on 22 September 2021          |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include <string>
#include <vector>
#include "GameObject.h"
#include "Text.h"

const int MENU_TEXT_CHAR_W = 25;
const int MENU_TEXT_CHAR_H = 53;

class MainMenu : public GameObject
{

public:

	MainMenu();
	virtual ~MainMenu() {}

	int GetMenuOption() const;
	void SetMenuText(const std::string& string);

	virtual void Update(int deltaTime);
	virtual bool Render();

	void Reset();

private:

	int m_menuOptionChoice;
	int m_menuOptionActive;
	std::vector<Text> m_menuText;

};