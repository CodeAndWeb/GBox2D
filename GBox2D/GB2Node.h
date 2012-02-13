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

#import "cocos2d.h"
#import "Box2D.h"
#import "GB2ShapeCache.h"
#import "GB2Engine.h"

@interface GB2Node : NSObject
{
@protected
    b2Body* body;       //!< pointer to the box2d's body
    b2World *world;     //!< pointer to the world object
    int objectTag;      //!< tag might be used to query an object
    CCNode *ccNode;     //!< reference to the ccNode, retained
    bool deleteLater;   //!< flag to delete the object on update phase
@protected
}

@property (nonatomic, retain) CCNode *ccNode;
@property (nonatomic, assign) bool deleteLater;

/**
 * Inits the object with a CCNode but no physics object
 * @param node CCNode which represents the object
 * @return the object
 */
-(id) initWithNode:(CCNode*)node;

/**
 * Inits the object with a dynamic shape and node
 * @param shape name of the physics shape to use
 * @param node CCNode to use for this object
 * @return the object
 */
-(id) initWithDynamicBody:(NSString *)shape node:(CCNode*)node;

/**
 * Inits the object with a static shape and node
 * @param shape name of the physics shape to use
 * @param node CCNode to use for this object
 * @return the object
 */
-(id) initWithStaticBody:(NSString *)shape node:(CCNode*)node;

/**
 * Inits the object with a kinematic shape and node
 * @param shape name of the physics shape to use
 * @param node CCNode to use for this object
 * @return the object
 */
-(id) initWithKinematicBody:(NSString *)shape node:(CCNode*)node;

/**
 * Inits the object with a shape, body type and node
 * @param shape name of the physics shape to use
 * @param node CCNode to use for this object
 * @return the object
 */
-(id) initWithShape:(NSString *)shape bodyType:(b2BodyType)bodyType node:(CCNode*)node;

/**
 * Adds a fixture to the body
 * @param fixtureDef fixture definition
 * @return the added fixture
 */
-(b2Fixture*) addFixture:(b2FixtureDef*)fixtureDef;

/**
 * Starts the given action on the inner CCNode
 * Should only be used with actions which do not
 * move or scale / rotate the object
 * @param action action to run
 * @return action
 */
-(CCAction*) runAction: (CCAction*) action;

/**
 * Stops all actions on the inner CCNode
 */
-(void) stopAllActions;

/**
 * Stops the given action on the inner CCNode
 * @param action action to stop
 */
-(void) stopAction: (CCAction*) action;

/**
 * Sets the CCNode to visible/invisible
 */
-(void) setVisible:(BOOL)isVisible;

/**
 * Sets the object's angle
 * @param angle angle to set
 */
-(void) setAngle:(float)angle;

/**
 * Sets the position from pixel coordinates
 * @param p position to set
 */
-(void)setCcPosition:(CGPoint)p;

/**
 * Scales the graphics (currently not the object!)
 * @param scale scale to set
 */
-(void) setScale:(float)scale;

/**
 * Returns the object's position in pixel coordinates
 */
-(CGPoint)ccPosition;

/**
 * Delete the object, remove it from the parent scene
 */
-(void) deleteNow;

/**
 * Returns true if the body is awake
 */
-(BOOL) isAwake;

/**
 * Called by GB2Engine to update the shape's position
 * and rotation from the physics coordinates 
 */
-(void) updateCCFromPhysics;

/**
 * Replaces the current fixtures with the new shape
 * @param shapeName name of the shape to set
 */
-(void) setBodyShape:(NSString*)shapeName;

/**
 * Returns the object's mass
 * @return mass
 */
-(float) mass;

/**
 * Returns the position of the object in physics coordinates
 * @return position
 */
-(b2Vec2) physicsPosition;

/**
 * Sets the physics position of the object
 * @param position position to set
 */
-(void) setPhysicsPosition:(b2Vec2)position;

/**
 * Returns the world center of the object
 * @return world center
 */
-(b2Vec2) worldCenter;

/**
 * Replaces the object's fixtures with the new shape
 * and sets the positon and body type to kinematic
 * @param shapeName name of the shape to set
 * @param pos position of the object
 */
-(void) setKinematicBody:(NSString*)shapeName position:(b2Vec2)pos;

/**
 * Replaces the object's fixtures with the new shape
 * and sets the positon and body type to dynamic
 * @param shapeName name of the shape to set
 * @param pos position of the object
 */
-(void) setDynamicBody:(NSString*)shapeName position:(b2Vec2)pos;

/**
 * Replaces the object's fixtures with the new shape
 * and sets the positon and body type to static
 * @param shapeName name of the shape to set
 * @param pos position of the object
 */
-(void) setStaticBody:(NSString*)shapeName position:(b2Vec2)pos;

/**
 * Sets the body type of the object
 * b2_kinematicBody, b2_staticBody, b2_dynamicBody
 * @param bodyType
 */
-(void) setBodyType:(b2BodyType)bodyType;

/**
 * Applies an impulse at the given point of the object
 * Use [self worldCenter] to apply the impulse to the 
 * center of the object without setting the object 
 * into a rotation
 * @param impulse impulse to apply
 * @param point point to apply the impulse to
 */
-(void) applyLinearImpulse:(b2Vec2)impulse point:(b2Vec2)point;

/**
 * Sets the linear velocity of the object
 * @param velocity velocity vector to set
 */
-(void) setLinearVelocity:(b2Vec2)velocity;

/**
 * Enables / disables rotation on the object
 * If called with YES the object can't rotate
 * @param fixedRotation
 */
-(void) setFixedRotation:(bool)fixedRotation;

/**
 * Add damping
 * @param linearDamping daming value to set
 */
-(void) setLinearDamping:(float)linearDamping;

/**
 * Add angular damping
 * @param angularDamping damping value
 */
-(void) setAngularDamping:(float)angularDamping;

/**
 * Apply a force to the given point of the object
 * @param force force to apply
 * @param point point on the object to apply the force to
 */
-(void) applyForce:(b2Vec2)force point:(b2Vec2)point;

/**
 * Returns the angle of the object
 * @return angle
 */
-(float) angle;

/**
 * Sets the position and rotation of the object
 * @param pos position to set
 * @param angle angle to set
 */
-(void) setTransform:(b2Vec2)pos angle:(float)angle;

/**
 * Returns true if the object is active (participates
 * in collition detection etc.
 */
-(bool) active;

/**
 * Sets the object to active (or not)
 * If the object is inactive it will not participate in 
 * collition detection
 */
-(void) setActive:(bool)isActive;

/**
 * Returns true if the body is sleeping
 * That means was not hit by other objects for some time
 * @return true if object is awake
 */
-(bool) awake;

/**
 * Returns the linear velocity of the object
 * @return linear velocity
 */
-(b2Vec2) linearVelocity;

/**
 * Sets the object to bullet mode and activates continuous collision
 * detection for the object
 */
-(void) setBullet:(bool)bulletFlag;

/**
 * Destroys the physics body of the object
 */
-(void) destroyBody;

/**
 * Returns the object's width in meters taken from the
 * sprite's size. If the sprite has transparent borders
 * this might differ from the object's real size
 */
-(float) widthInM;

/**
 * Clears mask bits on the object's fixtures
 * Bits to clear must be set to 1
 * @param bits bits to clear
 */
-(void) clrCollisionMaskBits:(uint16)bits;

/**
 * Clears mask bits on the object's fixtures
 * Bits to clear must be set to 1
 * @param bits bits to clear
 * @param forId only change the bits for the given fixtureID
 */
-(void) clrCollisionMaskBits:(uint16)bits forId:(NSString*)fixtureId;

/**
 * Adds mask bits on the object's fixtures
 * Bits to set must be set to 1
 * @param bits bits to set
 */
-(void) addCollisionMaskBits:(uint16)bits;

/**
 * Adds mask bits on the object's fixtures
 * Bits to set must be set to 1
 * @param bits bits to set
 * @param forId only change the bits for the given fixtureID
 */
-(void) addCollisionMaskBits:(uint16)bits forId:(NSString*)fixtureId;

/**
 * Sets the mask bits to the given value
 * @param bits bits
 */
-(void) setCollisionMaskBits:(uint16)bits;

/**
 * Sets the mask bits to the given value
 * @param bits bits
 * @param forId only change the bits for the given fixtureID
 */
-(void) setCollisionMaskBits:(uint16)bits forId:(NSString*)fixtureId;

/**
 * Add bits to the collision category
 * @param bits bits to set
 */
-(void) addCollisionCategoryBits:(uint16)bits;

/**
 * Add bits to the collision category
 * @param bits bits to set
 * @param forId only change the bits for the given fixtureID
 */
-(void) addCollisionCategoryBits:(uint16)bits forId:(NSString*)fixtureId;

/**
 * Clr bits on the collition category
 * Bits to clear must be set to 1
 * @param bits to clr
 */
-(void) clrCollisionCategoryBits:(uint16)bits;

/**
 * Clr bits on the collition category
 * Bits to clear must be set to 1
 * @param bits to clr
 * @param forId only change the bits for the given fixtureID
 */
-(void) clrCollisionCategoryBits:(uint16)bits forId:(NSString*)fixtureId;

/**
 * Sets the category bits to the given value
 * @param bits bits to set
 */
-(void) setCollisionCategoryBits:(uint16)bits;

/**
 * Sets the category bits to the given value
 * @param bits bits to set
 * @param forId only change the bits for the given fixtureID
 */
-(void) setCollisionCategoryBits:(uint16)bits forId:(NSString*)fixtureId;

/**
 * Returns the object's tag
 * @return tag of the object
 */
-(int) objectTag;

/**
 * Tag the object with an integer value
 * @param tag tag value to set
 */
-(void) setObjectTag:(int)tag;


/**
 * Sets the object's angular velocity
 * @param v velocity to set
 */
-(void) setAngularVelocity:(float32)v;

/**
 * Adds an edge to the fixture
 */
-(void) addEdgeFrom:(b2Vec2)start to:(b2Vec2)end;
@end
