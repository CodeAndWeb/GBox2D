/*
 MIT License
 
 Copyright (c) 2010 Andreas Loew / www.code-and-web.de
 
 For more information about htis module visit
 http://www.PhysicsEditor.de

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#import "Box2D.h"
#import "GB2Contact.h"
#import "GB2WorldContactListener.h"

GB2WorldContactListener::GB2WorldContactListener()
: b2ContactListener()
{
}

GB2WorldContactListener::~GB2WorldContactListener() 
{
}

/**
 * Calls constructed selectors on the objects involved in the collision
 *
 * If a is an object of type A, and b is object of type B this method will
 * call 
 *
 * universal selector:
 *    [a <contactType>:gb2contactB];
 *    [b <contactType>:gb2contactA];
 *
 * typed selector:
 *    [a <contactType>WithB:gb2contactB];
 *    [b <contactType>WithA:gb2contactA];
 *
 * @param contact the b2Contact 
 * @param contactType string containing "beginContact", "endContact" or "presolveContact"
 */
void GB2WorldContactListener::notifyObjects(b2Contact *contact, NSString *contactType)
{
    b2Body *bodyA = contact->GetFixtureA()->GetBody();
    b2Body *bodyB = contact->GetFixtureB()->GetBody();
    
    GB2Node *a = (GB2Node *)bodyA->GetUserData();
    GB2Node *b = (GB2Node *)bodyB->GetUserData();
    
    NSString *nameContactUniversal = [NSString stringWithFormat:@"%@:", contactType];
    NSString *nameContactA = [NSString stringWithFormat:@"%@With%@:", contactType, NSStringFromClass([a class])];
    NSString *nameContactB = [NSString stringWithFormat:@"%@With%@:", contactType, NSStringFromClass([b class])];
    
    SEL selectorContactWithB = NSSelectorFromString(nameContactB);
    SEL selectorContactUniversal = NSSelectorFromString(nameContactUniversal);
    if([a respondsToSelector:selectorContactWithB])
    {
        // perform designated contact listener
        GB2Contact *contactWithB = [GB2Contact contactWithObject:a 
                                                ownFixture:contact->GetFixtureA() 
                                               otherObject:b  
                                              otherFixture:contact->GetFixtureB()
                                                 b2Contact:contact
                                 ];    
        [a performSelector:selectorContactWithB withObject:contactWithB];
    }        
    else if([a respondsToSelector:selectorContactUniversal])
    {
        // perform universal contact listener
        GB2Contact *contactWithB = [GB2Contact contactWithObject:a 
                                                ownFixture:contact->GetFixtureA() 
                                               otherObject:b  
                                              otherFixture:contact->GetFixtureB()
                                                 b2Contact:contact
                                ];    
        [a performSelector:selectorContactUniversal withObject:contactWithB];        
    }
    
    SEL selectorContactWithA = NSSelectorFromString(nameContactA);
    if([b respondsToSelector:selectorContactWithA])
    {
        // perform designated contact listener
        GB2Contact *contactWithA = [GB2Contact contactWithObject:b 
                                                ownFixture:contact->GetFixtureB() 
                                               otherObject:a  
                                              otherFixture:contact->GetFixtureA()
                                                 b2Contact:contact
                                 ];
        [b performSelector:selectorContactWithA withObject:contactWithA];
    }    
    else if([b respondsToSelector:selectorContactUniversal])
    {
        // perform universal contact listener
        GB2Contact *contactWithA = [GB2Contact contactWithObject:b 
                                                ownFixture:contact->GetFixtureB()
                                               otherObject:a
                                              otherFixture:contact->GetFixtureA()
                                                 b2Contact:contact
                                 ];
        [b performSelector:selectorContactUniversal withObject:contactWithA];        
    }
}

/// Called when two fixtures begin to touch.
void GB2WorldContactListener::BeginContact(b2Contact* contact) 
{
    notifyObjects(contact, @"beginContact");        
}

/// Called when two fixtures cease to touch.
void GB2WorldContactListener::EndContact(b2Contact* contact) 
{ 
    notifyObjects(contact, @"endContact");
}

/// This is called after a contact is updated. This allows you to inspect a
/// contact before it goes to the solver. If you are careful, you can modify the
/// contact manifold (e.g. disable contact).
/// A copy of the old manifold is provided so that you can detect changes.
/// Note: this is called only for awake bodies.
/// Note: this is called even when the number of contact points is zero.
/// Note: this is not called for sensors.
/// Note: if you set the number of contact points to zero, you will not
/// get an EndContact callback. However, you may get a BeginContact callback
/// the next step.
void GB2WorldContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    B2_NOT_USED(contact);
    B2_NOT_USED(oldManifold);

    notifyObjects(contact, @"presolveContact");        
}

/// This lets you inspect a contact after the solver is finished. This is useful
/// for inspecting impulses.
/// Note: the contact manifold does not include time of impact impulses, which can be
/// arbitrarily large if the sub-step is small. Hence the impulse is provided explicitly
/// in a separate data structure.
/// Note: this is only called for contacts that are touching, solid, and awake.
void GB2WorldContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    B2_NOT_USED(contact);
    B2_NOT_USED(impulse);
}


