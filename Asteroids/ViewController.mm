//
//  ViewController.m
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#import "ViewController.h"
#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>

#include "common/timer.h"
#include "graphics/renderer.h"
#include "logic/gameField.h"
#include "logic/gameParams.h"
#include "logic/spaceship.h"

@interface ViewController ()
{
    CGPoint _startTouchPosition;
    CGSize _resolution;
    common::Timer* _timer;
    logic::GameField* _gameField;
    
    __weak IBOutlet UILabel *_titleLabel;
    __weak IBOutlet UILabel *_hintLabel;
    __weak IBOutlet UILabel *_timeLabel;
    __weak IBOutlet UILabel *_healthLabel;
    __weak IBOutlet UILabel *_gameOverLabel;
    __weak IBOutlet UILabel *_resultLabel;
}

- (void)tearDown;

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;

- (void)updateLabels;
- (BOOL)prefersStatusBarHidden;
- (NSString *)timeFormatted:(int)totalSeconds;

@end


@implementation ViewController

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    _resolution = [[UIScreen mainScreen] bounds].size;
    
    if (!graphics::Renderer::instance().init())
	{
        self.view = nil;
        [self tearDown];
	}
    else
    {
        _timer = new common::Timer();
        
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        
        // portrait only
        float sy = logic::GAMEFIELD_SIZE_X * (_resolution.height / _resolution.width);
        _gameField = new logic::GameField(vector2d(logic::GAMEFIELD_SIZE_X, sy));
        _gameField->init();
        
        [self updateLabels];
    }
    
    ((EAGLView*)self.view).renderDelegate = self;
}

- (void)dealloc
{
    [self tearDown];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    
    if ([self isViewLoaded] && ([[self view] window] == nil))
    {
        self.view = nil;
        [self tearDown];
    }
}

- (void)tearDown
{
    if (_gameField != 0)
    {
        delete _gameField;
        _gameField = 0;
    }
    
    if (_timer != 0)
    {
        delete _timer;
        _timer = 0;
    }
    
    graphics::Renderer::instance().destroy();
}

- (void)updateLabels
{
    if (_gameField != 0)
    {
        if (_gameField->isPlaying())
        {
            _titleLabel.hidden = YES;
            _hintLabel.hidden = YES;
            _gameOverLabel.hidden = YES;
            _resultLabel.hidden = YES;
            _healthLabel.hidden = NO;
            _timeLabel.hidden = NO;
            
            int health = _gameField->getSpaceship()->getHealth();
            [_healthLabel setText: [NSString stringWithFormat:@"Health: %d", health]];
            
            int seconds = (int)_gameField->getGameTime();
            [_timeLabel setText: [self timeFormatted: seconds]];
        }
        else
        {
            if (_gameField->isGameOver())
            {
                _titleLabel.hidden = YES;
                _gameOverLabel.hidden = NO;
                _resultLabel.hidden = NO;
                
                int seconds = (int)_gameField->getGameTime();
                [_resultLabel setText: [NSString stringWithFormat:@"Your time is %@.", [self timeFormatted: seconds]]];
            }
            else
            {
                _titleLabel.hidden = NO;
                _gameOverLabel.hidden = YES;
                _resultLabel.hidden = YES;
            }
            _hintLabel.hidden = NO;
            _healthLabel.hidden = YES;
            _timeLabel.hidden = YES;
        }
    }
}

- (NSString *)timeFormatted:(int)totalSeconds
{
    
    int seconds = totalSeconds % 60;
    int minutes = (totalSeconds / 60) % 60;
    int hours = totalSeconds / 3600;
    
    return [NSString stringWithFormat:@"%02d:%02d:%02d",hours, minutes, seconds];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (_gameField != 0)
    {
        if (_gameField->isPlaying())
        {
            _gameField->getSpaceship()->fire(true);
        }
        else
        {
            _gameField->startGame();
            
            [self updateLabels];
        }
    }
    
    UITouch *aTouch = [touches anyObject];
    _startTouchPosition = [aTouch locationInView: self.view];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *aTouch = [touches anyObject];
    CGPoint curTouchPosition = [aTouch locationInView: self.view];
    float offset = curTouchPosition.x - _startTouchPosition.x;
    _startTouchPosition = curTouchPosition;
    
    if (_gameField != 0 && _gameField->isPlaying())
    {
        float off = logic::GAMEFIELD_SIZE_X * offset / (float)_resolution.width;
        _gameField->getSpaceship()->move(off);
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (_gameField != 0 && _gameField->isPlaying())
    {
        _gameField->getSpaceship()->fire(false);
    }
}

- (void)render
{
    if (_gameField != 0 && _timer != 0)
    {
        _gameField->update(_timer->elapsed());
    }
    
    [self updateLabels];
    
    if (_gameField != 0)
    {
        _gameField->render();
    }
}

-(void)pauseGame
{
    if (_timer != 0)
    {
        _timer->reset();
    }
    
    if (_gameField != 0)
    {
        _gameField->pauseGame();
    }
}

-(void)resumeGame
{
    if (_timer != 0)
    {
        _timer->reset();
    }
    
    if (_gameField != 0)
    {
        _gameField->resumeGame();
    }
}

@end
