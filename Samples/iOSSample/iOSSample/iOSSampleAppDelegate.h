//
//  iOSSampleAppDelegate.h
//  iOSSample
//
//  Created by Artur on 7/26/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class iOSSampleViewController;

@interface iOSSampleAppDelegate : NSObject <UIApplicationDelegate>

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet iOSSampleViewController *viewController;

@end
