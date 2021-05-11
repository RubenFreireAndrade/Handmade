#pragma once

/*===================================================================#
| 'Background' source files last updated on 11 May 2021              |
#===================================================================*/

#include "GameObject.h"
#include "Music.h"
#include "Sprite.h"

class Background : public GameObject
{

public:

	Background(const std::string& imageFilename, const std::string& audioFilename);
	virtual ~Background();

	virtual void Update(int deltaTime) {}
	virtual bool Draw();

	void PlayMusic();
	void StopMusic();

protected:

	bool m_isPlaying;
	std::string m_imageID;
	std::string m_audioID;

	Music m_music;
	Sprite m_image;

};