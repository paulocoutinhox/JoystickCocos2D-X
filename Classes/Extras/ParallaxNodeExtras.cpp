#include "ParallaxNodeExtras.h"

class CCPointObject  : cocos2d::Ref
{
    CC_SYNTHESIZE(cocos2d::Vec2, m_tRatio, Ratio)
    CC_SYNTHESIZE(cocos2d::Vec2, m_tOffset, Offset)
    CC_SYNTHESIZE(cocos2d::Node *,m_pChild, Child)	// weak ref
};

ParallaxNodeExtras::ParallaxNodeExtras()
{
    ParallaxNode() ; // call parent constructor
}

ParallaxNodeExtras * ParallaxNodeExtras::node()
{
    return new ParallaxNodeExtras() ;
}

void ParallaxNodeExtras::incrementOffset(cocos2d::Vec2 offset,cocos2d::Node* node)
{
    for( unsigned int i=0;i < _parallaxArray->num;i++)
    {
        CCPointObject *point = (CCPointObject *)_parallaxArray->arr[i];
        cocos2d::Node * curNode = point->getChild() ;
        if( curNode == node )
        {
            point->setOffset( point->getOffset() + offset );
            break;
        }
    }
}
