#pragma once
#include <map>
#include <memory>
#include <string>
#include <SDL_render.h>

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

	Sprite() {}

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

	int m_imageCel{ 0 };
	float m_animationVelocity{ 0.0f };
	float m_animationRunningTime{ 0.0f };

	bool m_isAnimated{ false };
	bool m_isAnimationDead{ false };
	bool m_isAnimationLooping{ true };
	bool m_isAnimationLoopFinal{ false };

	SDL_Texture* m_image{ nullptr };
	SDL_Point m_celDimension = { 0, 0 };
	SDL_Point m_imageDimension = { 1, 1 };
	SDL_Point m_spriteDimension = { 0, 0 };

	static std::string s_rootFolder;
	static std::unique_ptr<Textures> s_textures;

};