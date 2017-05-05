#ifndef __SNEAKY_JOYSTICK_H__
#define __SNEAKY_JOYSTICK_H__

#include "cocos2d.h"

class SneakyJoystick : public cocos2d::Node
{
	CC_SYNTHESIZE_READONLY(cocos2d::Point, stickPosition, StickPosition);
	CC_SYNTHESIZE_READONLY(float, degrees, Degrees);
	CC_SYNTHESIZE_READONLY(cocos2d::Point, velocity, Velocity);
	CC_SYNTHESIZE(bool, autoCenter, AutoCenter);
	CC_SYNTHESIZE_READONLY(bool, isDPad, IsDPad);
	CC_SYNTHESIZE(bool, hasDeadzone, HasDeadzone);
	CC_SYNTHESIZE(int, numberOfDirections, NumberOfDirections);

	CC_SYNTHESIZE_READONLY(float, joystickRadius, JoystickRadius);
	CC_SYNTHESIZE_READONLY(float, thumbRadius, ThumbRadius);
	CC_SYNTHESIZE_READONLY(float, deadRadius, DeadRadius);
    
public:
    SneakyJoystick();

	bool initWithRect(cocos2d::Rect rect);
    
    void setTouchEnabled(bool enabled);
    bool isTouchEnabled() const;
	void setIsDPad(bool b);
	void setJoystickRadius(float r);
	void setThumbRadius(float r);
	void setDeadRadius(float r);
    
    std::function<void(SneakyJoystick*, cocos2d::Point, cocos2d::Point)> onVelocityChanged;
    
	virtual bool ccTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void ccTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void ccTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void ccTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    
protected:
    float joystickRadiusSq;
    float thumbRadiusSq;
    float deadRadiusSq;

private:
	void updateVelocity(cocos2d::Point point);
	void setTouchRadius();
    void sendVelocityEvent();
    cocos2d::EventListenerTouchOneByOne* _touchListener;
};
#endif
