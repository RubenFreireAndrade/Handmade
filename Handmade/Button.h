#pragma once
#include <string>
#include <SDL.h>
#include "BoxCollider.h"
#include "GameObject.h"
#include "Texture.h"

class Button : public GameObject
{

public:

	enum class State
	{
		Default = 1,
		Hover = 2,
		Clicked = 3
	};

	Button(const SDL_Point& position,
		const SDL_Point& dimension,
		const SDL_Rect& textureDimension,
		const std::string& filename = "",
		bool hasClickState = false,
		int rowIndex = 1);
	virtual ~Button() {}

	virtual void Update(int deltaTime) override;
	virtual bool Render() override;

private:

	State m_state;
	Texture m_texture;
	SDL_Rect m_collider;

	int m_rowIndex;
	bool m_hasClickState;

};