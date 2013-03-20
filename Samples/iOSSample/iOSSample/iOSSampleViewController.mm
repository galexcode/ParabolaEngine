//
//  iOSSampleViewController.m
//  iOSSample
//
//  Created by Artur on 7/26/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import "iOSSampleViewController.h"
#import "EAGLView.h"
#include <ParabolaCore/iOS_Bridge.h>

@interface iOSSampleViewController ()
@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, assign) CADisplayLink *displayLink;
@end

@implementation iOSSampleViewController

@synthesize animating;
@synthesize context;
@synthesize displayLink;

- (void)awakeFromNib
{
	int gl_version = ios_bridge_getGLESVersion();
	EAGLContext *aContext = 0;
	
	if(gl_version == 1)
	{
		aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
	}
	else if(gl_version == 2)
	{
		aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
		if(!aContext)
		{
			EAGLContext *aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
			NSLog(@"Failed to create a OpenGL ES 2.0 context. Attempting to fallback to OpenGL ES 1.0");
		}
	}
	
    if (!aContext)
        NSLog(@"Failed to create ES context");
    else if (![EAGLContext setCurrentContext:aContext])
        NSLog(@"Failed to set ES context current");
	
	self.context = aContext;
	[aContext release];
	
    [(EAGLView *)self.view setContext:context];
    [(EAGLView *)self.view setFramebuffer];
	
    animating = FALSE;
    animationFrameInterval = 1;
    self.displayLink = nil;
	
    ios_bridge_initialize();
}

- (void)dealloc
{
	ios_bridge_destroy();
	
    // Tear down context.
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
	
    [context release];
	
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
    // Release any cached data, images, etc. that aren't in use.
	ios_bridge_release_data();
}

- (void)viewWillAppear:(BOOL)animated
{
    [self startAnimation];
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self stopAnimation];
    [super viewWillDisappear:animated];
}

- (void)viewDidUnload
{
	[super viewDidUnload];
	ios_bridge_unload();
    // Tear down context.
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
	self.context = nil;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
    // Enumerate over all the touches and draw a red dot on the screen where the touches were
	__block int i = 0;
    [touches enumerateObjectsUsingBlock:^(id obj, BOOL *stop) {
        // Get a single touch and it's location
        UITouch *touch = obj;
        CGPoint touchPoint = [touch locationInView:self.view];
		
        ios_bridge_touch_pressed(touchPoint.x, touchPoint.y, i++);
		
    }];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
    // Enumerate over all the touches and draw a red dot on the screen where the touches were
	__block int i = 0;
    [touches enumerateObjectsUsingBlock:^(id obj, BOOL *stop) {
        // Get a single touch and it's location
        UITouch *touch = obj;
        CGPoint touchPoint = [touch locationInView:self.view];
        ios_bridge_touch_released(touchPoint.x, touchPoint.y, i++);
    }];
}


- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event{
    // Enumerate over all the touches and draw a red dot on the screen where the touches were
	__block int i = 0;
    [touches enumerateObjectsUsingBlock:^(id obj, BOOL *stop) {
        // Get a single touch and it's location
        UITouch *touch = obj;
        CGPoint touchPoint = [touch locationInView:self.view];
		
        ios_bridge_touch_moved(touchPoint.x, touchPoint.y, i++);
		
    }];
}

- (NSInteger)animationFrameInterval
{
    return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
    /*
	 Frame interval defines how many display frames must pass between each time the display link fires.
	 The display link will only fire 30 times a second when the frame internal is two on a display that refreshes 60 times a second. The default frame interval setting of one will fire 60 times a second when the display refreshes at 60 times a second. A frame interval setting of less than one results in undefined behavior.
	 */
    if (frameInterval >= 1) {
        animationFrameInterval = frameInterval;
		
        if (animating) {
            [self stopAnimation];
            [self startAnimation];
        }
    }
}

- (void)startAnimation
{
    if (!animating) {
        CADisplayLink *aDisplayLink = [[UIScreen mainScreen] displayLinkWithTarget:self selector:@selector(drawFrame)];
        [aDisplayLink setFrameInterval:animationFrameInterval];
        [aDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        self.displayLink = aDisplayLink;
		
        animating = TRUE;
    }
}

- (void)stopAnimation
{
    if (animating) {
        [self.displayLink invalidate];
        self.displayLink = nil;
        animating = FALSE;
    }
}

- (void)drawFrame
{
    [(EAGLView *)self.view setFramebuffer];
	
	ios_bridge_update();
	
    [(EAGLView *)self.view presentFramebuffer];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation{
    return ios_bridge_should_autorotate();
}

@end
