#pragma once
#include <map>
#include <memory>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

typedef std::map<std::string, TTF_Font*> Fonts;

class Text
{

public:

	enum class FontSize
	{
		Small = 72,
		Medium = 144,
		Large = 300
	};

	static bool Initialize();
	static bool Load(const std::string& filename,
		const std::string& tag,
		FontSize fontSize = FontSize::Small);
	static void Unload(const std::string& tag = "");
	static void Shutdown();

	Text() {}
	Text(const Text& copy);
	~Text();

	const SDL_Point& GetSize() const;
	const std::string& GetString() const;

	void SetSize(int width, int height);
	bool SetFont(const std::string& tag);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	void SetString(const std::string& string);

	void Render(int x = 0, int y = 0);

private:

	void CreateText();

	std::string m_string;
	bool m_isDirty{ true };
	SDL_Point m_textSize{ 0, 0 };

	TTF_Font* m_font{ nullptr };
	SDL_Texture* m_texture{ nullptr };
	SDL_Color m_color{ 255, 255, 255 };

	static std::string s_rootFolder;
	static std::unique_ptr<Fonts> s_fonts;

};