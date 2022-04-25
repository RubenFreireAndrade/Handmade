#include "Button.h"

Button::Button(int width, int height,
	int textureColumns, int textureRows,
	int textureWidth, int textureHeight,
	const std::string& filename)
{
	m_texture.Load(filename, filename);
	m_texture.SetDimension(width, height);
	m_texture.SetSourceDimension(textureColumns, textureRows, textureWidth, textureHeight);
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