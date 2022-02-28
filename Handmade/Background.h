#pragma once
#include "GameObject.h"
#include "Music.h"
#include "Sprite.h"

class Background : public GameObject
{

public:

	Background();
	virtual ~Background();

	void Load(const std::string& imageFilename,
		const std::string& audioFilename);
	void PlayMusic();
	void StopMusic();

	virtual void Update(int deltaTime) {}
	virtual bool Render();

protected:

	bool m_isPlaying;
	std::string m_imageID;
	std::string m_audioID;

	Music m_music;
	Sprite m_image;

};