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

	m_isWindowClosed = false;

	m_isKeyPressed = false;
	m_isMouseClicked = false;

	m_modifier = HM_MOD_NONE;

	m_mouseButton = HM_MOUSE_NONE;

	m_mouseMotion = std::pair<int, int>(0, 0);
	m_mousePosition = std::pair<int, int>(0, 0);
	
	m_mouseWheel = 0;
	
}
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag stating if X has been clicked
//------------------------------------------------------------------------------------------------------
bool Input::IsWindowClosed() const
{

	return m_isWindowClosed;

}
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag stating if an arbitrary key is pressed down or not
//------------------------------------------------------------------------------------------------------
bool Input::IsKeyPressed() const
{

	return m_isKeyPressed;

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
//predicate function that returns flag stating if an arbitrary mouse button is clicked or not
//------------------------------------------------------------------------------------------------------
bool Input::IsMouseClicked() const
{

	return m_isMouseClicked;

}
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag stating if one or more mouse buttons are clicked
//these are any of the standard three mouse buttons and we use a binary OR to combine buttons
//a maximum of two buttons may be clicked and if one button is clicked, mod_2 will be '0'
//------------------------------------------------------------------------------------------------------
bool Input::IsMouseClicked(int mouseButton_1, int mouseButton_2) const
{

	return m_mouseButton == (mouseButton_1 | mouseButton_2);

}
//------------------------------------------------------------------------------------------------------
//getter function that returns x and y motion/position of mouse within a pair
//in the client code, the user needs to store the returned values within a pair (can use auto)
//if individual values are required (eg. the x coordinate or y motion within an algorithm) 
//then we just need to access the first/second element of the returned pair
//------------------------------------------------------------------------------------------------------
std::pair<int, int> Input::GetMouseMotion() const
{

	return m_mouseMotion;

}
std::pair<int, int> Input::GetMousePosition() const
{

	return m_mousePosition;

}
int Input::GetMouseWheel() const
{

	return m_mouseWheel;

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
//setter function that enables, disables, shows or hides the mouse cursor
//------------------------------------------------------------------------------------------------------
void Input::SetCursorState(bool isCursorEnabled, bool isCursorVisible)
{

	SDL_ShowCursor(static_cast<int>(isCursorVisible));
	SDL_SetRelativeMouseMode(static_cast<SDL_bool>(isCursorEnabled));
	
}
//------------------------------------------------------------------------------------------------------
//function that processes all keyboard and mouse events
//------------------------------------------------------------------------------------------------------
void Input::Update()
{

	//variable to store SDL event data
	SDL_Event events;

	//reset window quitting flag 
	m_isWindowClosed = false;

	//reset mouse motion so that it's processed from scratch
	m_mouseMotion.first = 0;
	m_mouseMotion.second = 0;

	//reset mouse wheel so that it's processed from scratch
	m_mouseWheel = 0;

	//check for events on SDL event queue
	//keep this loop running until all events have been processed
	while(SDL_PollEvent(&events))
	{
			
		//check which type of event occurred and process accordingly
		switch(events.type)
		{
		
			//top right X on game window has been clicked
			//which signals that we need to close the window
			//this only works if the application is not fullscreen
			case SDL_QUIT:
			{
				m_isWindowClosed = true;
				break;
			}
		
			//a key is released so we set the flag and the printable key value to false/null
			//the modifier value is also stored which is 0 if no modifiers are pressed
			//if a modifier key is still being pressed then that modifier value is stored
			//for example if we pressed CTRL+ATL and released ALT, we store the value of CTRL
			case SDL_KEYUP: 
			{
				m_isKeyPressed = false;
				m_key = SDLK_UNKNOWN;
				m_modifier = events.key.keysym.mod;
				break;
			}
		
			//a key is pressed so we set the flag and the printable key value to true/ASCII (keycode)
			//we do a binary OR with the current modifier value to combine them
			//for example if we press LSHIFT+RSHIFT, we combine 0001 and 0010, i.e. 0001 | 0010 = 0011
			case SDL_KEYDOWN:
			{
				m_isKeyPressed = true;
				m_key = events.key.keysym.sym;
				m_modifier |= events.key.keysym.mod;
				break;
			}

			//the mouse was moved so we store both the position and the motion value
			//moving left/right on the x axis creates a negative/positive value, respectively
			//moving up/down on the y axis creates a negative/positive value, respectively
			case SDL_MOUSEMOTION:
			{
				m_mousePosition.first = events.motion.x;
				m_mousePosition.second = events.motion.y;
				
				m_mouseMotion.first = events.motion.xrel;
				m_mouseMotion.second = events.motion.yrel;
				break;
			}

			//the mouse wheel was moved so store the motion value. We use only the 'y'
			//scrolling up returns a positive value and scrolling down a negative value
			case SDL_MOUSEWHEEL:
			{
				m_mouseWheel = events.wheel.y;
			}

			//a mouse button was released so we first store the position of the mouse cursor
			//then we check what button was released and perform a binary XOR to 'undo' a button
			//for example if LEFT+RIGHT buttons are pressed we have a combo of 0001 and 0100 = 0101
			//if we release the RIGHT button we essentially do 0101 ^= 0100 = 0001 (LEFT only)
			case SDL_MOUSEBUTTONUP: 
			{

				m_isMouseClicked = false;
				m_mousePosition.first = events.motion.x;
				m_mousePosition.second = events.motion.y;

				switch (events.button.button)
				{
					case SDL_BUTTON_LEFT:   { m_mouseButton ^= HM_MOUSE_LEFT; break;   }
					case SDL_BUTTON_MIDDLE: { m_mouseButton ^= HM_MOUSE_MIDDLE; break; }
					case SDL_BUTTON_RIGHT:  { m_mouseButton ^= HM_MOUSE_RIGHT; break;  }
				}

				break;

			}

			//a mouse button was pressed so we first store the position of the mouse cursor
			//then we check what button was released and perform a binary OR to combine buttons
			//for example if LEFT+RIGHT buttons are pressed we have a combo of 0001 | 0100 = 0101
			case SDL_MOUSEBUTTONDOWN:
			{

				m_isMouseClicked = true;
				m_mousePosition.first = events.motion.x;
				m_mousePosition.second = events.motion.y;

				switch (events.button.button)
				{
					case SDL_BUTTON_LEFT:   { m_mouseButton |= HM_MOUSE_LEFT; break;   }
					case SDL_BUTTON_MIDDLE: { m_mouseButton |= HM_MOUSE_MIDDLE; break; }
					case SDL_BUTTON_RIGHT:  { m_mouseButton |= HM_MOUSE_RIGHT; break;  }
				}

				break;

			}

		}

	}

}