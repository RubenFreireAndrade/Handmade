#pragma once

/*===================================================================#
| 'Sound' source files last updated on 28 May 2021                   |
#===================================================================*/

#include <map>
#include <string>
#include <SDL_mixer.h>

//TODO - Add proper error messages
//TODO - Make sure asserts are disabled in Release mode

class Sound
{

public:

	static bool Load(const std::string& filename, const std::string& mapIndex);
	static void Unload(const std::string& mapIndex = "");

	Sound();

	void SetVolume(float volume);
	bool SetSound(const std::string& mapIndex);

	bool Play(int loop = 0);

private:

	Mix_Chunk* m_sound;
	static std::map<std::string, Mix_Chunk*>* s_sounds;

};