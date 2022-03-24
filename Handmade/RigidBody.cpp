#include "RigidBody.h"

//======================================================================================================
Vector<double> RigidBody::GravityForce(double mass_1, double mass_2, const Vector<double>& distance)
{
	double gravityForce = (GRAVITY * mass_1 * mass_2) /
		distance.Magnitude() * distance.Magnitude();
	return distance.Normalize() * gravityForce;
}
//======================================================================================================
//Vector<double> RigidBody::TorqueForce(const Vector<double>& force,
//	const Vector<double>& contactPosition, const Vector<double>& centreOfMass)
//{
//	//The result produces a vector, used for the rotation axis and torque magnitude
//	return glm::cross(force, (centreOfMass - contactPosition));
//}
//======================================================================================================
RigidBody::RigidBody() {}
//======================================================================================================
double RigidBody::GetAngle() const
{
	return m_angle;
}
//======================================================================================================
double RigidBody::GetAngularVelocity() const
{
	return m_angularVelocity;
}
//======================================================================================================
const Vector<double>& RigidBody::GetForce() const
{
	return m_force;
}
//======================================================================================================
//const Vector<double>& RigidBody::GetTorque() const
//{
//	return m_torque;
//}
//======================================================================================================
const Vector<double>& RigidBody::GetPosition() const
{
	return m_position;
}
//======================================================================================================
const Vector<double>& RigidBody::GetVelocity() const
{
	return m_velocity;
}
//======================================================================================================
void RigidBody::SetMass(double mass)
{
	m_mass = mass;
}
//======================================================================================================
void RigidBody::SetAngle(double angle)
{
	m_angle = angle;
}
//======================================================================================================
void RigidBody::SetAngularMass(double mass)
{
	m_angularMass = mass;
}
//======================================================================================================
void RigidBody::SetAngularVelocity(double velocity)
{
	m_angularVelocity = velocity;
}
//======================================================================================================
void RigidBody::SetForce(const Vector<double>& force)
{
	m_force = force;
}
//======================================================================================================
void RigidBody::SetTorque(const Vector<double>& torque)
{
	//m_torque = torque;
}
//======================================================================================================
void RigidBody::SetPosition(const Vector<double>& position)
{
	m_position = position;
}
//======================================================================================================
void RigidBody::SetVelocity(const Vector<double>& velocity)
{
	m_velocity = velocity;
}
//======================================================================================================
void RigidBody::AddForce(const Vector<double>& force)
{
	m_force += force;
}
//======================================================================================================
void RigidBody::AddTorque(const Vector<double>& force, const Vector<double>& contactPoint)
{
	AddForce(force);

	//T = F x d
	//TODO - Fix this
	Vector<double> distance = contactPoint - m_position;
	//Vector<double> torque = glm::cross(force, distance);
	//m_torque += torque;
}
//======================================================================================================
void RigidBody::Update(float deltaTime)
{
	if (m_mass > 0.0) m_acceleration = (m_force / static_cast<float>(m_mass));
	//if (m_angularMass > 0.0) m_angularAcceleration = glm::length(m_torque) / m_angularMass;

	Vector<double> oldVelocity = m_velocity;
	m_velocity += m_acceleration * deltaTime;
	m_position += (m_velocity + oldVelocity) * 0.5f * deltaTime;

	double oldAngularVelocity = m_angularVelocity;
	m_angularVelocity += m_angularAcceleration * deltaTime;
	m_angle += (m_angularVelocity + oldAngularVelocity) * 0.5 * deltaTime;

	//Extra code to be sorted later (WIP)
	//Here we assume AngVel is a Vec3 object
	//m_angularAcceleration = m_torque;
	/*if (m_angVel.SqLen() > 0)
	{
		Vec3f axis = m_angVel;
		axis.Normalise();
		Quaternion rotThisFrame(axis, m_angVel.Len() * dt);
		m_quat = rotThisFrame * m_quat;
	}*/
}