#include "Input.h"
#include "Player.h"

//======================================================================================================
Player::Player()
{
	m_idle.Load("Adventure_boy_idle.png", "Idle");
	m_idle.SetTexture("Idle");
	m_idle.SetDimension(200, 200);
	m_idle.SetSourceDimension(10, 1, 5880, 600);
	m_idle.IsAnimated(true);
	m_idle.IsAnimationLooping(true);
	m_idle.SetAnimationVelocity(20.0f);

	m_walk.Load("Adventure_boy_run.png", "Walk");
	m_walk.SetTexture("Walk");
	m_walk.SetDimension(200, 200);
	m_walk.SetSourceDimension(10, 1, 5880, 600);
	m_walk.IsAnimated(true);
	m_walk.IsAnimationLooping(true);
	m_walk.SetAnimationVelocity(20.0f);

	m_footsteps.Load("Melee.wav", "Foot");
	m_footsteps.SetSound("Foot");

	SetPosition(600, 500);
	m_bound.SetDimension(125, 250);
}
//======================================================================================================
const AABB& Player::GetBound()
{
	return m_bound;
}
//======================================================================================================
void Player::Update(int deltaTime)
{
	auto keys = Input::Instance()->GetKey();

	//Check if left or right key is pressed and set player's direction accordingly
	//assign standing direction as well so that when no key is pressed the correct
	//direction is set for the standing stance and sprite of the player object
	if (Input::Instance()->IsKeyPressed(HM_KEY_LEFT))
	{
		m_directionStand = m_directionWalk = Vector<int>::Left;
	}

	else if (Input::Instance()->IsKeyPressed(HM_KEY_RIGHT))
	{
		m_directionStand = m_directionWalk = Vector<int>::Right;
	}

	else
	{
		m_directionWalk = Vector<int>::Zero;
	}

	m_position += m_directionWalk * m_velocity;
	m_bound.SetPosition(m_position.x, m_position.y);

	m_idle.Update(deltaTime);
	m_walk.Update(deltaTime);
}
//======================================================================================================
bool Player::Render()
{
	//Flag to be used for playing "footstep" sound effect
	//We don't want it to play multiple times at once!
	static bool isWalking = false;

	//Check if player is walking or not and render the correct walking cycle
	//render the correct standing stance sprite based on which way he is facing
	if (m_directionWalk.x == 0 && m_directionWalk.y == 0)
	{
		m_directionStand.x < 0.0f ? m_idle.Render(m_position.x, m_position.y, 0.0, Texture::Flip::Horizontal)
			: m_idle.Render(m_position.x, m_position.y);
		isWalking = false;
	}

	else
	{
		m_directionWalk.x < 0.0f ? m_walk.Render(m_position.x, m_position.y, 0.0, Texture::Flip::Horizontal)
			: m_walk.Render(m_position.x, m_position.y);

		if (!isWalking)
		{
			m_footsteps.Play();
			isWalking = true;
		}
	}

	return true;
}
//======================================================================================================
Player::~Player()
{
	m_footsteps.Unload("Foot");
	m_walk.Unload("Walk");
	m_idle.Unload("Idle");
}