#ifndef ParallaxScrollNodeTest_ParallaxScrollNode_h
#define ParallaxScrollNodeTest_ParallaxScrollNode_h

#include "cocos2d.h"
#include "ParallaxScrollOffset.h"

using namespace cocos2d;

typedef cocos2d::Vector<ParallaxScrollOffset *> ParallaxScrollOffsetVector;
typedef cocos2d::Vector<cocos2d::Sprite *> SpriteVector;

class ParallaxScrollNode : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(ParallaxScrollNode);
    
    cocos2d::SpriteBatchNode batch;
    cocos2d::Size _range;
    ParallaxScrollOffsetVector _scrollOffsets;
    
    void addChild(cocos2d::Sprite *node, int z, cocos2d::Vec2 r, cocos2d::Vec2 p, cocos2d::Vec2 so);
    void addChild(cocos2d::Sprite *node, int z, cocos2d::Vec2 r, cocos2d::Vec2 p, cocos2d::Vec2 so, cocos2d::Vec2 v);
    
    void removeChild(cocos2d::Sprite *node, bool cleanup);
    void updateWithVelocity(cocos2d::Vec2 vel, float dt);
    void updateWithYPosition(float y, float dt);
    void updateWithXPosition(float x, float dt);
    
    void addInfiniteScrollWithZ(int z, cocos2d::Vec2 ratio, cocos2d::Vec2 pos, cocos2d::Vec2 dir, cocos2d::Sprite *firstObject, ...);
    void addInfiniteScrollXWithZ(int z, cocos2d::Vec2 ratio, cocos2d::Vec2 pos, cocos2d::Sprite* firstObject, ...);
    void addInfiniteScrollYWithZ(int z,  cocos2d::Vec2 ratio, cocos2d::Vec2 pos, cocos2d::Sprite* firstObject, ...);
    
    void addInfiniteScrollWithObjects(SpriteVector objects, int z, cocos2d::Vec2 ratio, cocos2d::Vec2 pos, cocos2d::Vec2 dir);
    void addInfiniteScrollWithObjects(SpriteVector objects, int z, cocos2d::Vec2 ratio, cocos2d::Vec2 pos, cocos2d::Vec2 dir, cocos2d::Vec2 relVel);
    void addInfiniteScrollWithObjects(SpriteVector objects, int z, cocos2d::Vec2 ratio, cocos2d::Vec2 pos, cocos2d::Vec2 dir, cocos2d::Vec2 relVel, cocos2d::Vec2 padding);
    
};

#endif
