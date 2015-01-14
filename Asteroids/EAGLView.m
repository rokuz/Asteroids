//
//  Asteroids
//
//  Based on https://developer.apple.com/library/ios/samplecode/GLEssentials/Introduction/Intro.html#//apple_ref/doc/uid/DTS40010104
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#import "EAGLView.h"
#import "ES2Renderer.h"

@implementation EAGLView

@dynamic animationFrameInterval;

+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (id)initWithCoder:(NSCoder*)coder
{    
    if ((self = [super initWithCoder:coder]))
	{
        // Get the layer
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        
        eaglLayer.opaque = TRUE;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
		
		
		m_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        
        if (!m_context || ![EAGLContext setCurrentContext:m_context])
		{
			return nil;
		}
		
		m_renderer = [[ES2Renderer alloc] initWithContext:m_context AndDrawable:(id<EAGLDrawable>)self.layer];
		
		if (!m_renderer)
		{
			return nil;
		}
        
		_animating = FALSE;
		displayLinkSupported = FALSE;
		animationFrameInterval = 1;
		displayLink = nil;
		animationTimer = nil;
		
		NSString *reqSysVer = @"3.1";
		NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
		if ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending)
			displayLinkSupported = TRUE;
    }
	
    return self;
}

- (void)drawView:(id)sender
{   
	[EAGLContext setCurrentContext:m_context];
    [m_renderer beginRender];
    [self.renderDelegate render];
    [m_renderer endRender];
}

- (void)layoutSubviews
{
	[m_renderer resizeFromLayer:(CAEAGLLayer*)self.layer];
    [self drawView:nil];
    [super layoutSubviews];
}

- (NSInteger)animationFrameInterval
{
	return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
	if (frameInterval >= 1)
	{
		animationFrameInterval = frameInterval;
		
		if (_animating)
		{
			[self stopAnimation];
			[self startAnimation];
		}
	}
}

- (void)startAnimation
{
	if (!_animating)
	{
		if (displayLinkSupported)
		{
			displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(drawView:)];
			[displayLink setFrameInterval:animationFrameInterval];
			[displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
		}
		else
			animationTimer = [NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)((1.0 / 60.0) * animationFrameInterval) target:self selector:@selector(drawView:) userInfo:nil repeats:TRUE];
		
		_animating = TRUE;
	}
}

- (void)stopAnimation
{
	if (_animating)
	{
		if (displayLinkSupported)
		{
			[displayLink invalidate];
			displayLink = nil;
		}
		else
		{
			[animationTimer invalidate];
			animationTimer = nil;
		}
		
		_animating = FALSE;
	}
}

- (void)dealloc
{
	if ([EAGLContext currentContext] == m_context)
        [EAGLContext setCurrentContext:nil];
}

@end
