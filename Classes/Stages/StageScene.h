#ifndef STAGE_SCENE_H
#define STAGE_SCENE_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../SneakyInput/SneakyButton.h"
#include "../SneakyInput/SneakyButtonSkinnedBase.h"
#include "../SneakyInput/SneakyJoystick.h"
#include "../SneakyInput/SneakyJoystickSkinnedBase.h"
#include "../Entities/Player.h"
#include "../ContactListener.h"

class StageScene : public cocos2d::Layer
{

public:
    
    virtual bool init();
    static cocos2d::Scene* scene();
    void update(float dt);
    
    CREATE_FUNC(StageScene);

private:

    ContactListener *contactListener;
    Player *player;
    b2World *world;
    SneakyJoystick *leftJoystick;
    SneakyButton *action1Button;

    void updatePhysics(float dt);
    void createPhysics();
};

#endif
