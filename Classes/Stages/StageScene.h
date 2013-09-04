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
#include "../Extras/ParallaxScrollNode.h"
#include "../Extras/ParallaxNodeExtras.h"

class StageScene : public cocos2d::Layer
{

public:
    
    virtual bool init();
    static cocos2d::Scene* scene();
    void update(float dt);
    void setHUDLayer(Layer *layer);
    void setBackgroundLayer(ParallaxScrollNode *layer);
    static StageScene *createWithHUDAndBackGround(Layer *hudLayer, ParallaxScrollNode *backgroundLayer);

private:

    ContactListener *contactListener;
    Player *player;
    b2World *world;
    SneakyJoystick *leftJoystick;
    SneakyButton *action1Button;
    cocos2d::Layer *hudLayer;
    ParallaxScrollNode *backgroundLayer;
    cocos2d::Size worldSize;
    
    void updatePhysics(float dt);
    void createPhysics();
};

#endif
