#ifndef PLAYER_H
#define PLAYER_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Entity.h"

#define PTM_RATIO 32.0

class Player : public Entity
{
    
public:

    Player();
    virtual ~Player();
    virtual bool init(cocos2d::Layer *layer, b2World *world);
    void update(float dt);
    void updateVelocity(cocos2d::Point velocity);
    void move(cocos2d::Point velocity);
    void stopMoving();
    void actionButtonPressed(int button);
    
    void setStateDefault();
    void setStateMoving();
    void changeDirection(int direction);

    int getTag();

};

#endif
