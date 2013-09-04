#ifndef CCParallaxNodeExtras_H
#define CCParallaxNodeExtras_H

#include "cocos2d.h"

USING_NS_CC;

class ParallaxNodeExtras : public ParallaxNode
{
public:
    ParallaxNodeExtras();
    static ParallaxNodeExtras * node() ;
    void incrementOffset(CCPoint offset,CCNode* node) ;
};

#endif
