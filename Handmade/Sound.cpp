#include <algorithm>
#include <assert.h>
#include "Sound.h"
#include "Utility.h"

std::map<std::string, Mix_Chunk*>* Sound::s_sounds = new std::map<std::string, Mix_Chunk*>;

//======================================================================================================
bool Sound::Load(const std::string& filename, const std::string& mapIndex)
{
	//Sound data already loaded in memory
	assert(s_sounds->find(mapIndex) == s_sounds->end());

	Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());

	if (!sound)
	{
		Utility::Log(MESSAGE_BOX,
			"File could not be loaded.", Utility::Severity::FAILURE);
		return false;
	}

	(*s_sounds)[mapIndex] = sound;

	return true;
}
//======================================================================================================
void Sound::Unload(const std::string& mapIndex)
{
	if (!mapIndex.empty())
	{
		auto it = s_sounds->find(mapIndex);

		//Sound data not found, so make sure to enter a valid ID
		assert(it != s_sounds->end());

		Mix_FreeChunk(it->second);
		s_sounds->erase(it);
	}

	else
	{
		for (auto it = s_sounds->begin(); it != s_sounds->end(); it++)
		{
			Mix_FreeChunk(it->second);
		}

		s_sounds->clear();
	}
}
//======================================================================================================
Sound::Sound()
{
	m_sound = nullptr;
}
//======================================================================================================
void Sound::SetVolume(float volume)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	Mix_VolumeChunk(m_sound, static_cast<int>(volume * 128.0f));
}
//======================================================================================================
bool Sound::SetSound(const std::string& mapIndex)
{
	auto it = s_sounds->find(mapIndex);

	//Sound data not found, so make sure to enter a valid ID
	assert(it != s_sounds->end());

	m_sound = (*it).second;
	return true;
}
//======================================================================================================
bool Sound::Play(int loop)
{
	if (Mix_PlayChannel(-1, m_sound, loop) == -1)
	{
		Utility::Log(MESSAGE_BOX,
			"Music could not be played.", Utility::Severity::FAILURE);
		return false;
	}

	return true;
}