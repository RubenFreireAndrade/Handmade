#pragma once

/*===================================================================#
| 'Sphere' source files last updated on 19 May 2021                  |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
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