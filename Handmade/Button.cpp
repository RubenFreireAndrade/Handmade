#include "Button.h"

Button::Button(const SDL_Point& dimension,
	const SDL_Rect& textureDimension,
	const std::string& filename)
{
	m_texture.Load(filename, filename);
	m_texture.SetDimension(dimension.x, dimension.y);
	m_texture.SetSourceDimension(textureDimension.x, 
		textureDimension.y, 
		textureDimension.w, 
		textureDimension.h);
	m_texture.SetTexture(filename);
	
	m_texture.SetCel(1, 1);
}

void Button::Update(int deltaTime)
{

}

bool Button::Render()
{
	m_texture.Render(100, 100);
	return true;
}