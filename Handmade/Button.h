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
		Default = 0,
		Hover = 1,
		Clicked = 2
	};

	Button(const SDL_Point& dimension,
		const SDL_Rect& textureDimension,
		const std::string& filename = "");
	virtual ~Button() {}

	virtual void Update(int deltaTime) override;
	virtual bool Render() override;

private:

	State m_state;
	Texture m_texture;
	SDL_Rect m_collider;

};