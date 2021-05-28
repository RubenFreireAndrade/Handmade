#include <assert.h>
#include "Screen.h"
#include "Text.h"
#include "Utility.h"

std::map<std::string, TTF_Font*>* Text::s_fonts = new std::map<std::string, TTF_Font*>;

//======================================================================================================
bool Text::Initialize()
{
	if (TTF_Init() == -1)
	{
		Utility::Log(MESSAGE_BOX,
			"Font sub-system did not initialize properly.", Utility::Severity::FAILURE);
		return false;
	}

	return true;
}
//======================================================================================================
bool Text::Load(const std::string& filename, const std::string& mapIndex, FontSize fontSize)
{
	//Font data already loaded in memory
	assert(s_fonts->find(mapIndex) == s_fonts->end());

	TTF_Font* font = TTF_OpenFont(filename.c_str(), static_cast<int>(fontSize));

	if (!font)
	{
		Utility::Log(MESSAGE_BOX,
			"File could not be loaded.", Utility::Severity::FAILURE);
		return false;
	}

	(*s_fonts)[mapIndex] = font;

	return true;
}
//======================================================================================================
void Text::Unload(const std::string& mapIndex)
{
	if (!mapIndex.empty())
	{
		auto it = s_fonts->find(mapIndex);

		//Font data not found, so make sure to enter a valid ID
		assert(it != s_fonts->end());

		TTF_CloseFont(it->second);
		s_fonts->erase(it);
	}

	else
	{
		for (auto it = s_fonts->begin(); it != s_fonts->end(); it++)
		{
			TTF_CloseFont(it->second);
		}

		s_fonts->clear();
	}
}
//======================================================================================================
void Text::Shutdown()
{
	TTF_Quit();
}
//======================================================================================================
Text::Text()
{
	m_font = nullptr;
	m_texture = nullptr;
	m_textSize = { 0, 0 };
	m_color = { 255, 255, 255 };
}
//======================================================================================================
Text::Text(const Text& copy)
{
	m_text = copy.m_text;
	m_font = copy.m_font;
	m_color = copy.m_color;
	m_textSize = copy.m_textSize;
	m_texture = nullptr;
	CreateText();
}
//======================================================================================================
Text::~Text()
{
	SDL_DestroyTexture(m_texture);
}
//======================================================================================================
const SDL_Point& Text::GetSize() const
{
	return m_textSize;
}
//======================================================================================================
const std::string& Text::GetText() const
{
	return m_text;
}
//======================================================================================================
void Text::SetSize(int width, int height)
{
	m_textSize.x = width;
	m_textSize.y = height;
}
//======================================================================================================
void Text::SetText(const std::string& text)
{
	m_text = text;
	CreateText();
}
//======================================================================================================
void Text::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	CreateText();
}
//======================================================================================================
bool Text::SetFont(const std::string& mapIndex)
{
	auto it = s_fonts->find(mapIndex);

	//Font data not found, so make sure to enter a valid ID
	assert(it != s_fonts->end());

	m_font = (*it).second;
	return true;
}
//======================================================================================================
void Text::Render(int positionX, int positionY)
{
	SDL_Rect dst;

	//assign dimension of rectangular block to 
	//which text will be rendered to on screen
	dst.x = positionX;
	dst.y = positionY;
	dst.w = m_textSize.x;
	dst.h = m_textSize.y;

	//render the text object using all values passed and determined above
	SDL_RenderCopy(Screen::Instance()->GetRenderer(), m_texture, nullptr, &dst);
}
//======================================================================================================
void Text::CreateText()
{
	//This means the font has not properly been loaded
	assert(m_font != nullptr);

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