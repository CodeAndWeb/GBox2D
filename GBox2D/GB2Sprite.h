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
#import "GB2Node.h"


@interface GB2Sprite : GB2Node
{
}

/**
 * Create a GB2Sprite with the given shape and dispay frame name.
 * The body is created as dynamic body
 * @param shape shape name for the body
 * @param spriteName name of the sprite
 */
-(id) initWithDynamicBody:(NSString *)shape spriteFrameName:(NSString*)spriteName;

/**
 * Create a GB2Sprite with the given shape and dispay frame name.
 * The body is created as static body
 * @param shape shape name for the body
 * @param spriteName name of the sprite
 */
-(id) initWithStaticBody:(NSString *)shape spriteFrameName:(NSString*)spriteName;

/**
 * Create a GB2Sprite with the given shape and dispay frame name.
 * The body is created as kinematic body
 * @param shape shape name for the body
 * @param spriteName name of the sprite
 */
-(id) initWithKinematicBody:(NSString *)shape spriteFrameName:(NSString*)spriteName;

/**
 * Create a GB2Sprite with the given shape and dispay frame name.
 * The body is created as dynamic body
 * @param shape shape name for the body
 * @param spriteName name of the sprite
 */
+(id) spriteWithDynamicBody:(NSString *)shape spriteFrameName:(NSString*)spriteName;

/**
 * Create a GB2Sprite with the given shape and dispay frame name.
 * The body is created as static body
 * @param shape shape name for the body
 * @param spriteName name of the sprite
 */
+(id) spriteWithStaticBody:(NSString *)shape spriteFrameName:(NSString*)spriteName;

/**
 * Create a GB2Sprite with the given shape and dispay frame name.
 * The body is created as kinematic body
 * @param shape shape name for the body
 * @param spriteName name of the sprite
 */
+(id) spriteWithKinematicBody:(NSString *)shape spriteFrameName:(NSString*)spriteName;

/**
 * Sets the display frame on the inner CCSprite
 * @param newFrame frame to set
 */
-(void) setDisplayFrame:(CCSpriteFrame*)newFrame;

/**
 * Sets a display frame by it's name
 * @param name name of the frame to set
 */
-(void) setDisplayFrameNamed:(NSString*)name;

@end
