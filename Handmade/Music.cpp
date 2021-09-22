#include <algorithm>
#include <assert.h>
#include "Music.h"
#include "Utility.h"

std::unique_ptr<Musics> Music::s_musics = std::make_unique<Musics>();

//======================================================================================================
bool Music::Initialize(int frequency, int chunkSize)
{
	if (Mix_OpenAudio(frequency, AUDIO_S16SYS, 2, chunkSize) == -1)
	{
		Utility::Log(MESSAGE_BOX,
			"Audio sub-system did not initialize properly.", Utility::Severity::Failure);
		return false;
	}

	return true;
}
//======================================================================================================
bool Music::Load(const std::string& filename, const std::string& tag)
{
	assert(s_musics->find(tag) == s_musics->end());

	Mix_Music* music = Mix_LoadMUS(filename.c_str());

	if (!music)
	{
		Utility::Log(MESSAGE_BOX,
			"File could not be loaded.", Utility::Severity::Failure);
		return false;
	}

	s_musics->insert(std::pair<std::string, Mix_Music*>(tag, music));
	return true;
}
//======================================================================================================
void Music::Unload(const std::string& tag)
{
	if (!tag.empty())
	{
		auto it = s_musics->find(tag);
		assert(it != s_musics->end());
		Mix_FreeMusic(it->second);
		s_musics->erase(it);
	}

	else
	{
		for (const auto& music : *s_musics)
		{
			Mix_FreeMusic(music.second);
		}

		s_musics->clear();
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
bool Music::SetMusic(const std::string& tag)
{
	auto it = s_musics->find(tag);
	assert(it != s_musics->end());
	m_music = (*it).second;
	return true;
}
//======================================================================================================
bool Music::Play(Loop loop)
{
	if (!Mix_PlayingMusic())
	{
		if (Mix_PlayMusic(m_music, static_cast<int>(loop)) == -1)
		{
			Utility::Log(MESSAGE_BOX,
				"Music could not be played.", Utility::Severity::Failure);
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