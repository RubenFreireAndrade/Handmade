#pragma once
#include <string>
#include "BoxCollider.h"
#include "GameObject.h"
#include "Texture.h"

class Button : public GameObject
{

public:

	enum class State
	{
		Default = 0,
		Hover = 1
	};

	Button(int width = 1, int height = 1,
		int textureColumns = 1, int textureRows = 1,
		int textureWidth = 1, int textureHeight = 1,
		const std::string& filename = "");
	virtual ~Button() {}

	virtual void Update(int deltaTime) override;
	virtual bool Render() override;

private:

	State m_state;
	Texture m_texture;
	BoxCollider m_collider;

};