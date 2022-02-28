#include <algorithm>
#include <assert.h>
#include "Sound.h"
#include "Utility.h"

std::string Sound::s_rootFolder = "Assets/Sounds/";
std::unique_ptr<Sounds> Sound::s_sounds = std::make_unique<Sounds>();

//======================================================================================================
bool Sound::Load(const std::string& filename, const std::string& tag)
{
	assert(s_sounds->find(tag) == s_sounds->end());

	Mix_Chunk* sound = Mix_LoadWAV((s_rootFolder + filename).c_str());

	if (!sound)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error loading sound file \"" + (s_rootFolder + filename) + "\"\n\n"
			"Possible causes could be a corrupt or missing file. Another reason could be "
			"that the filename and/or path are incorrectly spelt.", Utility::Severity::Failure);
		return false;
	}

	s_sounds->insert(std::pair<std::string, Mix_Chunk*>(tag, sound));
	return true;
}
//======================================================================================================
void Sound::Unload(const std::string& tag)
{
	if (!tag.empty())
	{
		auto it = s_sounds->find(tag);
		assert(it != s_sounds->end());
		Mix_FreeChunk(it->second);
		s_sounds->erase(it);
	}

	else
	{
		for (const auto& sound : *s_sounds)
		{
			Mix_FreeChunk(sound.second);
		}

		s_sounds->clear();
	}
}
//======================================================================================================
void Sound::SetVolume(float volume)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	Mix_VolumeChunk(m_sound, static_cast<int>(volume * 128.0f));
}
//======================================================================================================
bool Sound::SetSound(const std::string& tag)
{
	auto it = s_sounds->find(tag);
	assert(it != s_sounds->end());
	m_sound = (*it).second;
	return true;
}
//======================================================================================================
bool Sound::Play(int loop)
{
	if (Mix_PlayChannel(-1, m_sound, loop) == -1)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Sound could not be played.", Utility::Severity::Failure);
		return false;
	}

	return true;
}