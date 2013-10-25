#include "ParallaxNodeExtras.h"

class CCPointObject  : CCObject
{
    CC_SYNTHESIZE(CCPoint, m_tRatio, Ratio)
    CC_SYNTHESIZE(CCPoint, m_tOffset, Offset)
    CC_SYNTHESIZE(CCNode *,m_pChild, Child)	// weak ref
};

ParallaxNodeExtras::ParallaxNodeExtras()
{
    ParallaxNode() ; // call parent constructor
}

ParallaxNodeExtras * ParallaxNodeExtras::node()
{
    return new ParallaxNodeExtras() ;
}

void ParallaxNodeExtras::incrementOffset(CCPoint offset,CCNode* node)
{
    for( unsigned int i=0;i < _parallaxArray->num;i++)
    {
        CCPointObject *point = (CCPointObject *)_parallaxArray->arr[i];
        CCNode * curNode = point->getChild() ;
        if( curNode->isEqual(node) )
        {
            point->setOffset( ccpAdd(point->getOffset(), offset) );
            break;
        }
    }
}
