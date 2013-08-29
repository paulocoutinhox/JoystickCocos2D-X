#ifndef __JoystickCocos2D__Player__
#define __JoystickCocos2D__Player__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#define PTM_RATIO 32.0

class Player : cocos2d::Object
{
    
public:
    
    cocos2d::Sprite *sprite;
    cocos2d::RepeatForever *actionStateDefault;
    cocos2d::RepeatForever *actionStateMoving;
    cocos2d::Animate *animateDefault;
    cocos2d::Animate *animateMoving;
    cocos2d::Animation *animationDefault;
    cocos2d::Animation *animationMoving;
    cocos2d::SpriteBatchNode *batchNode;
    
    int direction;
    b2Body *body;
    b2World *world;
    int state; // 1 = default, 2 = moving
    
    Player();
    virtual ~Player(void);
    virtual bool init(cocos2d::Layer *layer, b2World *world);
    void update(float dt);
    void updateVelocity(cocos2d::Point velocity);
    void move(cocos2d::Point velocity);
    void stopMoving();
    void actionButtonPressed(int button);
    
    void setStateDefault();
    void setStateMoving();
    void changeDirection(int direction);
    
    void setBatchNode(cocos2d::SpriteBatchNode *batchNode);
    cocos2d::SpriteBatchNode *getBatchNode();
    cocos2d::Sprite *getSprite();    
    
};

#endif
