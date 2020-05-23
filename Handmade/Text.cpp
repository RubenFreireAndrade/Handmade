#include "Screen.h"
#include "Text.h"
#include "TextureManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Text::Text()
{

	m_font = nullptr;
	m_texture = nullptr;
	m_textSize = { 0, 0 };
	m_color = { 255, 255, 255 };

}

SDL_Point Text::GetSize() const
{
	return m_textSize;
}

//------------------------------------------------------------------------------------------------------
//setter function that assigns size of text object
//------------------------------------------------------------------------------------------------------
void Text::SetSize(int width, int height)
{

	m_textSize.x = width;
	m_textSize.y = height;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns string text and creates text object
//------------------------------------------------------------------------------------------------------
void Text::SetText(const std::string& text)
{

	m_text = text;
	CreateText();

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns text color and creates text object
//------------------------------------------------------------------------------------------------------
void Text::SetColor(Uint8 r, Uint8 g, Uint8 b)
{

	m_color.r = r;
	m_color.g = g;
	m_color.b = b;

	CreateText();

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns font style to text object based on index value passed
//------------------------------------------------------------------------------------------------------
void Text::SetFont(const std::string& mapIndex)
{

	m_font = TextureManager::Instance()->GetFont(mapIndex);

}
//------------------------------------------------------------------------------------------------------
//function that draws the actual text on screen
//------------------------------------------------------------------------------------------------------
void Text::Draw(int xPosition, int yPosition)
{

	SDL_Rect dst;

	//assign dimension of rectangular block to which text will be rendered to on screen
	dst.x = xPosition;
	dst.y = yPosition;
	dst.w = m_textSize.x;
	dst.h = m_textSize.y;

	//render the text object using all values passed and determined above
	SDL_RenderCopy(Screen::Instance()->GetRenderer(), m_texture, nullptr, &dst);

}
//------------------------------------------------------------------------------------------------------
//function that creates the actual text object
//------------------------------------------------------------------------------------------------------
void Text::CreateText()
{

	//create text object using font style, text string and color 
	//value and store in a temporary pointer to be used below
	SDL_Surface* textSurface = TTF_RenderText_Blended(m_font, m_text.c_str(), m_color);

	//free the old texture first before creating a new
	//texture object from surface object loaded above
	SDL_DestroyTexture(m_texture);
	m_texture = SDL_CreateTextureFromSurface(Screen::Instance()->GetRenderer(), textSurface);

	//remove temporary SDL surface object as we don't need it anymore
	SDL_FreeSurface(textSurface);

}