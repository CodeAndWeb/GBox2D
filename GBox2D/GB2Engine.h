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
#import "GB2Node.h"
#import "GB2Config.h"

#pragma once

/**
 * The PTM_RATIO
 * Using it as a global variable is ugly but hiding it into
 * GB2Engine would slow down things too much.
 */
extern float PTM_RATIO;


@class GB2Node;

/**
 * Type for block callbacks with GB2Node objects
 * Used in iterateObjectsWithBlock
 */
typedef void(^GB2NodeCallBack)(GB2Node*);

/**
 * Convert b2Vec2 to CGPoint honoring PTM_RATIO
 */
inline b2Vec2 b2Vec2FromCGPoint(const CGPoint &p)
{
    return b2Vec2(p.x/PTM_RATIO, p.y/PTM_RATIO);
}

inline b2Vec2 b2Vec2FromCC(float x, float y)
{
    return b2Vec2(x/PTM_RATIO, y/PTM_RATIO);
}

/**
 * Convert CGPoint to b2Vec2 honoring PTM_RATIO
 */
inline CGPoint CGPointFromb2Vec2(const b2Vec2 &p)
{
    return CGPointMake(p.x * PTM_RATIO, p.y*PTM_RATIO);
}

class GB2WorldContactListener;

/**
 * GB2Engine
 * 
 * Wrapper for the Box2d simulation
 * Implemented as singleton to allow simple adding of new
 * objects
 */
@interface GB2Engine : NSObject 
{
    GB2WorldContactListener *worldContactListener;
    b2World* world;
}

/**
 * Access to the b2World object
 */
@property (readonly, assign) b2World* world;

/**
 * Returns the shared instance
 */
+ (GB2Engine *)sharedInstance;

/**
 * Delete all objects in the world
 * including the world
 */
- (void)deleteWorld;

/**
 * Delete all objects
 */
- (void)deleteAllObjects;

/**
 * Iterate all objects and performs the block with the object
 */
- (void) iterateObjectsWithBlock:(GB2NodeCallBack)callback;

@end



