#include "ParallaxScrollOffset.h"

using namespace cocos2d;

// on "init" you need to initialize your instance
bool ParallaxScrollOffset::init()
{
    if ( !CCLayer::init() ) return false;
    
    this->setRelVelocity(ccp(0,0));
    this->setScrollOffset(ccp(0,0));
    this->setPosition(ccp(0,0));
    this->setRatio(ccp(0,0));
    return true;
}

ParallaxScrollOffset* ParallaxScrollOffset::scrollWithNode(CCNode *node, CCPoint r, CCPoint p, CCPoint s)
{
    ParallaxScrollOffset *offset = ParallaxScrollOffset::create();
    return (ParallaxScrollOffset*)offset->initWithNode(node,r,p,s);
}

ParallaxScrollOffset* ParallaxScrollOffset::scrollWithNode(CCNode *node, CCPoint r, CCPoint p, CCPoint s, CCPoint v)
{
    ParallaxScrollOffset *offset = ParallaxScrollOffset::create();
    return (ParallaxScrollOffset*)offset->initWithNode(node,r,p,s,v);
}

ParallaxScrollOffset* ParallaxScrollOffset::initWithNode(CCNode *node, CCPoint r, CCPoint p, CCPoint s, CCPoint v)
{
    if(!this) return NULL;
    this->setRatio(r);
    this->setScrollOffset(s);
    this->setRelVelocity(v);
    this->setOrigPosition(p);
    node->setPosition(p);
    node->setAnchorPoint(ccp(0, 0));
    this->setTheChild(node);
    return this;
}

ParallaxScrollOffset* ParallaxScrollOffset::initWithNode(CCNode *node, CCPoint r, CCPoint p, CCPoint s)
{
    return this->initWithNode(node, r, p, p, ccp(0,0));
}
