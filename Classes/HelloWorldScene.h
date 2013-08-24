#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SneakyInput/SneakyButton.h"
#include "SneakyInput/SneakyButtonSkinnedBase.h"
#include "SneakyInput/SneakyJoystick.h"
#include "SneakyInput/SneakyJoystickSkinnedBase.h"
#include "Player.h"

class HelloWorld : public cocos2d::Layer
{
public:
    
    virtual bool init();
    static cocos2d::Scene* scene();
    void update(float dt);
    
    CREATE_FUNC(HelloWorld);
    
    SneakyJoystick *leftJoystick;
    SneakyButton *action1Button;
    
    // player
    Player *player;
    
    // box2d
    b2World *world;
};

#endif
