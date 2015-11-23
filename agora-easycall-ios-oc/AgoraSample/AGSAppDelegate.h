//
//  AppDelegate.h
//  AgoraSample
//
//  Created by Shilong on 9/7/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AGSAgoraKitManager.h"

@interface AGSAppDelegate : UIResponder <UIApplicationDelegate, UINavigationControllerDelegate, AGSAgoraKitManagerDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) UINavigationController *navigationController;
@end

