#pragma once

/*===================================================================#
| 'Sprite' source files last updated on 22 September 2021            |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include <map>
#include <memory>
#include <string>
#include <SDL_render.h>

//TODO - Add proper error messages
//TODO - Make sure asserts are disabled in Release mode

typedef std::map<std::string, SDL_Texture*> Textures;

class Sprite
{

public:

	enum class Flip
	{
		None = SDL_FLIP_NONE,
		Vertical = SDL_FLIP_VERTICAL,
		Horizontal = SDL_FLIP_HORIZONTAL
	};

	static bool Load(const std::string& filename, const std::string& tag);
	static void Unload(const std::string& tag = "");

	Sprite();

	bool IsAnimationDead();
	void IsAnimated(bool flag);
	bool IsAnimationLooping();
	void IsAnimationLooping(bool flag);

	bool SetImage(const std::string& tag);
	void SetImageCel(int column, int row);
	void SetAnimationVelocity(float velocity);
	void SetSpriteDimension(int width, int height);
	void SetImageDimension(int columns, int rows, int width, int height);

	void ResetAnimation();
	void Update(int deltaTime);

	void Render(int x = 0, 
		int y = 0,
		double angle = 0.0, 
		Flip flip = Flip::None);

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

	static std::unique_ptr<Textures> s_textures;

};