#include <algorithm>
#include <assert.h>
#include "Music.h"
#include "Utility.h"

std::unique_ptr<MusicMap> Music::s_music = std::make_unique<MusicMap>();

//======================================================================================================
bool Music::Initialize(int frequency, int chunkSize)
{
	if (Mix_OpenAudio(frequency, AUDIO_S16SYS, 2, chunkSize) == -1)
	{
		Utility::Log(MESSAGE_BOX,
			"Audio sub-system did not initialize properly.", Utility::Severity::FAILURE);
		return false;
	}

	return true;
}
//======================================================================================================
bool Music::Load(const std::string& filename, const std::string& mapIndex)
{
	//Music data already loaded in memory
	assert(s_music->find(mapIndex) == s_music->end());

	Mix_Music* music = Mix_LoadMUS(filename.c_str());

	if (!music)
	{
		Utility::Log(MESSAGE_BOX,
			"File could not be loaded.", Utility::Severity::FAILURE);
		return false;
	}

	s_music->insert(std::pair<std::string, Mix_Music*>(mapIndex, music));
	return true;
}
//======================================================================================================
void Music::Unload(const std::string& mapIndex)
{
	if (!mapIndex.empty())
	{
		auto it = s_music->find(mapIndex);

		//Music data not found, so make sure to enter a valid ID
		assert(it != s_music->end());

		Mix_FreeMusic(it->second);
		s_music->erase(it);
	}

	else
	{
		for (const auto& music : (*s_music))
		{
			Mix_FreeMusic(music.second);
		}

		s_music->clear();
	}
}
//======================================================================================================
void Music::Shutdown()
{
	Mix_CloseAudio();
}
//======================================================================================================
Music::Music()
{
	m_music = nullptr;
}
//======================================================================================================
void Music::SetVolume(float volume)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	Mix_VolumeMusic(static_cast<int>(volume * 128.0f));
}
//======================================================================================================
bool Music::SetMusic(const std::string& mapIndex)
{
	auto it = s_music->find(mapIndex);

	//Music data not found, so make sure to enter a valid ID
	assert(it != s_music->end());

	m_music = (*it).second;
	return true;
}
//======================================================================================================
bool Music::Play(LoopType loopType)
{
	if (!Mix_PlayingMusic())
	{
		if (Mix_PlayMusic(m_music, static_cast<int>(loopType)) == -1)
		{
			Utility::Log(MESSAGE_BOX,
				"Music could not be played.", Utility::Severity::FAILURE);
			return false;
		}
	}

	return true;
}
//======================================================================================================
void Music::Pause()
{
	if (!Mix_PausedMusic())
	{
		Mix_PauseMusic();
	}
}
//======================================================================================================
void Music::Resume()
{
	if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
}
//======================================================================================================
void Music::Stop()
{
	if (Mix_PlayingMusic())
	{
		Mix_HaltMusic();
	}
}