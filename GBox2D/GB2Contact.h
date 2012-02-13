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

#pragma once

@class GB2Node;

/** 
 * GB2Contact
 *
 * This class represents a contact between 2 objects
 * It is used as parameter to the contact resolving function
 *
 * The callee get his own object and fixture in own*,
 * the opponent's data in other*
 */
@interface GB2Contact: NSObject
{
    @private
    b2Fixture *ownFixture;   /**< the fixture that collided */
    GB2Node *otherObject;    /**< the other object */
    b2Fixture *otherFixture; /**< the other object's fixture that collided */
    b2Contact *box2dContact; /**< the box2d contact structure */
}

@property (nonatomic, retain) GB2Node *otherObject;
@property b2Fixture *ownFixture;
@property b2Fixture *otherFixture;
@property b2Contact *box2dContact;

-(id) initWithObject:(GB2Node*)object ownFixture:(b2Fixture*)ownFixture otherObject:(GB2Node*)otherObject otherFixture:(b2Fixture*)otherFixture b2Contact:(b2Contact*)contact;
+(id) contactWithObject:(GB2Node*)object ownFixture:(b2Fixture*)ownFixture otherObject:(GB2Node*)otherObject otherFixture:(b2Fixture*)otherFixture b2Contact:(b2Contact*)contact;

/**
 * Sets a collition to disabled
 * You can use this in the presolver phase to disable contacts
 * between Sprites
 */
-(void) setEnabled:(BOOL)enabled;

@end

