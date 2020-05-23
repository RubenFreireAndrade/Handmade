#include "Sprite.h"
#include "Screen.h"
#include "TextureManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Sprite::Sprite()
{

	m_textureIndex = 0;
	m_texture = nullptr;
	m_textureCell = { 0, 0 };
	m_spriteDimension = { 0, 0 };
	m_textureDimension = { 0, 0, 0, 0 };

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns specific position of image cell in texture
//------------------------------------------------------------------------------------------------------
void Sprite::SetTextureCell(int column, int row)
{

	m_textureCell.x = column;
	m_textureCell.y = row;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns texture image to sprite based on index value passed
//------------------------------------------------------------------------------------------------------
void Sprite::SetTexture(const std::string& mapIndex)
{

	m_texture = TextureManager::Instance()->GetTexture(mapIndex);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns size of sprite
//------------------------------------------------------------------------------------------------------
void Sprite::SetSpriteDimension(int width, int height)
{

	m_spriteDimension.x = width;
	m_spriteDimension.y = height;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns dimension size of texture and pixel size of each cell
//------------------------------------------------------------------------------------------------------
void Sprite::SetTextureDimension(int column, int row, int width, int height)
{

	m_textureDimension.x = column;
	m_textureDimension.y = row;
	m_textureDimension.w = width;
	m_textureDimension.h = height;

}
//------------------------------------------------------------------------------------------------------
//function that creates and draws the actual sprite on screen
//------------------------------------------------------------------------------------------------------
void Sprite::Draw(int xPosition, int yPosition, double angle, FlipType flipType)
{

	//aquire index value of specific texture cell to "cut out" using a basic formula 
	m_textureIndex = (m_textureCell.y * m_textureDimension.x) + m_textureCell.x;

	//use internal blitting function to draw the sprite on screen
	BlitSprite(xPosition, yPosition, angle, flipType);

}
//------------------------------------------------------------------------------------------------------
//function that calculates the source and destination sections of the sprite and screen and renders
//------------------------------------------------------------------------------------------------------
void Sprite::BlitSprite(int xPosition, int yPosition, double angle, FlipType flipType)
{

	//variables to store rectangular dimensions for the source 
	//sprite and destination portion of the screen to render to 
	SDL_Rect src;
	SDL_Rect dst;

	//use modulo and divide with the texture index to get exact cell block XY coordinates
	//to "cut out" and assign all of this as well as width and height to the source rect
	src.x = (m_textureIndex % m_textureDimension.x) * m_textureDimension.w;
	src.y = (m_textureIndex / m_textureDimension.x) * m_textureDimension.h;
	src.w = m_textureDimension.w;
	src.h = m_textureDimension.h;

	//assign dimension of rectangular block to which sprite will be rendered to on screen
	dst.x = xPosition;
	dst.y = yPosition;
	dst.w = m_spriteDimension.x;
	dst.h = m_spriteDimension.y;

	//if sprite needs to be rotated, use the centre of the sprite as its centre of rotation
	SDL_Point centrePoint;
	centrePoint.x = m_spriteDimension.x / 2;
	centrePoint.y = m_spriteDimension.y / 2;

	//render the sprite using all values passed and determined above
	SDL_RenderCopyEx(Screen::Instance()->GetRenderer(), 
		             m_texture, &src, &dst, angle, &centrePoint, static_cast<SDL_RendererFlip>(flipType));

}