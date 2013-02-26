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
#import "GB2Engine.h"
#import "GB2WorldContactListener.h"

// default ptm ratio value
float PTM_RATIO = 32.0f;

@interface GB2Engine (private_selectors)
- (id)init;
- (void)step:(ccTime)dt;
@end

@implementation GB2Engine

@synthesize world;

+ (GB2Engine*)sharedInstance
{
	static GB2Engine* instance = 0;
	if (!instance)
    {
		instance = [[GB2Engine alloc] init];    
    }
    
	return instance;
}

-(id)init
{
    self = [super init];
    if(self)
    {
        // set default gravity
        b2Vec2 gravity(0.0f, -10.0f);
        bool doSleep = true;    
        world = new b2World(gravity);
        world->SetAllowSleeping(doSleep);
        
        // get ptmRatio from GB2ShapeCache
        if(GB2_HIGHRES_PHYSICS_SHAPES)
        {
            PTM_RATIO = [GB2ShapeCache sharedShapeCache].ptmRatio / 2.0f;            
        }
        else
        {
            PTM_RATIO = [GB2ShapeCache sharedShapeCache].ptmRatio;
        }
        
        // set the contact listener
        worldContactListener = new GB2WorldContactListener();
        world->SetContactListener(worldContactListener);    
        
        // schedule update
        [[CCDirector sharedDirector].scheduler scheduleUpdateForTarget:self priority:0 paused:NO];
    }
    return self;
}

- (void)deleteAllObjects
{
    // iterate all bodies
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) 
    {        
        GB2Node *o = (GB2Node*)(b->GetUserData());
        if(o)
        {
            // destroy physics object
            [o deleteNow];        
        }
        else
        {
            // destroy body
            world->DestroyBody(b);
        }
    }
}

- (void)deleteWorld 
{    
    // delete all objects
    [self deleteAllObjects];
    
    // delete the world
	delete world;
	world = NULL;
    
    // delete the contact listener
    delete worldContactListener;
    worldContactListener = NULL;
}


- (void)update:(ccTime)dt 
{            
    const float32 timeStep = 1.0f / 30.0f;
    const int32 velocityIterations = 5;
    const int32 positionIterations = 1;
    
    // step the world
	world->Step(timeStep, velocityIterations, positionIterations);

    [self iterateObjectsWithBlock:^(GB2Node *o) {
        // update position, rotation
        [o updateCCFromPhysics];
        
        if(o.deleteLater)
        {
            // destroys the body and removes the object from the scene
            [o deleteNow];
        }
    }];
}

- (void) iterateObjectsWithBlock:(GB2NodeCallBack)callback
{
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) 
    {        
        // get the object
        callback((GB2Node*)(b->GetUserData()));
    }    
}


@end