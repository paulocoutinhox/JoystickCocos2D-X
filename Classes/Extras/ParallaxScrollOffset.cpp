#include "ParallaxScrollOffset.h"

using namespace cocos2d;

// on "init" you need to initialize your instance
bool ParallaxScrollOffset::init()
{
    if ( !cocos2d::Layer::init() ) return false;
    
    this->setRelVelocity(cocos2d::Vec2(0,0));
    this->setScrollOffset(cocos2d::Vec2(0,0));
    this->setPosition(cocos2d::Vec2(0,0));
    this->setRatio(cocos2d::Vec2(0,0));
    return true;
}

ParallaxScrollOffset* ParallaxScrollOffset::scrollWithNode(cocos2d::Node *node, cocos2d::Vec2 r, cocos2d::Vec2 p, cocos2d::Vec2 s)
{
    ParallaxScrollOffset *offset = ParallaxScrollOffset::create();
    return (ParallaxScrollOffset*)offset->initWithNode(node,r,p,s);
}

ParallaxScrollOffset* ParallaxScrollOffset::scrollWithNode(cocos2d::Node *node, cocos2d::Vec2 r, cocos2d::Vec2 p, cocos2d::Vec2 s, cocos2d::Vec2 v)
{
    ParallaxScrollOffset *offset = ParallaxScrollOffset::create();
    return (ParallaxScrollOffset*)offset->initWithNode(node,r,p,s,v);
}

ParallaxScrollOffset* ParallaxScrollOffset::initWithNode(cocos2d::Node *node, cocos2d::Vec2 r, cocos2d::Vec2 p, cocos2d::Vec2 s, cocos2d::Vec2 v)
{
    if(!this) return NULL;
    this->setRatio(r);
    this->setScrollOffset(s);
    this->setRelVelocity(v);
    this->setOrigPosition(p);
    node->setPosition(p);
    node->setAnchorPoint(cocos2d::Vec2(0, 0));
    this->setTheChild(node);
    return this;
}

ParallaxScrollOffset* ParallaxScrollOffset::initWithNode(cocos2d::Node *node, cocos2d::Vec2 r, cocos2d::Vec2 p, cocos2d::Vec2 s)
{
    return this->initWithNode(node, r, p, p, cocos2d::Vec2(0,0));
}
