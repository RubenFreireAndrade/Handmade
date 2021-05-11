#pragma once

/*===================================================================#
| 'Music' source files last updated on 11 May 2021                   |
#===================================================================*/

#include <map>
#include <string>
#include <SDL_mixer.h>

//TODO - Adjust volume level when starting the game
//TODO - Normalize audio volume

class Music
{

public:

	enum class LoopType
	{
		PLAY_ONCE = 1,
		PLAY_ENDLESS = -1
	};

	static bool Initialize(int frequency = 44100, int chunkSize = 1024);
	static bool Load(const std::string& filename, const std::string& mapIndex);
	static void Unload(const std::string& mapIndex = "");
	static void Shutdown();

	Music();

	void SetVolume(int volume);
	bool SetMusic(const std::string& mapIndex);

	bool Play(LoopType loopType = LoopType::PLAY_ONCE);
	void Pause();
	void Resume();
	void Stop();

private:

	Mix_Music* m_music;
	static std::map<std::string, Mix_Music*>* s_music;

};