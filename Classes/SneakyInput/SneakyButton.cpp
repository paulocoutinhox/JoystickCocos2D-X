#include "SneakyButton.h"

using namespace cocos2d;

SneakyButton::SneakyButton() : onFire(nullptr)
{
    
}

bool SneakyButton::isTouchEnabled() const
{
    return _touchListener != nullptr;
}

void SneakyButton::setTouchEnabled(bool enabled)
{
    _eventDispatcher->removeEventListener(_touchListener);
    _touchListener = nullptr;
    
    if (enabled)
    {
        _touchListener = EventListenerTouchOneByOne::create();
        _touchListener->setSwallowTouches(true);
        _touchListener->onTouchBegan = CC_CALLBACK_2(SneakyButton::ccTouchBegan, this);
        _touchListener->onTouchMoved = CC_CALLBACK_2(SneakyButton::ccTouchMoved, this);
        _touchListener->onTouchEnded = CC_CALLBACK_2(SneakyButton::ccTouchEnded, this);
        _touchListener->onTouchCancelled = CC_CALLBACK_2(SneakyButton::ccTouchCancelled, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    }
}

bool SneakyButton::initWithRect(Rect rect)
{
	bool pRet = false;
	//if(cocos2d::Sprite::init()){
		
		bounds = Rect(0, 0, rect.size.width, rect.size.height);
		center = Point(rect.size.width/2, rect.size.height/2);
		status = 1; //defaults to enabled
		active = false;
		value = 0;
		isHoldable = 0;
		isToggleable = 0;
		radius = 32.0f;
		rateLimit = 1.0f/120.0f;
		
		setPosition(rect.origin); //not sure about this
        setTouchEnabled(true);
		pRet = true;
	//}
	return pRet;
}

void SneakyButton::limiter(float delta)
{
	value = 0;
	this->unschedule(schedule_selector(SneakyButton::limiter));
	active = false;
}

void SneakyButton::setRadius(float r)
{
	radius = r;
	radiusSq = r*r;
}

bool SneakyButton::ccTouchBegan(Touch *touch, Event *event)
{
	if (active) return false;
	
	Point location = Director::getInstance()->convertToGL(touch->getLocationInView());
	location = this->convertToNodeSpace(location);
		//Do a fast rect check before doing a circle hit check:
	if(location.x < -radius || location.x > radius || location.y < -radius || location.y > radius){
		return false;
	}else{
		float dSq = location.x*location.x + location.y*location.y;
		if(radiusSq > dSq){
			active = true;
            if (onFire) {
                this->onFire(this);
            }
			if (!isHoldable && !isToggleable){
				value = 1;
				this->schedule(schedule_selector(SneakyButton::limiter), rateLimit);
			}
			if (isHoldable) value = 1;
			if (isToggleable) value = !value;
			return true;
		}
	}
return false;
}

void SneakyButton::ccTouchMoved(Touch *touch, Event *event)
{
	if (!active) return;
	
	Point location = Director::getInstance()->convertToGL(touch->getLocationInView());
	location = this->convertToNodeSpace(location);
		//Do a fast rect check before doing a circle hit check:
	if(location.x < -radius || location.x > radius || location.y < -radius || location.y > radius){
		return;
	}else{
		float dSq = location.x*location.x + location.y*location.y;
		if(radiusSq > dSq){
			if (isHoldable) value = 1;
		}
		else {
			if (isHoldable) value = 0; active = false;
		}
	}
}

void SneakyButton::ccTouchEnded(Touch *touch, Event *event)
{
	if (!active) return;
	if (isHoldable) value = 0;
	if (isHoldable||isToggleable) active = false;
}

void SneakyButton::ccTouchCancelled(Touch *touch, Event *event)
{
	this->ccTouchEnded(touch, event);
}
