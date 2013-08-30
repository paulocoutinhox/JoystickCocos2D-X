#include "StageScene.h"

USING_NS_CC;

Scene* StageScene::scene()
{
    Scene *scene = Scene::create();
    StageScene *layer = StageScene::create();
    scene->addChild(layer);
    return scene;
}

bool StageScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    // create bottom label
    LabelTTF* label = LabelTTF::create("Joystick Cocos2D-X Version 3", "Arial", 12);
    
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + label->getContentSize().height));

    this->addChild(label, 1);

    // add game background
    Sprite* sprite = Sprite::create("BackgroundGame.png");
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
    // add joystick
    int joystickOffset = 10;
    
    Rect joystickBaseDimensions = Rect(0, 0, 64.0f, 64.0f);
    Point joystickBasePosition  = Point(origin.x + (joystickBaseDimensions.size.width / 2) + joystickOffset, origin.y + (joystickBaseDimensions.size.height / 2) + joystickOffset);
    
    Rect accelButtonDimensions = Rect(0, 0, 64.0f, 64.0f);
    Point accelButtonPosition  = Point(origin.x + visibleSize.width - (joystickBaseDimensions.size.width / 2) - joystickOffset,origin.y + (joystickBaseDimensions.size.height / 2) + joystickOffset);
    
    // add joystick base
    SneakyJoystickSkinnedBase *joystickBase = SneakyJoystickSkinnedBase::create();
    SneakyJoystick *joystick = new SneakyJoystick();
    joystick->initWithRect(joystickBaseDimensions);
    joystickBase->setBackgroundSprite(CCSprite::create("joystick/dpadDown.png"));
    joystickBase->setThumbSprite(CCSprite::create("joystick/joystickDown.png"));
    joystickBase->setJoystick(joystick);
    joystickBase->setPosition(joystickBasePosition);
    leftJoystick = joystickBase->getJoystick();
    addChild(joystickBase);
    
    // add joystick button
    SneakyButtonSkinnedBase *action1ButtonBase = SneakyButtonSkinnedBase::create();
    SneakyButton *button1 = new SneakyButton();
    button1->initWithRect(accelButtonDimensions);
    action1ButtonBase->setDefaultSprite(CCSprite::create("joystick/action1Down.png"));
    action1ButtonBase->setActivatedSprite(CCSprite::create("joystick/action1Down.png"));
    action1ButtonBase->setPressSprite(CCSprite::create("joystick/action1Up.png"));
    action1ButtonBase->setButton(button1);
    action1ButtonBase->setPosition(accelButtonPosition);
    action1Button = action1ButtonBase->getButton();
    addChild(action1ButtonBase);
    
    // create physics
    createPhysics();
    
    // add the player
    player = new Player();
	player->init(this, world);    
    addChild(player->getBatchNode());
    
    // rest of framework init process
    scheduleUpdate();

    return true;
}

void StageScene::update(float dt)
{
    // update the physics
    updatePhysics(dt);

    // update the player
    if (player)
    {
        player->update(dt);
        player->updateVelocity(leftJoystick->getVelocity());
        
        if (action1Button->getIsActive())
        {
            player->actionButtonPressed(1);
        }
    }

    // update collisions
    std::vector<ContactData>::iterator pos;
    for(pos = contactListener->_contacts.begin(); pos != contactListener->_contacts.end(); ++pos)
    {
        ContactData contact = *pos;

        // get the box2d bodies for each object
        b2Body *bodyA = contact.fixtureA->GetBody();
        b2Body *bodyB = contact.fixtureB->GetBody();

        if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL)
        {
            Entity *entityA = (Entity*)bodyA->GetUserData();
            Entity *entityB = (Entity*)bodyB->GetUserData();

            int iTagA = entityA->getTag();
            int iTagB = entityB->getTag();

            if (iTagA == Entity::TAG_PLAYER)
            {

            }
            else if (iTagB == Entity::TAG_PLAYER)
            {

            }
        }
    }
}

void StageScene::updatePhysics(float dt)
{
    world->Step(dt, 10, 10);
}

void StageScene::createPhysics()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    // world
    b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
    world = new b2World(gravity);

    // contact listener
    contactListener = new ContactListener();
    world->SetContactListener(contactListener);

    // create edges around the entire screen
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, (66 / PTM_RATIO));

    b2Body *groundBody = world->CreateBody(&groundBodyDef);
    b2EdgeShape groundEdge;
    b2FixtureDef boxShapeDef;
    boxShapeDef.shape = &groundEdge;

    // wall definitions
    groundEdge.Set(b2Vec2(0,0), b2Vec2(visibleSize.width/PTM_RATIO, 0));
    groundBody->CreateFixture(&boxShapeDef);
}
