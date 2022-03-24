#pragma once
#include <array>
#include "AABB.h"
#include "Vector.h"

class OBB
{

public:

	OBB() {}

	void SetRotation(float angle);
	void SetScale(float x, float y);
	void SetPosition(float x, float y);
	void SetDimension(float width, float height);

	bool IsColliding(const OBB& secondBox) const;
	bool IsColliding(const AABB& secondBox) const;

	void Update();

private:

	bool IsColliding(const OBB* tempBox) const;

	float m_angle{ 0.0f };

	Vector<float> m_scale{ 1.0f, 1.0f };
	Vector<float> m_position{ 0.0f, 0.0f };
	Vector<float> m_dimension{ 1.0f, 1.0f };

	Vector<float> m_upAxis{ Vector<float>::Up };
	Vector<float> m_rightAxis{ Vector<float>::Right };
	std::array<Vector<float>, 4> m_corners{ Vector<float>::Zero };

};