#include "Player.h"

USING_NS_CC;

Player::Player()
{
    direction = 2; // 1 = left, 2 = right
    state     = 1;
}

Player::~Player(void)
{
    Object::~Object();
	actionStateDefault->release();
	actionStateMoving->release();
    body = NULL;
}

bool Player::init(Layer *layer, b2World *world)
{
    // some variables
    visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // node and spite
    batchNode = SpriteBatchNode::create("orc/Orc.pvr.ccz");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("orc/Orc.plist");
    sprite = CCSprite::createWithSpriteFrameName("Orc_move_right0001.png");
    
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // animation for default state
    animationDefault = Animation::create();
    
    for (int i = 1; i < 2; i++)
    {
        char szImageFileName[128] = {0};
        sprintf(szImageFileName, "Orc_move_right00%02i.png", i);
        animationDefault->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szImageFileName));
    }
    
    animationDefault->setDelayPerUnit(1.0 / 1);
    animationDefault->setRestoreOriginalFrame(true);
    
    animateDefault = CCAnimate::create(animationDefault);
    actionStateDefault = RepeatForever::create(animateDefault);
    // actionStateDefault will be undefined after this scope. Because of that we need to retain it. 
	// We have to release it in destructor.
	actionStateDefault->retain();

    // animation for moving state
    animationMoving = Animation::create();
    
    for (int i = 1; i < 17; i++)
    {
        char szImageFileName[128] = {0};
        sprintf(szImageFileName, "Orc_move_right00%02i.png", i);
        animationMoving->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szImageFileName));
    }
    
    animationMoving->setDelayPerUnit(0.04f);
    animationMoving->setRestoreOriginalFrame(true);
    
    animateMoving = CCAnimate::create(animationMoving);
    actionStateMoving = RepeatForever::create(animateMoving);
    // actionStateMoving will be undefined after this scope. Because of that we need to retain it. 
	// We have to release it in destructor.
	actionStateMoving->retain();

    // create physics
    this->world = world;
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(sprite->getPositionX() /PTM_RATIO, sprite->getPositionY()/PTM_RATIO);
    bodyDef.userData = this;
    bodyDef.fixedRotation = false;
    body = world->CreateBody(&bodyDef);
    
    b2PolygonShape shape;
    shape.SetAsBox(1,1);
    
    b2FixtureDef shapeDef;
    shapeDef.shape = &shape;
    shapeDef.density = 3.0f;
    shapeDef.friction = 4.0f;
    shapeDef.restitution = 0.0f;
    body->CreateFixture(&shapeDef);
    
    // set default state
    setStateDefault();
    changeDirection(direction);
    
    batchNode->addChild(sprite);
    
    return true;
}

void Player::update(float dt)
{
    if (world)
    {
        world->Step(dt, 10, 10);
        for(b2Body *b = world->GetBodyList(); b; b=b->GetNext())
        {
            if (b->GetUserData() != NULL)
            {
                Player *ballData = (Player *)b->GetUserData();
				cocos2d::Size spriteSize = ballData->getSprite()->getContentSize();
                ballData->getSprite()->setPosition(Point(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
				
				// if orc reach the left wall, stop it here
				if(ballData->getSprite()->getPositionX() <= spriteSize.width / 2)
				{	
					b->SetTransform(b2Vec2((spriteSize.width / 2 + 0.1f) / PTM_RATIO, b->GetPosition().y), 0.0f);
					ballData->sprite->setPosition(Point((spriteSize.width / 2 + 0.1f), b->GetPosition().y * PTM_RATIO));
				}

				// if orc reach the right wall, stop it here
				if(ballData->getSprite()->getPositionX() >= visibleSize.width - (spriteSize.width / 2))
				{	
					b->SetTransform(b2Vec2((visibleSize.width - (spriteSize.width / 2) - 0.1f)/ PTM_RATIO, b->GetPosition().y), 0.0f);
					ballData->sprite->setPosition(Point((visibleSize.width - (spriteSize.width / 2) - 0.1f), b->GetPosition().y * PTM_RATIO));
				}
            }
        }
    }
}

void Player::updateVelocity(Point velocity)
{
    move(velocity);
}

void Player::move(Point velocity)
{
    b2Vec2 impulse;
    
    if (velocity.x > 0)
    {
        // move right
        setStateMoving();
        
        changeDirection(2);
        
        impulse = b2Vec2(0.25f * body->GetMass(), 0.0f);
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter());
    }
    else if (velocity.x < 0)
    {
        // move left
        setStateMoving();
        changeDirection(1);
        
        impulse = b2Vec2(-0.25f * body->GetMass(), 0.0f);
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter());
    }
    else
    {
        // not moving
        setStateDefault();
    }
}

void Player::setStateDefault()
{
    if (state == 2)
    {
        state = 1;
		sprite->stopAllActions();
        sprite->runAction(actionStateDefault);
        
    }
}

void Player::setStateMoving()
{
    if (state == 1)
    {
        state = 2;
		sprite->stopAllActions();
        sprite->runAction(actionStateMoving);
    }
}

void Player::stopMoving()
{
    if (state == 2)
    {
        body->SetLinearVelocity(b2Vec2(0, 0));
    }
}

void Player::actionButtonPressed(int button)
{
    if (button == 1)
    {
        body->ApplyLinearImpulse(b2Vec2(0, body->GetMass() * 3), body->GetWorldCenter());
    }
}

void Player::changeDirection(int direction)
{
    if (this->direction != direction && direction == 1)
    {
        sprite->setFlipX(true);
        this->direction = direction;
        
        if (state == 2)
        {
            stopMoving();
        }
    }
    else if (this->direction != direction && direction == 2)
    {
        sprite->setFlipX(false);
        this->direction = direction;
        
        if (state == 2)
        {
            stopMoving();
        }
    }
}

void Player::setBatchNode(SpriteBatchNode *batchNode)
{
    this->batchNode = batchNode;
}

SpriteBatchNode *Player::getBatchNode()
{
    return batchNode;
}

cocos2d::Sprite *Player::getSprite()
{
    return sprite;
}