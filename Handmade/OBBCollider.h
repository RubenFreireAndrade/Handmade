#pragma once
#include <array>
#include "BoxCollider.h"
#include "Vector.h"

class OBBCollider
{

public:

	OBBCollider() {}

	void SetRotation(float angle);
	void SetScale(float x, float y);
	void SetPosition(float x, float y);
	void SetDimension(float width, float height);

	bool IsColliding(const OBBCollider& secondBox) const;
	bool IsColliding(const BoxCollider& secondBox) const;

	void Update();

private:

	bool IsColliding(const OBBCollider* tempBox) const;

	float m_angle{ 0.0f };

	Vector<float> m_scale{ 1.0f, 1.0f };
	Vector<float> m_position{ 0.0f, 0.0f };
	Vector<float> m_dimension{ 1.0f, 1.0f };

	Vector<float> m_upAxis{ Vector<float>::Up };
	Vector<float> m_rightAxis{ Vector<float>::Right };
	std::array<Vector<float>, 4> m_corners{ Vector<float>::Zero };

};