#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

/*==============================================================================================#
|                                                                                               |
| Handmade Lite is an educational game engine, written by Karsten Vermeulen for the purposes of |
| educating other fellow programmers, programming students and anyone else wishing to learn     |
| about game development, C++ and OOP. The engine, class design and overall structure is by no  |
| means perfect and there is certainly room for improvement. Feel free to use, copy, break,     |
| update and do as you wish with this code - it is there, free, for all!                        |
|																							    |
| Designed to teach. Made from scratch. Built by hand.							                |
|																							    |
#===============================================================================================#
|	                                                                                            |
| Please note, that this project is not open source and therefore has no license affiliated     |
| with it. However, feel free to use the engine to build your own game or learn from the code.  |
| Handmade Lite is an educational tool, designed to be used as such. Please be respectful and   |
| do not distribute the engine or its code as your own work. You may alter or tweak the engine  |
| code as a learning experience and you may also 'borrow' some code and functionality and use   |
| it to create your own game engine or game.                                                    |
|	                                                                                            |
#===============================================================================================#
|                                                                                               |
| If you like Handmade Lite and wish to show your support, if you have any questions about      |
| the project, or if you just want to reach out, please do get in touch:                        |
|																						        |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'TextureManager' source files last updated in May 2020   							            |
#==============================================================================================*/

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Singleton.h"

class TextureManager
{

public:

	enum class DataType   { FONT_DATA, TEXTURE_DATA };
	enum class RemoveType { CUSTOM_DATA, ALL_DATA };

public:

	friend class Singleton<TextureManager>;

public:

	TTF_Font* GetFont(const std::string& mapIndex);
	SDL_Texture* GetTexture(const std::string& mapIndex);

public:

	bool Initialize();
	bool LoadFontFromFile(const std::string& filename, int fontSize, const std::string& mapIndex);
	bool LoadTextureFromFile(const std::string& filename, const std::string& mapIndex);
	void UnloadFromMemory(DataType dataType, RemoveType removeType, const std::string& mapIndex = "");
	void ShutDown();

public:

	void Output();

private:

	TextureManager()  {}
	TextureManager(const TextureManager&);
	TextureManager& operator=(const TextureManager&);

private:

	std::map<std::string, TTF_Font*> m_fontMap;
	std::map<std::string, SDL_Texture*> m_textureMap;
	
};

typedef Singleton<TextureManager> TheTexture;

#endif