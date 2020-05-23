#include "AudioManager.h"
#include "Background.h"
#include "ScreenManager.h"
#include "TextureManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that loads and links resources, and assigns all default values
//------------------------------------------------------------------------------------------------------
Background::Background(const std::string& imageFilename, const std::string& audioFilename)
{

	m_isPlaying = false;

	//load image and audio resources into memory
	TheTexture::Instance()->LoadTextureFromFile(imageFilename, imageFilename);
	TheAudio::Instance()->
	LoadFromFile(audioFilename, AudioManager::AudioType::MUSIC_AUDIO, audioFilename);

	//get resolution so that we can adjust the background image accordingly
	SDL_Point resolution = TheScreen::Instance()->GetResolution();

	//link image resource with sprite component
	m_image.SetTexture(imageFilename);
	m_image.SetSpriteDimension(resolution.x, resolution.y);
	m_image.SetTextureDimension(1, 1, resolution.x, resolution.y);

	//link audio resource with music component
	m_music.SetAudio(audioFilename, Audio::AudioType::MUSIC_AUDIO);

	//store names of resource tags so that we can remove them in the destructor 
	m_imageName = imageFilename;
	m_audioName = audioFilename;
	
}
//------------------------------------------------------------------------------------------------------
//function that renders the background image on screen
//------------------------------------------------------------------------------------------------------
bool Background::Draw()
{

	m_image.Draw();
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that plays the background music
//------------------------------------------------------------------------------------------------------
void Background::PlayMusic()
{

	if (!m_isPlaying)
	{
		m_music.Play(Audio::LoopType::PLAY_ENDLESS);
		m_isPlaying = true;
	}

}
//------------------------------------------------------------------------------------------------------
//function that stops the background music from playing
//------------------------------------------------------------------------------------------------------
void Background::StopMusic()
{

	m_music.Stop();
	m_isPlaying = false;

}
//------------------------------------------------------------------------------------------------------
//destructor that unloads all resources from memory
//------------------------------------------------------------------------------------------------------
Background::~Background()
{

	TheAudio::Instance()->
	UnloadFromMemory(AudioManager::AudioType::MUSIC_AUDIO, 
		             AudioManager::RemoveType::CUSTOM_AUDIO, m_audioName);
	
	TheTexture::Instance()->
	UnloadFromMemory(TextureManager::DataType::TEXTURE_DATA, 
		             TextureManager::RemoveType::CUSTOM_DATA, m_imageName);

}