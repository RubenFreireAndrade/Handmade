#pragma once

/*===================================================================#
| 'Sphere' source files last updated on 11 May 2021                  |
#===================================================================*/

#include "Vector.h"

class Sphere
{

public:

	Sphere();

	void SetRadius(int radius);
	void SetPosition(int x, int y);

	bool IsColliding(const Sphere& secondSphere) const;

private:

	int m_radius;
	Vector<int> m_position;

};