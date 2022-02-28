#pragma once
#include "Vector.h"

class Sphere
{

public:

	Sphere() {}

	void SetRadius(int radius);
	void SetPosition(int x, int y);

	bool IsColliding(const Sphere& secondSphere) const;

private:

	int m_radius{ 0 };
	Vector<int> m_position;

};