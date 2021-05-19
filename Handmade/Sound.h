#pragma once

/*===================================================================#
| 'Sound' source files last updated on 19 May 2021                   |
#===================================================================*/

#include <map>
#include <string>
#include <SDL_mixer.h>

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