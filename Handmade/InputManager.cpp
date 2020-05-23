#include "InputManager.h"
#include "ScreenManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
InputManager::InputManager()
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
bool InputManager::IsXClicked() const
{

	return m_isXClicked;

}
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag stating if a key has been pressed
//------------------------------------------------------------------------------------------------------
bool InputManager::IsKeyPressed() const
{

	return m_isKeyPressed;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns pointer to array of key states
//------------------------------------------------------------------------------------------------------
const Uint8* InputManager::GetKeyStates() const
{

	return m_keyStates;

}
//------------------------------------------------------------------------------------------------------
//predicate function that checks if mouse cursor collides with passed box bound
//------------------------------------------------------------------------------------------------------
bool InputManager::IsMouseColliding(const AABB& bound) const
{

	//create a temporary bounding box to represent mouse cursor
	AABB tempBound;

	//set mouse cursor bounds of 1x1 based on mouse position
	tempBound.SetPosition(static_cast<int>(m_mousePosition.x), 
		                  static_cast<int>(m_mousePosition.y));
	tempBound.SetDimension(1, 1);

	//return flag based on if mouse collides with bound
	return tempBound.IsColliding(bound);

}
//------------------------------------------------------------------------------------------------------
//predicate function that checks if mouse cursor collides with passed sphere bound
//------------------------------------------------------------------------------------------------------
bool InputManager::IsMouseColliding(const Sphere& bound) const
{

	//create a temporary sphere bound to represent mouse cursor
	Sphere tempBound;

	//set mouse cursor radius of 1 based on mouse position
	tempBound.SetPosition(static_cast<int>(m_mousePosition.x), 
		                  static_cast<int>(m_mousePosition.y));
	tempBound.SetRadius(1);

	//return flag based on if mouse collides with bound
	return tempBound.IsColliding(bound);

}
//------------------------------------------------------------------------------------------------------
//getter function that returns state of left mouse button
//------------------------------------------------------------------------------------------------------
InputManager::ButtonState InputManager::GetLeftButtonState() const
{

	return m_leftButtonState;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns state of middle mouse button
//------------------------------------------------------------------------------------------------------
InputManager::ButtonState InputManager::GetMiddleButtonState() const
{

	return m_middleButtonState;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns state of right mouse button
//------------------------------------------------------------------------------------------------------
InputManager::ButtonState InputManager::GetRightButtonState() const
{

	return m_rightButtonState;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns motion value of mouse wheel movement
//------------------------------------------------------------------------------------------------------
SDL_Point InputManager::GetMouseWheel() const
{

	return m_mouseWheel;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns motion value of mouse movement
//------------------------------------------------------------------------------------------------------
SDL_Point InputManager::GetMouseMotion() const
{

	return m_mouseMotion;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns position of mouse
//------------------------------------------------------------------------------------------------------
SDL_Point InputManager::GetMousePosition() const
{

	return m_mousePosition;

}

const std::string& InputManager::GetInput() const
{
	return m_input;
}

//------------------------------------------------------------------------------------------------------
//setter function that places mouse cursor at passed position
//------------------------------------------------------------------------------------------------------
void InputManager::SetMousePosition(int x, int y)
{

	SDL_WarpMouseInWindow(TheScreen::Instance()->GetWindow(), x, y);

}
//------------------------------------------------------------------------------------------------------
//setter function that creates a system mouse cursor 
//------------------------------------------------------------------------------------------------------
void InputManager::SetMouseCursorType(CursorType cursorType)
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
void InputManager::SetMouseCursorState(CursorState cursorEnabled, CursorState cursorVisible)
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
void InputManager::Update()
{

	//variable to store SDL event data
	SDL_Event events;

	//if no events are occuring, then put CPU to sleep for a millisecond
	//this prevents CPU from running too much 
	if(!SDL_PollEvent(&events)) 
	{
		SDL_Delay(1);
	}
	
	//if previous event was valid, push it back on queue to be processed
	else 
	{
		SDL_PushEvent(&events);
	}

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

				//erase the last character if a backspace is pressed
				if (events.key.keysym.sym == SDLK_BACKSPACE && m_input.size() > 0)
				{
					m_input.erase(m_input.end() - 1);
				}
				
				//otherwise enter all keys (except the enter key!)
				else if(events.key.keysym.sym != SDLK_RETURN)
				{
					m_input += events.key.keysym.sym;
				}

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