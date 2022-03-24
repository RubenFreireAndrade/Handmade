#include "SphereCollider.h"

//======================================================================================================
int SphereCollider::GetRadius() const
{
	return m_radius;
}
//======================================================================================================
const Vector<int>& SphereCollider::GetPosition() const
{
	return m_position;
}
//======================================================================================================
void SphereCollider::SetRadius(int radius)
{
	m_radius = radius;
}
//======================================================================================================
void SphereCollider::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}
//======================================================================================================
bool SphereCollider::IsColliding(const SphereCollider& secondSphere) const
{
	Vector<int> centerPoint_1(m_position.x + m_radius, m_position.y + m_radius);
	Vector<int> centerPoint_2(secondSphere.m_position.x + secondSphere.m_radius,
		secondSphere.m_position.y + secondSphere.m_radius);

	return (centerPoint_1.Distance(centerPoint_2) <= (m_radius + secondSphere.m_radius));
}