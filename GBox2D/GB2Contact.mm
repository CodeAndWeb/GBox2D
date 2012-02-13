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

#import "GB2Contact.h"
#import "cocos2d.h"
#import "GB2Node.h"

@implementation GB2Contact

@synthesize otherObject;
@synthesize ownFixture;
@synthesize otherFixture;
@synthesize box2dContact;

-(id) initWithObject:(GB2Node*)myOwnObject ownFixture:(b2Fixture*)myOwnFixture otherObject:(GB2Node*)theOtherObject otherFixture:(b2Fixture*)theOtherFixture  b2Contact:(b2Contact*)theB2Contact
{
    self = [super init];
    if(self)
    {
        otherObject = [theOtherObject retain];
        ownFixture = myOwnFixture;
        otherFixture = theOtherFixture;
        box2dContact = theB2Contact;
    }
    return self;
}

+(id) contactWithObject:(GB2Node*)ownObject ownFixture:(b2Fixture*)ownFixture otherObject:(GB2Node*)otherObject otherFixture:(b2Fixture*)otherFixture b2Contact:(b2Contact*)contact
{
    return [[[GB2Contact alloc] initWithObject:ownObject ownFixture:ownFixture otherObject:(GB2Node*)otherObject otherFixture:otherFixture b2Contact:contact] autorelease];
}

-(void) setEnabled:(BOOL)enabled
{
    box2dContact->SetEnabled(enabled);
}

-(void) dealloc
{
    [otherObject release];
    [super dealloc];
}

@end


