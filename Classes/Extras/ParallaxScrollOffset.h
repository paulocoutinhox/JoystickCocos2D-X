#ifndef ParallaxScrollNodeTest_CCParallaxScrollOffset_h
#define ParallaxScrollNodeTest_CCParallaxScrollOffset_h

#include "cocos2d.h"
using namespace cocos2d;

class ParallaxScrollOffset : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(ParallaxScrollOffset);

    CC_SYNTHESIZE(cocos2d::Vec2, scrollOffset, ScrollOffset);
    CC_SYNTHESIZE(cocos2d::Vec2, origPosition, OrigPosition);
    CC_SYNTHESIZE(cocos2d::Vec2, relVelocity, RelVelocity);
    CC_SYNTHESIZE(cocos2d::Vec2, ratio, Ratio);
    CC_SYNTHESIZE(cocos2d::Vec2, buffer, Buffer);
    CC_SYNTHESIZE(cocos2d::Node*, theChild, TheChild);
    
    static ParallaxScrollOffset* scrollWithNode(cocos2d::Node *node, cocos2d::Vec2 r, cocos2d::Vec2 p, cocos2d::Vec2 s);
    static ParallaxScrollOffset* scrollWithNode(cocos2d::Node *node, cocos2d::Vec2 r, cocos2d::Vec2 p, cocos2d::Vec2 s, cocos2d::Vec2 v);
    ParallaxScrollOffset* initWithNode(cocos2d::Node *node, cocos2d::Vec2 r, cocos2d::Vec2 p, cocos2d::Vec2 s, cocos2d::Vec2 v);
    ParallaxScrollOffset* initWithNode(cocos2d::Node *node, cocos2d::Vec2 r, cocos2d::Vec2 p, cocos2d::Vec2 s);
};

#endif
