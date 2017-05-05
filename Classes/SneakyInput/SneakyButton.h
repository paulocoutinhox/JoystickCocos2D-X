#ifndef __SNEAKY_BUTTON_H__
#define __SNEAKY_BUTTON_H__

#include "cocos2d.h"

class SneakyButton : public cocos2d::Node
{
	CC_SYNTHESIZE(bool, status, Status);
	CC_SYNTHESIZE_READONLY(bool, active, IsActive);
	CC_SYNTHESIZE_READONLY(bool, value, Value);
	CC_SYNTHESIZE(bool, isHoldable, IsHoldable);
	CC_SYNTHESIZE(bool, isToggleable, IsToggleable);
	CC_SYNTHESIZE(float, rateLimit, RateLimit);

	CC_SYNTHESIZE_READONLY(float, radius, Radius);
    
public:
    SneakyButton();
	bool initWithRect(cocos2d::Rect rect);
    
	void limiter(float delta);
	void setRadius(float r);
    void setTouchEnabled(bool enabled);
    bool isTouchEnabled() const;
    std::function<void(SneakyButton *)> onFire;
    
	virtual bool ccTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void ccTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void ccTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void ccTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    
protected:
    cocos2d::Point center;
    float radiusSq;
    
    cocos2d::Rect bounds;
private:
    cocos2d::EventListenerTouchOneByOne* _touchListener;

};

#endif