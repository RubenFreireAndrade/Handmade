#include <algorithm>
#include <assert.h>
#include <SDL_image.h>
#include "Screen.h"
#include "Texture.h"
#include "Utility.h"

std::string Texture::s_rootFolder = "Assets/Textures/";
std::unique_ptr<Textures> Texture::s_textures = std::make_unique<Textures>();

//======================================================================================================
bool Texture::Load(const std::string& filename, const std::string& tag)
{
	assert(s_textures->find(tag) == s_textures->end());

	SDL_Surface* imageData = IMG_Load((s_rootFolder + filename).c_str());

	if (!imageData)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error loading image file \"" + (s_rootFolder + filename) + "\"\n\n"
			"Possible causes could be a corrupt or missing file. Another reason could be "
			"that the filename and/or path are incorrectly spelt.", Utility::Severity::Failure);
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Screen::Instance()->GetRenderer(), imageData);
	SDL_FreeSurface(imageData);

	s_textures->insert(std::pair<std::string, SDL_Texture*>(tag, texture));
	return true;
}
//======================================================================================================
void Texture::Unload(const std::string& tag)
{
	if (!tag.empty())
	{
		auto it = s_textures->find(tag);
		assert(it != s_textures->end());
		SDL_DestroyTexture(it->second);
		s_textures->erase(it);
	}

	else
	{
		for (const auto& texture : *s_textures)
		{
			SDL_DestroyTexture(texture.second);
		}

		s_textures->clear();
	}
}
//======================================================================================================
bool Texture::IsAnimationDead()
{
	return m_isAnimationDead;
}
//======================================================================================================
void Texture::IsAnimated(bool flag)
{
	m_isAnimated = flag;
}
//======================================================================================================
bool Texture::IsAnimationLooping()
{
	return m_isAnimationLooping;
}
//======================================================================================================
void Texture::IsAnimationLooping(bool flag)
{
	m_isAnimationLooping = flag;
}
//======================================================================================================
void Texture::SetCel(int column, int row)
{
	//Make sure this function is called AFTER setting the image dimension
	assert(column > 0 && column <= m_sourceDimension.x);
	assert(row > 0 && row <= m_sourceDimension.y);
	m_cel = ((row - 1) * m_sourceDimension.x) + (column - 1);
}
//======================================================================================================
void Texture::SetAnimationVelocity(float velocity)
{
	assert(velocity >= 0.0f);
	m_animationVelocity = velocity;
}
//======================================================================================================
bool Texture::SetTexture(const std::string& tag)
{
	auto it = s_textures->find(tag);
	assert(it != s_textures->end());
	m_texture = (*it).second;
	return true;
}
//======================================================================================================
void Texture::SetDimension(int width, int height)
{
	m_textureDimension.x = width;
	m_textureDimension.y = height;
}
//======================================================================================================
void Texture::SetSourceDimension(int columns, int rows, int width, int height)
{
	rows = std::max(rows, 1);
	columns = std::max(columns, 1);

	m_sourceDimension.x = columns;
	m_sourceDimension.y = rows;

	m_celDimension.x = width / columns;
	m_celDimension.y = height / rows;
}
//======================================================================================================
void Texture::ResetAnimation()
{
	m_cel = 0;
	m_isAnimationDead = false;
	m_animationRunningTime = 0.0f;
	m_isAnimationLoopFinal = false;
}
//======================================================================================================
void Texture::Update(int deltaTime)
{
	//If sprite is an animation we have to calculate the 
	//image cel each frame because it won't be a static value
	if (m_isAnimated)
	{
		m_animationRunningTime += deltaTime / 1000.0f;

		//Aquire index value of specific texture cel to 'cut out' using a formula
		//The image index is zero-based and is a whole number value counting from
		//top left and going right and down the sprite sheet, and is capable of 'wrapping'
		m_cel = static_cast<int>(m_animationRunningTime * m_animationVelocity) %
			static_cast<int>(m_sourceDimension.x * m_sourceDimension.y);

		if (m_isAnimationLooping)
		{
			m_isAnimationDead = false;
			m_isAnimationLoopFinal = false;
		}

		//If animation is set to cycle once and the last image cel 
		//has been reached then flag this as the final animation loop
		else if (!m_isAnimationLooping &&
			m_cel == (m_sourceDimension.x * m_sourceDimension.y - 1))
		{
			m_isAnimationLoopFinal = true;
		}

		//If this is the final animation, flag to kill entire animation
		//because even though the animation is marked final, a few more 
		//frames will be called with the last image cel set, so only
		//mark it dead when the first image cel comes around again
		if (m_isAnimationLoopFinal && m_cel == 0)
		{
			m_isAnimationDead = true;
		}
	}
}
//======================================================================================================
void Texture::Render(int x, int y, double angle, Flip flip)
{
	if (!m_isAnimationDead)
	{
		//Variables to store rectangular dimensions for the source 
		//sprite and destination portion of the screen to render to 
		SDL_Rect src;
		SDL_Rect dst;

		//We need to get exact cel block xy coordinates to 'cut out' 
		src.x = (m_cel % m_sourceDimension.x) * m_celDimension.x;
		src.y = (m_cel / m_sourceDimension.x) * m_celDimension.y;
		src.w = m_celDimension.x;
		src.h = m_celDimension.y;

		dst.x = x;
		dst.y = y;
		dst.w = m_textureDimension.x;
		dst.h = m_textureDimension.y;

		//Use the centre of the sprite as its centre of rotation
		SDL_Point centrePoint;
		centrePoint.x = m_textureDimension.x / 2;
		centrePoint.y = m_textureDimension.y / 2;

		SDL_RenderCopyEx(Screen::Instance()->GetRenderer(),
			m_texture, &src, &dst, angle, &centrePoint, static_cast<SDL_RendererFlip>(flip));
	}
}