#pragma once

/*===================================================================#
| 'Sound' source files last updated on 22 September 2021             |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include <map>
#include <memory>
#include <string>
#include <SDL_mixer.h>

//TODO - Add proper error messages
//TODO - Make sure asserts are disabled in Release mode

typedef std::map<std::string, Mix_Chunk*> Sounds;

class Sound
{

public:

	static bool Load(const std::string& filename, const std::string& tag);
	static void Unload(const std::string& tag = "");

	Sound();

	void SetVolume(float volume);
	bool SetSound(const std::string& tag);

	bool Play(int loop = 0);

private:

	Mix_Chunk* m_sound;

	static std::string s_rootFolder;
	static std::unique_ptr<Sounds> s_sounds;

};