#include "ParallaxScrollNode.h"

#ifndef PTM_RATIO
#define PTM_RATIO 32
#endif

#ifndef SIGN
#define SIGN(x) ((x < 0) ? -1 : (x > 0))
#endif

bool ParallaxScrollNode::init()
{
    if ( !cocos2d::Layer::init() ) return false;
    
    cocos2d::Size screen = cocos2d::Director::getInstance()->getWinSize();
    _range = cocos2d::Size(screen.width, screen.height);
    this->setAnchorPoint(cocos2d::Vec2(0,0));
    
    return true;
}

// Used with box2d style velocity (m/s where m = 32 pixels), but box2d is not required
void ParallaxScrollNode::updateWithVelocity(cocos2d::Vec2 vel, float dt)
{
    vel = vel * PTM_RATIO;
//    cocos2d::log("count: %zi", _scrollOffsets.size());
    
    for (ParallaxScrollOffset * scrollOffset : _scrollOffsets)
    {
        cocos2d::Vec2 relVel = scrollOffset->getRelVelocity() * PTM_RATIO;
        cocos2d::Vec2 totalVel = vel + relVel;
        cocos2d::Vec2 offset = (totalVel * dt);
        offset.scale(scrollOffset->getRatio());
        
        cocos2d::Node *child = scrollOffset->getTheChild();
        child->setPosition(child->getPosition() + offset);

        if ( (offset.x < 0 && child->getPosition().x + child->getContentSize().width < 0) ||
             (offset.x > 0 && child->getPosition().x > _range.width) )
        {
            child->setPosition(child->getPosition() + cocos2d::Vec2(-SIGN(offset.x) * fabs(scrollOffset->getScrollOffset().x), 0));
        }

        // Positive y indicates upward movement in cocos2d
        if ( (offset.y < 0 && child->getPosition().y + child->getContentSize().height < 0) ||
             (offset.y > 0 && child->getPosition().y > _range.height) )
        {
            child->setPosition(child->getPosition() + cocos2d::Vec2(0, -SIGN(offset.y) * fabs(scrollOffset->getScrollOffset().y)));
        }
    }
}


void ParallaxScrollNode::updateWithYPosition(float y, float dt)
{	
    
    for (ParallaxScrollOffset * scrollOffset : _scrollOffsets)
    {
        cocos2d::Node *child = scrollOffset->getTheChild();
        float offset = y * scrollOffset->getRatio().y;
        child->setPosition(cocos2d::Vec2(child->getPosition().x, scrollOffset->getOrigPosition().y + offset));
    }
}

void ParallaxScrollNode::updateWithXPosition(float x, float dt)
{
    for (ParallaxScrollOffset * scrollOffset : _scrollOffsets)
    {
        cocos2d::Node *child = scrollOffset->getTheChild();
        float offset = x * scrollOffset->getRatio().x;
        child->setPosition(cocos2d::Vec2(scrollOffset->getOrigPosition().x + offset, child->getPosition().y));
    }
}

void ParallaxScrollNode::addChild(cocos2d::Sprite *node, int z, cocos2d::Vec2 r, cocos2d::Vec2 p, cocos2d::Vec2 so, cocos2d::Vec2 v)
{
    node->setAnchorPoint(cocos2d::Vec2(0,0));
    
    ParallaxScrollOffset *obj = ParallaxScrollOffset::scrollWithNode(node, r, p, so, v);
    _scrollOffsets.pushBack(obj);
    this->cocos2d::Node::addChild(node, z);
}

void ParallaxScrollNode::addChild(cocos2d::Sprite *node, int z, cocos2d::Vec2 r, cocos2d::Vec2 p, cocos2d::Vec2 so){
    this->addChild(node,z,r,p,so,cocos2d::Vec2(0,0));
}

void ParallaxScrollNode::removeChild(cocos2d::Sprite *node, bool cleanup)
{
    ParallaxScrollOffset *toDelete;
    for (ParallaxScrollOffset * scrollOffset : _scrollOffsets)
    {
        if( scrollOffset->getTheChild() == node){
            toDelete = scrollOffset;
            break;
        }
    }
    _scrollOffsets.eraseObject(toDelete);
}

void ParallaxScrollNode::addInfiniteScrollWithObjects(SpriteVector objects, int z, cocos2d::Vec2 ratio, cocos2d::Vec2 pos, cocos2d::Vec2 dir, cocos2d::Vec2 relVel, cocos2d::Vec2 padding)
{
    // NOTE: corrects for 1 pixel at end of each sprite to avoid thin lines appearing

    // Calculate total width and height
    float totalWidth = 0;
    float totalHeight = 0;
    
    for (cocos2d::Sprite *sprite : objects)
    {
        totalWidth += sprite->getContentSize().width + dir.x * padding.x;
        totalHeight += sprite->getContentSize().height + dir.y * padding.y;
    }
    
    // Position objects, add to parallax
    cocos2d::Vec2 currPos = pos;
    
    for (cocos2d::Sprite *sprite : objects)
    {
        this->addChild(sprite, z, ratio, currPos, cocos2d::Vec2(totalWidth, totalHeight), relVel);
        cocos2d::Vec2 nextPosOffset = cocos2d::Vec2(dir.x * (sprite->getContentSize().width + padding.x), dir.y * (sprite->getContentSize().height + padding.y));
        currPos = currPos + nextPosOffset;
    }
}

void ParallaxScrollNode::addInfiniteScrollWithObjects(SpriteVector objects, int z, cocos2d::Vec2 ratio, cocos2d::Vec2 pos, cocos2d::Vec2 dir, cocos2d::Vec2 relVel)
{
    this->addInfiniteScrollWithObjects(objects, z, ratio, pos, dir, relVel, cocos2d::Vec2(-1,-1));
}

void ParallaxScrollNode::addInfiniteScrollWithObjects(SpriteVector objects, int z, cocos2d::Vec2 ratio, cocos2d::Vec2 pos, cocos2d::Vec2 dir)
{
    this->addInfiniteScrollWithObjects(objects, z, ratio, pos, dir, cocos2d::Vec2(0,0));
}

void ParallaxScrollNode::addInfiniteScrollXWithZ(int z, cocos2d::Vec2 ratio, cocos2d::Vec2 pos, cocos2d::Sprite* firstObject, ...){
    va_list args;
    va_start(args, firstObject);

    SpriteVector argArray;
    for (cocos2d::Sprite *arg = firstObject; arg != NULL; arg = va_arg(args, cocos2d::Sprite*))
    {
        argArray.pushBack(arg);
    }
    va_end(args);

    this->addInfiniteScrollWithObjects(argArray, z, ratio, pos, cocos2d::Vec2(1,0));
}
