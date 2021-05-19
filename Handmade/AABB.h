#pragma once

/*===================================================================#
| 'AABB' source files last updated on 19 May 2021                    |
#===================================================================*/

#include "Vector.h"

class AABB
{

public:

	void SetPosition(int x, int y);
	void SetDimension(int width, int height);

	void Update();
	bool IsColliding(const AABB& secondBox) const;

private:

	Vector<int> m_min;
	Vector<int> m_max;
	Vector<int> m_position;
	Vector<int> m_dimension;

};