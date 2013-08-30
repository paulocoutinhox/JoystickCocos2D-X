#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <vector>

#define PTM_RATIO 32.0

struct ContactData {
    b2Fixture *fixtureA;
    b2Fixture *fixtureB;
    bool operator==(const ContactData& other) const
    {
        return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
    }
};

class ContactListener : public b2ContactListener {

public:
    std::vector<ContactData>_contacts;

    ContactListener();
    ~ContactListener();

    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

};

#endif
