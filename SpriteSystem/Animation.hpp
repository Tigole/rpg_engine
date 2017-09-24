#ifndef _ANIMATION_HPP
#define _ANIMATION_HPP 1

#include "Animation/IAnimation.hpp"

class Animation : public IAnimation
{
public:
	Animation();

protected:
	//
};

class SpriteAnimation : public Animation
{
public:
	SpriteAnimation();

	virtual bool mt_Reset(void);

	void mt_Update(float delta_time_ms);
	void mt_Play(void);
	void mt_Stop(void);
};

#endif // !_ANIMATION_HPP
