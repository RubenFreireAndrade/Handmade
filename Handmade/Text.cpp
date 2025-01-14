#include <assert.h>
#include "Screen.h"
#include "Text.h"
#include "Utility.h"

std::string Text::s_rootFolder = "Assets/Fonts/";
std::unique_ptr<Fonts> Text::s_fonts = std::make_unique<Fonts>();

//======================================================================================================
bool Text::Initialize()
{
	if (TTF_Init() == -1)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error initializing the font sub-system.", Utility::Severity::Failure);
		return false;
	}

	return true;
}
//======================================================================================================
bool Text::Load(const std::string& filename, const std::string& tag, FontSize fontSize)
{
	assert(s_fonts->find(tag) == s_fonts->end());

	TTF_Font* font = TTF_OpenFont((s_rootFolder + filename).c_str(), static_cast<int>(fontSize));

	if (!font)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error loading font file \"" + (s_rootFolder + filename) + "\"\n\n"
			"Possible causes could be a corrupt or missing file. Another reason could be "
			"that the filename and/or path are incorrectly spelt.", Utility::Severity::Failure);
		return false;
	}

	s_fonts->insert(std::pair<std::string, TTF_Font*>(tag, font));
	return true;
}
//======================================================================================================
void Text::Unload(const std::string& tag)
{
	if (!tag.empty())
	{
		auto it = s_fonts->find(tag);
		assert(it != s_fonts->end());
		TTF_CloseFont(it->second);
		s_fonts->erase(it);
	}

	else
	{
		for (const auto& font : *s_fonts)
		{
			TTF_CloseFont(font.second);
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
Text::Text(const Text& copy)
{
	m_texture = nullptr;
	m_font = copy.m_font;
	m_color = copy.m_color;
	m_string = copy.m_string;
	m_textSize = copy.m_textSize;
	m_isDirty = true;
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
const std::string& Text::GetString() const
{
	return m_string;
}
//======================================================================================================
void Text::SetSize(int width, int height)
{
	m_textSize.x = width;
	m_textSize.y = height;
}
//======================================================================================================
void Text::SetString(const std::string& string)
{
	m_string = string;
	m_isDirty = true;
}
//======================================================================================================
void Text::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	m_isDirty = true;
}
//======================================================================================================
bool Text::SetFont(const std::string& tag)
{
	auto it = s_fonts->find(tag);
	assert(it != s_fonts->end());
	m_font = (*it).second;
	m_isDirty = true;
	return true;
}
//======================================================================================================
void Text::Render(int x, int y)
{
	SDL_Rect dst;

	dst.x = x;
	dst.y = y;
	dst.w = m_textSize.x;
	dst.h = m_textSize.y;

	if (m_isDirty)
	{
		CreateText();
		m_isDirty = false;
	}

	SDL_RenderCopy(Screen::Instance()->GetRenderer(), m_texture, nullptr, &dst);
}
//======================================================================================================
void Text::CreateText()
{
	assert(m_font != nullptr);
	SDL_Surface* textSurface = TTF_RenderText_Blended(m_font, m_string.c_str(), m_color);

	SDL_DestroyTexture(m_texture);
	m_texture = SDL_CreateTextureFromSurface(Screen::Instance()->GetRenderer(), textSurface);

	SDL_FreeSurface(textSurface);
}