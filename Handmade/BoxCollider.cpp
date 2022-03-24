#include <algorithm>
#include "BoxCollider.h"

//======================================================================================================
BoxCollider BoxCollider::GetCollisionRegion(const BoxCollider& secondBox)
{
	BoxCollider collider;

	collider.m_min.x = std::max(m_min.x, secondBox.m_min.x);
	collider.m_min.y = std::max(m_min.y, secondBox.m_min.y);
	collider.m_max.x = std::min(m_max.x, secondBox.m_max.x);
	collider.m_max.y = std::max(m_max.y, secondBox.m_max.y);

	return collider;
}
//======================================================================================================
void BoxCollider::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}
//======================================================================================================
void BoxCollider::SetDimension(int width, int height)
{
	m_dimension.x = width;
	m_dimension.y = height;
}
//======================================================================================================
void BoxCollider::Update()
{
	m_min.x = m_position.x;
	m_min.y = m_position.y;
	m_max.x = m_position.x + m_dimension.x;
	m_max.y = m_position.y + m_dimension.y;
}
//======================================================================================================
bool BoxCollider::IsColliding(const BoxCollider& secondBox) const
{
	return ((m_max.x > secondBox.m_min.x && secondBox.m_max.x > m_min.x) &&
		(m_max.y > secondBox.m_min.y && secondBox.m_max.y > m_min.y));
}
//======================================================================================================
bool BoxCollider::IsColliding(const BoxCollider& secondBox,
	const Vector<int>& lhsBoxVelocity,
	const Vector<int>& rhsBoxVelocity,
	float maxTime, float* firstTime)
{
	//Velocity of box 1 relative to box 2
	Vector<int> relativeVelocity = lhsBoxVelocity - rhsBoxVelocity;

	//Time of first contact in X
	auto x0 = 0.0f;

	if (secondBox.m_min.x > m_max.x && relativeVelocity.x > 0)
	{
		x0 = (secondBox.m_min.x - m_max.x) / static_cast<float>(relativeVelocity.x);
	}

	else if (m_min.x > secondBox.m_max.x && relativeVelocity.x < 0)
	{
		//Swap to get +ve time
		x0 = (secondBox.m_max.x - m_min.x) / static_cast<float>(relativeVelocity.x);
	}

	//Time of final contact in X
	auto x1 = maxTime;

	if (secondBox.m_max.x > m_min.x && relativeVelocity.x > 0)
	{
		x1 = (secondBox.m_max.x - m_min.x) / static_cast<float>(relativeVelocity.x);
	}

	else if (m_max.x > secondBox.m_min.x && relativeVelocity.x < 0)
	{
		//Swap to get +ve time
		x1 = (secondBox.m_min.x - m_max.x) / static_cast<float>(relativeVelocity.x);
	}

	//Time of first contact in Y
	auto y0 = 0.0f;

	if (secondBox.m_min.y > m_max.y && relativeVelocity.y > 0)
	{
		y0 = (secondBox.m_min.y - m_max.y) / static_cast<float>(relativeVelocity.y);
	}

	else if (m_min.y > secondBox.m_max.y && relativeVelocity.y < 0)
	{
		//Swap to get +ve time
		y0 = (secondBox.m_max.y - m_min.y) / static_cast<float>(relativeVelocity.y);
	}

	//Time of final contact in Y
	auto y1 = maxTime;

	if (secondBox.m_max.y > m_min.y && relativeVelocity.y > 0)
	{
		y1 = (secondBox.m_max.y - m_min.y) / static_cast<float>(relativeVelocity.y);
	}

	else if (m_max.y > secondBox.m_min.y && relativeVelocity.y < 0)
	{
		//Swap to get +ve time
		y1 = (secondBox.m_min.y - m_max.y) / static_cast<float>(relativeVelocity.y);
	}

	//Time of first contact for the 2 rects is the MAX
	//of the times of first contact in X and Y
	auto first = std::max(x0, y0);

	//Time of last contact for the 2 rects is the MIN
	//of the times of last contact in X and Y
	auto last = std::min(x1, y1);

	//If the time of final contact is AFTER the time of
	//first contact, then the rects do intersect
	auto intersect = (last > first && first < maxTime);

	//Pass back time of first contact
	if (firstTime)
	{
		*firstTime = first;
	}

	return intersect;
}