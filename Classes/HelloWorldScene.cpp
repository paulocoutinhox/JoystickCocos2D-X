#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    // create and initialize a label
    LabelTTF* label = LabelTTF::create("Joystick Cocos2D Version 3", "Arial", 12);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    Sprite* sprite = Sprite::create("BackgroundGame.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    // add joystick
    int joystickOffset = 10;
    
    Rect joystickBaseDimensions = Rect(0, 0, 64.0f, 64.0f);
    Point joystickBasePosition  = Point(origin.x + (joystickBaseDimensions.size.width / 2) + joystickOffset, origin.y + (joystickBaseDimensions.size.height / 2) + joystickOffset);
    
    Rect accelButtonDimensions = Rect(0, 0, 64.0f, 64.0f);
    Point accelButtonPosition  = Point(origin.x + visibleSize.width - (joystickBaseDimensions.size.width / 2) - joystickOffset,origin.y + (joystickBaseDimensions.size.height / 2) + joystickOffset);
    
    // add joystick base
    SneakyJoystickSkinnedBase *joystickBase = SneakyJoystickSkinnedBase::create();
    SneakyJoystick *joystick = new SneakyJoystick();
    joystick->initWithRect(joystickBaseDimensions);
    joystickBase->setBackgroundSprite(CCSprite::create("dpadDown.png"));
    joystickBase->setThumbSprite(CCSprite::create("joystickDown.png"));
    joystickBase->setJoystick(joystick);
    joystickBase->setPosition(joystickBasePosition);
    leftJoystick = joystickBase->getJoystick();
    addChild(joystickBase);
    
    // add joystick button
    SneakyButton *action1Button = new SneakyButton();
    SneakyButtonSkinnedBase *action1ButtonBase = SneakyButtonSkinnedBase::create();
    action1Button->initWithRect(accelButtonDimensions);
    action1ButtonBase->setDefaultSprite(CCSprite::create("action1Down.png"));
    action1ButtonBase->setActivatedSprite(CCSprite::create("action1Down.png"));
    action1ButtonBase->setPressSprite(CCSprite::create("action1Up.png"));
    action1ButtonBase->setButton(action1Button);
    action1ButtonBase->setPosition(accelButtonPosition);
    action1Button = action1ButtonBase->getButton();
    action1Button->setIsToggleable(true);
    addChild(action1ButtonBase);
    
    return true;
}


void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
