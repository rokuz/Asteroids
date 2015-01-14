//
//  AppDelegate.m
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#import "AppDelegate.h"
#include "ViewController.h"
#include "EAGLView.h"

@interface AppDelegate()
{
    ViewController* _mainController;
    EAGLView* _view;
}
@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	_mainController = (ViewController*)self.window.rootViewController;
    _view = (EAGLView*)_mainController.view;
    [_view startAnimation];
    
    return YES;
}
							
- (void)applicationWillResignActive:(UIApplication *)application
{
    [_mainController pauseGame];
    [_view stopAnimation];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    [_view stopAnimation];
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    [_view startAnimation];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    [_view startAnimation];
    [_mainController resumeGame];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    [_view stopAnimation];
}

@end
