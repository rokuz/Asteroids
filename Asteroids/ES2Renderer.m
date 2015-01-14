//
//  Asteroids
//
//  Based on https://developer.apple.com/library/ios/samplecode/GLEssentials/Introduction/Intro.html#//apple_ref/doc/uid/DTS40010104
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#import "ES2Renderer.h"

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@interface ES2Renderer (PrivateMethods)
@end

@implementation ES2Renderer

EAGLContext * m_context;
GLuint m_colorRenderbuffer;
GLuint m_depthRenderbuffer;
GLuint m_defaultFBOName;

- (ES2Renderer*)initWithContext:(EAGLContext *) context AndDrawable:(id<EAGLDrawable>)drawable
{	
	glGenFramebuffers(1, &m_defaultFBOName);
	
	glGenRenderbuffers(1, &m_colorRenderbuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFBOName);
	glBindRenderbuffer(GL_RENDERBUFFER, m_colorRenderbuffer);
	m_context = context;
	
	[m_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:drawable];
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorRenderbuffer);
	
	GLint backingWidth;
	GLint backingHeight;
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &backingWidth);
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &backingHeight);
	
	glGenRenderbuffers(1, &m_depthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, backingWidth, backingHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderbuffer);
	
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		NSLog(@"failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
		return NO;
	}
	
	self = [super init];
	
	if (nil == self)
	{
		glDeleteFramebuffers(1, &m_defaultFBOName);
		glDeleteRenderbuffers(1, &m_colorRenderbuffer);
		glDeleteRenderbuffers(1, &m_depthRenderbuffer);
	}
	
	return self;
}

- (void)beginRender
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFBOName);
}

- (void)endRender
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_colorRenderbuffer);
    [m_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (BOOL)resizeFromLayer:(CAEAGLLayer *)layer
{
	GLint backingWidth;
	GLint backingHeight;
	
    glBindRenderbuffer(GL_RENDERBUFFER, m_colorRenderbuffer);
    [m_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer];
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &backingWidth);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &backingHeight);
	
	glGenRenderbuffers(1, &m_depthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, backingWidth, backingHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderbuffer);
	
    glViewport(0, 0, backingWidth, backingHeight);
	
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
        NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
        return NO;
    }
	
    return YES;
}

- (void)dealloc
{
	if (m_defaultFBOName)
	{
		glDeleteFramebuffers(1, &m_defaultFBOName);
		m_defaultFBOName = 0;
	}
	
	if (m_colorRenderbuffer)
	{
		glDeleteRenderbuffers(1, &m_colorRenderbuffer);
		m_colorRenderbuffer = 0;
	}
    
    if (m_depthRenderbuffer)
	{
		glDeleteRenderbuffers(1, &m_depthRenderbuffer);
		m_depthRenderbuffer = 0;
	}
}

@end
