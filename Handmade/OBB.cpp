#include "OBB.h"
#include "Screen.h"

//======================================================================================================
void OBB::SetRotation(float angle)
{
	m_angle = angle;
}
//======================================================================================================
void OBB::SetScale(float x, float y)
{
	m_scale.x = x;
	m_scale.y = y;
}
//======================================================================================================
void OBB::SetPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}
//======================================================================================================
void OBB::SetDimension(float width, float height)
{
	m_dimension.x = width;
	m_dimension.y = height;
}
//======================================================================================================
bool OBB::IsColliding(const OBB& secondBox) const
{
	OBB tempBox[2];
	tempBox[0] = *this;
	tempBox[1] = secondBox;

	return IsColliding(tempBox);
}
//======================================================================================================
bool OBB::IsColliding(const BoxCollider& secondBox) const
{
	//TODO - Fix this
	/*OBB collider;

	collider.SetScale(secondBox.GetScale());
	collider.SetPosition(secondBox.GetPosition());
	collider.SetDimension(secondBox.GetDimension());
	collider.Update();

	return IsColliding(collider);*/
	return true;
}
//======================================================================================================
void OBB::Update()
{
	Vector<float> halfDimension(m_dimension.x * m_scale.x * 0.5f, m_dimension.y * m_scale.y * 0.5f);

	//Use the up and right vector to calculate box's corners 
	//below and to create projection vectors to project onto later on
	//We have to reset them to their defaults before rotating them
	m_upAxis = Vector<float>::Up;
	m_rightAxis = Vector<float>::Right;

	//TODO - Fix this. We need to rotate the up/right vectors around Z
	//TODO - Do we use a simple 2x2 matrix here or find some way to rotate vector?

	//Transform the up and right vectors based on how the OBB is rotated 
	/*m_upAxis = m_rotation.GetMatrix() * m_upAxis * halfDimension.y;
	m_rightAxis = m_rotation.GetMatrix() * m_rightAxis * halfDimension.x;*/

	//Calculate all four corners of the box based on bound's centre 
	//position, starting in the top left corner and moving clockwise
	m_corners[0] = m_position - m_rightAxis + m_upAxis;
	m_corners[1] = m_position + m_rightAxis + m_upAxis;
	m_corners[2] = m_position + m_rightAxis - m_upAxis;
	m_corners[3] = m_position - m_rightAxis - m_upAxis;
}
//======================================================================================================
bool OBB::IsColliding(const OBB* tempBox) const
{
	//Assign all four temporary axes based on both boxes' up and right axes 
	//These will be the four axes that all eight corners are projected onto
	std::array<Vector<float>, 4> axes;

	axes[0] = tempBox[0].m_rightAxis;
	axes[1] = tempBox[0].m_upAxis;
	axes[2] = tempBox[1].m_rightAxis;
	axes[3] = tempBox[1].m_upAxis;

	for (int i = 0; i < 4; i++)
	{
		//Reset the min and max extent values each time a new axis is tested
		//Set both min and max to the first projected corner of each box
		std::array<Vector<float>, 2> extents;
		extents[0].x = extents[0].y = m_corners[0].Dot(axes[i].Normalize());
		extents[1].x = extents[1].y = tempBox[1].m_corners[0].Dot(axes[i].Normalize());

		//Now loop through each box...
		for (int j = 0; j < 2; j++)
		{
			//...and through each corner
			for (int k = 0; k < 4; k++)
			{
				//project each box's corner onto the current active axis
				//use the length of this projection to calculate min and max projection values 
				auto projection = tempBox[j].m_corners[k].Dot(axes[i].Normalize());

				//Find the min and max extent values for each box
				extents[j].x = std::min(projection, extents[j].x);
				extents[j].y = std::max(projection, extents[j].y);
			}
		}

		//If there is at least 1 extent non-overlap found
		//boxes do not collide, so return false immediately
		if (!(extents[0].y > extents[1].x && extents[1].y > extents[0].x))
		{
			return false;
		}
	}

	//Otherwise there are extent overlaps for each axis
	//and that means both boxes collide, so return true
	return true;
}