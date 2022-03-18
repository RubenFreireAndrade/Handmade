#pragma once

#include "AABB.h"
#include "GameObject.h"
#include "Sound.h"
#include "Texture.h"
#include "Vector.h"

class Player : public GameObject
{

public:

	Player();
	~Player() override;

	const AABB& GetBound();

	void Update(int deltaTime) override;
	bool Render() override;

private:

	int m_velocity = 5;

	AABB m_bound;
	Sound m_footsteps;

	Texture m_idle;
	Texture m_walk;

	Vector<int> m_directionWalk;
	Vector<int> m_directionStand;

};