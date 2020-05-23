//====================
//to be removed!
//====================

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Sprite.h"

class Animation : public Sprite
{

public:

	Animation();
	virtual ~Animation() {}

public:

	bool IsAnimationDead() const;
	bool& IsAnimationLooping();
	void SetAnimationVelocity(float velocity);
	
public:

	virtual void Draw(int xPosition = 0, int yPosition = 0, 
		              double angle = 0.0, FlipType flipType = FlipType::NO_FLIP);

protected:

	bool m_isAnimationDead;
	bool m_isAnimationLoopFinal;
	bool m_isAnimationLooping;
	
	double m_timeElapsed;
	float m_animationVelocity;

};

#endif