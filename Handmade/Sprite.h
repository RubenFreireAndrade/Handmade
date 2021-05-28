#pragma once

/*===================================================================#
| 'Sprite' source files last updated on 28 May 2021                  |
#===================================================================*/

#include <map>
#include <string>
#include <SDL_render.h>

//TODO - Add proper error messages
//TODO - Make sure asserts are disabled in Release mode

class Sprite
{

public:

	enum class FlipType
	{
		NO_FLIP = SDL_FLIP_NONE,
		HORIZONTAL = SDL_FLIP_HORIZONTAL,
		VERTICAL = SDL_FLIP_VERTICAL
	};

	static bool Load(const std::string& filename, const std::string& mapIndex);
	static void Unload(const std::string& mapIndex = "");

	Sprite();

	bool IsAnimationDead();
	void IsAnimated(bool flag);
	bool IsAnimationLooping();
	void IsAnimationLooping(bool flag);

	void SetImageCel(int column, int row);
	void SetAnimationVelocity(float velocity);
	bool SetImage(const std::string& mapIndex);
	void SetSpriteDimension(int width, int height);
	void SetImageDimension(int columns, int rows, int width, int height);

	void ResetAnimation();
	void Update(int deltaTime);

	void Render(int positionX = 0,
		int positionY = 0,
		double angle = 0.0,
		FlipType flipType = FlipType::NO_FLIP);

private:

	int m_imageCel;
	float m_animationVelocity;
	float m_animationRunningTime;

	bool m_isAnimated;
	bool m_isAnimationDead;
	bool m_isAnimationLooping;
	bool m_isAnimationLoopFinal;

	SDL_Texture* m_image;
	SDL_Point m_celDimension;
	SDL_Point m_imageDimension;
	SDL_Point m_spriteDimension;

	static std::map<std::string, SDL_Texture*>* s_images;

};