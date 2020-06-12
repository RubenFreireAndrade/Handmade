#include "Input.h"
#include "Screen.h"

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

	m_cursor = nullptr;
	m_keyStates = nullptr;
	m_isXClicked = false;
	m_isKeyPressed = false;

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
//predicate function that returns flag stating if a key has been pressed
//------------------------------------------------------------------------------------------------------
bool Input::IsKeyPressed() const
{

	return m_isKeyPressed;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns pointer to array of key states
//------------------------------------------------------------------------------------------------------
const Uint8* Input::GetKeyStates() const
{

	return m_keyStates;

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

	//store state of keyboard in array
	m_keyStates = SDL_GetKeyboardState(nullptr);

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
		
			//a key is pressed 
			case SDL_KEYUP: 
			{
				m_isKeyPressed = false;
				break;
			}
		
			//a key is released 
			//here we store all entered keyboard keys into a 
			//string for possible text input in the client code
			case SDL_KEYDOWN:
			{
				m_isKeyPressed = true;
				break;
			}

			//the mouse was moved 
			//set the position and mouse motion value
			case SDL_MOUSEMOTION:
			{
				m_mousePosition.x = events.motion.x;
				m_mousePosition.y = events.motion.y;
				m_mouseMotion.x = events.motion.xrel;
				m_mouseMotion.y = events.motion.yrel;
				break;
			}

			//the mouse wheel was moved 
			case SDL_MOUSEWHEEL:
			{
				m_mouseWheel.x = events.wheel.x;
				m_mouseWheel.y = events.wheel.y;
			}

			//a mouse button was clicked or released
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