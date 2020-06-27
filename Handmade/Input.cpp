#include "Input.h"
#include "Screen.h"

#include <iostream>
#include <algorithm>

//------------------------------------------------------------------------------------------------------
//static function that will create an instance of this Input object and return its address
//------------------------------------------------------------------------------------------------------
Input* Input::Instance()
{

	static Input* inputObject = new Input();
	return inputObject;

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
Input::Input()
{

	m_key = ' ';
	m_cursor = nullptr;
	m_isXClicked = false;
	m_isKeyDown = false;

	m_modifier = HM_MOD_NONE;

	m_mouseWheel = { 0, 0 };
	m_mouseMotion = { 0, 0 };
	m_mousePosition = { 0, 0 };

	m_leftButtonState = ButtonState::UP;
	m_middleButtonState = ButtonState::UP;
	m_rightButtonState = ButtonState::UP;
	
}
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag stating if X has been clicked
//------------------------------------------------------------------------------------------------------
bool Input::IsXClicked() const
{

	return m_isXClicked;

}
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag stating if an arbitrary key is pressed down or not
//------------------------------------------------------------------------------------------------------
bool Input::IsKeyDown() const
{

	return m_isKeyDown;

}
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag stating if a key has been pressed
//here we store the state of keyboard in array and query the array using index value
//the index value corresponds to the physical key code, i.e. the scancode
//------------------------------------------------------------------------------------------------------
bool Input::IsKeyPressed(int keyCode) const
{

	const Uint8* m_keyStates = SDL_GetKeyboardState(nullptr);
	return m_keyStates[keyCode];

}
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag stating if one or more modifier keys are pressed
//these keys include CTRL, ALT, SHIFT, etc and we use a binary OR to combine keys
//a maximum of two modifier keys may be pressed and if one modifier is pressed, mod_2 will be '0'
//------------------------------------------------------------------------------------------------------
bool Input::IsModifierPressed(int modifier_1, int modifier_2) const
{

	return m_modifier == (modifier_1 | modifier_2);

}
//------------------------------------------------------------------------------------------------------
//function that returns ASCII code of the key that's currently pressed down
//this is handy for printing out the characters if needed. Can be used to query as well
//------------------------------------------------------------------------------------------------------
char Input::GetKey()
{

	return m_key;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns state of left mouse button
//------------------------------------------------------------------------------------------------------
Input::ButtonState Input::GetLeftButtonState() const
{

	return m_leftButtonState;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns state of middle mouse button
//------------------------------------------------------------------------------------------------------
Input::ButtonState Input::GetMiddleButtonState() const
{

	return m_middleButtonState;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns state of right mouse button
//------------------------------------------------------------------------------------------------------
Input::ButtonState Input::GetRightButtonState() const
{

	return m_rightButtonState;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns motion value of mouse wheel movement
//------------------------------------------------------------------------------------------------------
SDL_Point Input::GetMouseWheel() const
{

	return m_mouseWheel;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns motion value of mouse movement
//------------------------------------------------------------------------------------------------------
SDL_Point Input::GetMouseMotion() const
{

	return m_mouseMotion;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns position of mouse
//------------------------------------------------------------------------------------------------------
SDL_Point Input::GetMousePosition() const
{

	return m_mousePosition;

}
//------------------------------------------------------------------------------------------------------
//setter function that places mouse cursor at passed position
//------------------------------------------------------------------------------------------------------
void Input::SetMousePosition(int x, int y)
{

	SDL_WarpMouseInWindow(Screen::Instance()->GetWindow(), x, y);

}
//------------------------------------------------------------------------------------------------------
//setter function that creates a system mouse cursor 
//------------------------------------------------------------------------------------------------------
void Input::SetCursorType(CursorType cursorType)
{

	//first destroy old cursor object from memory
	SDL_FreeCursor(m_cursor);

	//based on type of cursor value passed, create mouse cursor using SDL ID flag value 
	m_cursor = SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(cursorType));
	
	//use cursor pointer to assign cursor to SDL
	SDL_SetCursor(m_cursor);

}
//------------------------------------------------------------------------------------------------------
//setter function that enables, disables, shows or hides the mouse cursor
//------------------------------------------------------------------------------------------------------
void Input::SetCursorState(CursorState cursorEnabled, CursorState cursorVisible)
{

	//if mouse cursor is enabled then check if it's visible  
	//and display the cursor accordingly, and keep the mouse 
	//cursor within the window border as long as it's enabled
	if (static_cast<bool>(cursorEnabled))
	{
		
		if (static_cast<bool>(cursorVisible))
		{
			SDL_ShowCursor(1);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		else
		{
			SDL_ShowCursor(0);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}

	}

	//if mouse cursor is disabled then hide it and free it from the window border
	else
	{
		SDL_ShowCursor(0);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
	
}
//------------------------------------------------------------------------------------------------------
//function that processes all keyboard and mouse events
//------------------------------------------------------------------------------------------------------
void Input::Update()
{

	//variable to store SDL event data
	SDL_Event events;

	//reset window quitting flag 
	m_isXClicked = false;

	//reset mouse motion so that it's processed from scratch
	m_mouseMotion.x = 0;
	m_mouseMotion.y = 0;

	//reset mouse wheel so that it's processed from scratch
	m_mouseWheel.x = 0;
	m_mouseWheel.y = 0;

	//check for events on SDL event queue
	//keep this loop running until all events have been processed
	while(SDL_PollEvent(&events))
	{
			
		//check which type of event occurred and process accordingly
		switch(events.type)
		{
		
			//top right X on game window has been clicked
			case SDL_QUIT:
			{
				m_isXClicked = true;
				break;
			}
		
			//a key is released so we set the flag and the printable key value to false/null
			//the modifier value is also stored which is 0 if no modifiers are pressed
			//if a modifier key is still being pressed then that modifier value is stored
			//for example if we pressed CTRL+ATL and released ALT, we store the value of CTRL
			case SDL_KEYUP: 
			{
				m_isKeyDown = false;
				m_key = SDLK_UNKNOWN;
				m_modifier = events.key.keysym.mod;
				break;
			}
		
			//a key is pressed so we set the flag and the printable key value to true/ASCII (keycode)
			//we do a binary OR with the current modifier value to combine them
			//for example if we press LSHIFT+RSHIFT, we combine 0001 and 0010, i.e. 0001 | 0010 = 0011
			case SDL_KEYDOWN:
			{
				m_isKeyDown = true;
				m_key = events.key.keysym.sym;
				m_modifier |= events.key.keysym.mod;
				break;
			}

			//the mouse was moved 
			//set the position and mouse motion value ..
			case SDL_MOUSEMOTION:
			{
				m_mousePosition.x = events.motion.x;
				m_mousePosition.y = events.motion.y;
				m_mouseMotion.x = events.motion.xrel;
				m_mouseMotion.y = events.motion.yrel;
				break;
			}

			//the mouse wheel was moved  ..
			case SDL_MOUSEWHEEL:
			{
				m_mouseWheel.x = events.wheel.x;
				m_mouseWheel.y = events.wheel.y;
			}

			//a mouse button was clicked or released ..
			case SDL_MOUSEBUTTONUP: 
			case SDL_MOUSEBUTTONDOWN:
			{
				
				//set position of mouse
				m_mousePosition.x = events.motion.x;
				m_mousePosition.y = events.motion.y;
				
				//temporarily store button state for assigning below
				ButtonState state = ((events.button.state == SDL_PRESSED) ? ButtonState::DOWN : ButtonState::UP);

				//based on which of the three mouse buttons was pressed 
				//or released, assign flag to button's state variable
				switch(events.button.button)
				{
				
					case SDL_BUTTON_LEFT:
					{
						m_leftButtonState = state;
						break;
					}
				
					case SDL_BUTTON_MIDDLE:
					{
						m_middleButtonState = state;
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						m_rightButtonState = state;
						break;
					}
				
					break;

				}

				break;

			}

		}

	}

}