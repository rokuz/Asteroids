//
//  Asteroids
//
//  Based on https://developer.apple.com/library/ios/samplecode/GLEssentials/Introduction/Intro.html#//apple_ref/doc/uid/DTS40010104
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>

@interface ES2Renderer : NSObject
{
}

- (ES2Renderer*)initWithContext:(EAGLContext *) context AndDrawable:(id<EAGLDrawable>)drawable;
- (void)beginRender;
- (void)endRender;
- (BOOL)resizeFromLayer:(CAEAGLLayer*)layer;

@end

