//
//  ViewController.h
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "EAGLView.h"

@interface ViewController : UIViewController<RenderDelegate>

-(void)pauseGame;
-(void)resumeGame;

@end
