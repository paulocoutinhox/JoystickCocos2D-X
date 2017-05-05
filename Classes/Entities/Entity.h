#ifndef ENTITY_H
#define ENTITY_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#define PTM_RATIO 32.0

class Entity
{

public:

    static const int TAG_PLAYER = 1;
    static const int TAG_GROUND = 2;
    static const int TAG_WALL   = 3;

    Entity();
    virtual ~Entity();
    void setBatchNode(cocos2d::SpriteBatchNode *batchNode);
    cocos2d::SpriteBatchNode *getBatchNode();
    cocos2d::Sprite *getSprite();
    int getDirection();
    int getState();
    virtual int getTag();

protected:

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
    int state; // 1 = default, 2 = moving, 3 = jumping

};

#endif // ENTITY_H
