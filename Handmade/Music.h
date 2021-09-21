#pragma once

/*===================================================================#
| 'Music' source files last updated on 21 September 2021             |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include <map>
#include <memory>
#include <string>
#include <SDL_mixer.h>

//TODO - Add proper error messages
//TODO - Make sure asserts are disabled in Release mode

typedef std::map<std::string, Mix_Music*> Musics;

class Music
{

public:

	enum class Loop
	{
		Once = 1,
		Ongoing = -1
	};

	static bool Initialize(int frequency = 44100, int chunkSize = 1024);
	static bool Load(const std::string& filename, const std::string& tag);
	static void Unload(const std::string& tag = "");
	static void Shutdown();

	Music();

	void SetVolume(float volume);
	bool SetMusic(const std::string& tag);

	bool Play(Loop loop = Loop::Once);
	void Pause();
	void Resume();
	void Stop();

private:

	Mix_Music* m_music;
	static std::unique_ptr<Musics> s_musics;

};