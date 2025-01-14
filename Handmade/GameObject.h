#pragma once
#include <string>
#include <SDL.h>

class GameObject
{

public:

	GameObject() {}
	virtual ~GameObject() = 0 {}

	bool IsAlive() const;
	bool IsActive() const;
	bool IsVisible() const;

	void IsAlive(bool flag);
	void IsActive(bool flag);
	void IsVisible(bool flag);

	float GetAngle() const;
	int GetPriority() const;

	const std::string& GetTag() const;
	const SDL_Point& GetPosition() const;
	const SDL_Point& GetDimension() const;

	void SetPosition(int x, int y);
	void SetDimension(int x, int y);
	void SetTag(const std::string& tag);

	virtual void Update(int deltaTime) = 0;
	virtual bool Render() = 0;

protected:

	int m_priority{ 0 };
	float m_angle{ 0.0f };

	bool m_isDirty{ true };
	bool m_isAlive{ true };
	bool m_isActive{ true };
	bool m_isVisible{ true };

	std::string m_tag;
	SDL_Point m_position;
	SDL_Point m_dimension;

};