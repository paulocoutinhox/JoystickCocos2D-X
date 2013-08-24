#ifndef __SNEAKY_BUTTON_SKINNED_H__
#define __SNEAKY_BUTTON_SKINNED_H__

#include "SneakyButton.h"

class SneakyButtonSkinnedBase : public cocos2d::Layer 
{
	CC_SYNTHESIZE_READONLY(cocos2d::Sprite *, defaultSprite, DefaultSprite);
	CC_SYNTHESIZE_READONLY(cocos2d::Sprite *, activatedSprite, ActivatedSprite);
	CC_SYNTHESIZE_READONLY(cocos2d::Sprite *, disabledSprite, DisabledSprite);
	CC_SYNTHESIZE_READONLY(cocos2d::Sprite *, pressSprite, PressSprite);

	CC_SYNTHESIZE_READONLY(SneakyButton *, button, Button); //Not sure about this

	//Public methods
	CREATE_FUNC(SneakyButtonSkinnedBase);
	virtual ~SneakyButtonSkinnedBase();
	bool init();
	void watchSelf(float delta);
	void setContentSize(cocos2d::Size s);
	void setDefaultSprite(cocos2d::Sprite *aSprite);
	void setActivatedSprite(cocos2d::Sprite *aSprite);
	void setDisabledSprite(cocos2d::Sprite *aSprite);
	void setPressSprite(cocos2d::Sprite *aSprite);
	void setButton(SneakyButton *aButton);
};

#endif
