#include <math.h>
#include "Sphere.h"

//======================================================================================================
Sphere::Sphere()
{
	m_radius = 0;
}
//======================================================================================================
void Sphere::SetRadius(int radius)
{
	m_radius = radius;
}
//======================================================================================================
void Sphere::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}
//======================================================================================================
bool Sphere::IsColliding(const Sphere& secondSphere) const
{
	Vector<int> centrePoint_1(m_position.x + m_radius, m_position.y + m_radius);
	Vector<int> centrePoint_2(secondSphere.m_position.x + secondSphere.m_radius,
							  secondSphere.m_position.y + secondSphere.m_radius);

	return (centrePoint_1.Distance(centrePoint_2) <= (m_radius + secondSphere.m_radius));
}