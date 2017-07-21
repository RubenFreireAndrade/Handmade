/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : July 2017

  -----------------------------------------------------------------------------------------------

- This game state controls the main state of the game. It consists of a background object which
  will render the main bacdrop image and play the correct background music. Other game objects 
  can be added to the vector as needed. 

- The Update() function will update all the game objects in the vector, as long as they are 
  active. The Draw() routine draws all the game objects in the vector, as long as they are active
  and visible. 

*/

#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <vector>
#include "Background.h"
#include "GameObject.h"
#include "GameState.h"

class PlayState : public GameState
{

public:

	PlayState(GameState* state);
	virtual ~PlayState() {}

public:

	virtual bool OnEnter();
	virtual bool Update();
	virtual bool Draw();
	virtual void OnExit();

private :

	Background* m_image;
	std::vector<GameObject*> m_gameObjects;
	
};

#endif