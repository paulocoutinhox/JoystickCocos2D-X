#include "Entity.h"

USING_NS_CC;

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::setBatchNode(SpriteBatchNode *batchNode)
{
    this->batchNode = batchNode;
}

SpriteBatchNode *Entity::getBatchNode()
{
    return batchNode;
}

cocos2d::Sprite *Entity::getSprite()
{
    return sprite;
}

int Entity::getDirection()
{
    return direction;
}

int Entity::getState()
{
    return state;
}

int Entity::getTag()
{
    return 0;
}
