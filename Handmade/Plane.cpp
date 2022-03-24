#include "Plane.h"

//======================================================================================================
void Plane::SetPoint1(int x, int y)
{
	m_planePoints.point1.x = x;
	m_planePoints.point1.y = y;
}
//======================================================================================================
void Plane::SetPoint2(int x, int y)
{
	m_planePoints.point2.x = x;
	m_planePoints.point2.y = y;
}
//======================================================================================================
void Plane::Update()
{
	auto plane = m_planePoints.point2 - m_planePoints.point1;

	m_normal.x = -plane.y;
	m_normal.y = plane.x;

	if (m_normal.x == -0)
	{
		m_normal.x = 0;
	}

	m_normal = m_normal.Normalize();
	m_distanceFromOrigin = (int)(m_normal.Dot(m_planePoints.point1));
}
//======================================================================================================
Plane::PlaneSide Plane::SideOfPlane(int x, int y) const
{
	auto distanceFromPlane = DistanceFromPlane(x, y);

	if (distanceFromPlane < 0)
	{
		return PlaneSide::Negative;
	}

	if (distanceFromPlane > 0)
	{
		return PlaneSide::Positive;
	}

	return PlaneSide::OnPlane;
}
//======================================================================================================
int Plane::DistanceFromPlane(int x, int y) const
{
	return (m_normal.Dot(Vector<int>(x, y))) - m_distanceFromOrigin;
}
//======================================================================================================
bool Plane::IsColliding(const SphereCollider& secondSphere) const
{
	auto position = secondSphere.GetPosition();
	return (abs(DistanceFromPlane(position.x, position.y)) <= secondSphere.GetRadius());
}