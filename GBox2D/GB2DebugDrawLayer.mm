/*
 MIT License
 
 Copyright (c) 2010 Andreas Loew / www.code-and-web.de
 
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

#import "GB2DebugDrawLayer.h"
#import "GB2Engine.h"
#import "GLES-Render.h"
#import "Box2D.h"

@implementation GB2DebugDrawLayer

-(id) init
{
    self = [super init];
    if(self)
    {
        // take world from the singleton
        world = [GB2Engine sharedInstance].world;

        // Enable debug draw
        debugDraw = new GLESDebugDraw(PTM_RATIO);
        world->SetDebugDraw(debugDraw);
        
        // Set the flags
        uint32 flags = 0;
        flags += b2Draw::e_shapeBit;
        // flags += b2DebugDraw::e_aabbBit;
        flags += b2Draw::e_centerOfMassBit;
        
        debugDraw->SetFlags(flags);            
    }
    return self;
}

-(void)dealloc
{
    // remove debug draw from the world
    world->SetDebugDraw(0);
    
    // delete debug draw
    delete debugDraw;
    
    // dealloc super objects
    [super dealloc];
}

-(void) draw
{
    [super draw];
    
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
    kmGLPushMatrix();
    
    // draw the world stuff
	world->DrawDebugData();
    kmGLPopMatrix();
    
}

@end
