//
//  Asteroids
//
//  Based on https://developer.apple.com/library/ios/samplecode/GLEssentials/Introduction/Intro.html#//apple_ref/doc/uid/DTS40010104
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ES2Renderer.h"

@protocol RenderDelegate<NSObject>
@required
- (void)render;
@end

@interface EAGLView : UIView
{
    id<RenderDelegate> _renderDelegate;
    
@private
	ES2Renderer *m_renderer;
	EAGLContext *m_context;
	BOOL displayLinkSupported;
	NSInteger animationFrameInterval;
	id displayLink;
    NSTimer *animationTimer;
}

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;
@property (nonatomic,strong) id renderDelegate;

- (void) startAnimation;
- (void) stopAnimation;
- (void) drawView:(id)sender;

@end
