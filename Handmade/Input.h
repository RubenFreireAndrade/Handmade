#ifndef INPUT_H
#define INPUT_H

/*==============================================================================================#
|                                                                                               |
| Handmade Lite is an educational game engine, written by Karsten Vermeulen for the purposes of |
| educating other fellow programmers, programming students and anyone else wishing to learn     |
| about game development, C++ and OOP. The engine, class design and overall structure is by no  |
| means perfect and there is certainly room for improvement. Feel free to use, copy, break,     |
| update and do as you wish with this code - it is there, free, for all!                        |
|																							    |
| Designed to teach. Made from scratch. Built by hand.							                |
|																							    |
#===============================================================================================#
|	                                                                                            |
| Please note, that this project is not open source and therefore has no license affiliated     |
| with it. However, feel free to use the engine to build your own game or learn from the code.  |
| Handmade Lite is an educational tool, designed to be used as such. Please be respectful and   |
| do not distribute the engine or its code as your own work. You may alter or tweak the engine  |
| code as a learning experience and you may also 'borrow' some code and functionality and use   |
| it to create your own game engine or game.                                                    |
|	                                                                                            |
#===============================================================================================#
|                                                                                               |
| If you like Handmade Lite and wish to show your support, if you have any questions about      |
| the project, or if you just want to reach out, please do get in touch:                        |
|																						        |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'Input' source files last updated in May 2020   							                    |
#==============================================================================================*/

#include <string>
#include <SDL.h>
#include "AABB.h"
#include "Sphere.h"

class Input
{

public:

	enum class ButtonState { UP, DOWN };
	enum class CursorState { ON = 1, OFF = 0, SHOW = 1, HIDE = 0 };
	enum class CursorType  { ARROW, IBEAM, WAIT, CROSSHAIR, WAIT_ARROW, NO = 10, HAND = 11 };

public:

	static Input* Instance();

public:

	bool IsXClicked() const;
	bool IsKeyPressed() const;
	const Uint8* GetKeyStates() const;
	bool IsMouseColliding(const AABB& bound) const;
	bool IsMouseColliding(const Sphere& bound) const;

public:

	ButtonState GetLeftButtonState() const;
	ButtonState GetMiddleButtonState() const;
	ButtonState GetRightButtonState() const;

	SDL_Point GetMouseWheel() const;
	SDL_Point GetMouseMotion() const;
	SDL_Point GetMousePosition() const;

	const std::string& GetInput() const;

	void SetMousePosition(int x, int y);
	void SetMouseCursorType(CursorType cursorType = CursorType::ARROW);
	void SetMouseCursorState(CursorState cursorEnabled = CursorState::ON, 
		                     CursorState cursorVisible = CursorState::SHOW);

public:

	void Update();
	void FlushInput() { m_input.clear(); }

private:

	Input();
	Input(const Input&);
	Input& operator=(Input&);

private:

	bool m_isXClicked;
	bool m_isKeyPressed;
	std::string m_input;

	const Uint8* m_keyStates;
	
	SDL_Cursor* m_cursor;

	ButtonState m_leftButtonState;
	ButtonState m_middleButtonState;
	ButtonState m_rightButtonState;

	SDL_Point m_mouseWheel;
	SDL_Point m_mouseMotion;
	SDL_Point m_mousePosition;
	
};

#endif