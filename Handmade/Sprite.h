#pragma once

/*===================================================================#
| 'Sprite' source files last updated on 11 May 2021                  |
#===================================================================*/

#include <map>
#include <string>
#include <SDL_render.h>

//TODO - Reset animation cel back to 0
//TODO - Add an 'assert' to make sure when setting image cel dimensions are set
//TODO - Dimension of sprite must relate to dimension of game object base class
//TODO - Fix bug when setting animation velocity to a negative number

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

	void Update(int deltaTime);

	void Draw(int positionX = 0,
		int positionY = 0,
		double angle = 0.0,
		FlipType flipType = FlipType::NO_FLIP);

private:

	int m_imageCel;
	float m_animationVelocity;

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