#pragma once
#include "Vector.h"

class AABB
{

public:

	AABB GetCollisionRegion(const AABB& secondBox);

	void SetPosition(int x, int y);
	void SetDimension(int width, int height);

	void Update();
	bool IsColliding(const AABB& secondBox) const;

	bool IsColliding(
		const AABB& secondBox,
		const Vector<int>& lhsBoxVelocity, // velocity of rectangle 1
		const Vector<int>& rhsBoxVelocity, // velocity of rectangle 2
		float maxTime, // max time - i.e. your DT for this frame
		float* firstTime = 0); // Set to time of first contact 

private:

	Vector<int> m_min;
	Vector<int> m_max;
	Vector<int> m_position;
	Vector<int> m_dimension;

};