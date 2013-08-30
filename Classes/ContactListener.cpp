#include "ContactListener.h"

ContactListener::ContactListener(): _contacts()
{
}

ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
    // We need to copy out the data because the b2Contact passed in
    // is reused.
    ContactData Contact = { contact->GetFixtureA(), contact->GetFixtureB() };
    _contacts.push_back(Contact);
}

void ContactListener::EndContact(b2Contact* contact)
{
    ContactData Contact = { contact->GetFixtureA(), contact->GetFixtureB() };
    std::vector<ContactData>::iterator pos;
    pos = std::find(_contacts.begin(), _contacts.end(), Contact);
    if (pos != _contacts.end())
    {
        _contacts.erase(pos);
    }
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}
