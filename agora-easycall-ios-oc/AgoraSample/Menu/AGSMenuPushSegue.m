//
//  AGSMenuPushSegue.m
//  AgoraSample
//
//  Created by Shilong on 9/17/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import "AGSMenuPushSegue.h"
#import "AGSFrostedViewController.h"
#import "AGSMenuViewController.h"
#import "AGSChatViewController.h"
#import "AGSAgoraKitManager.h"

@implementation AGSMenuPushSegue

- (void)perform
{
    UIViewController *menuViewController = (AGSMenuViewController *)self.sourceViewController;
    UIViewController *nextViewController = (UIViewController *)self.destinationViewController;
    UINavigationController *currentNavigationController = (UINavigationController *)menuViewController.frostedViewController.contentViewController;    
    
    [menuViewController.frostedViewController hideMenuViewControllerWithCompletionHandler:^{
        
        if ([currentNavigationController.topViewController isKindOfClass:[AGSChatViewController class]]) {
            AGSChatViewController *chatViewController = (AGSChatViewController *)currentNavigationController.topViewController;
            [AGSAgoraKitManager shareManager].callBackView.durationTime = chatViewController.duration;
            [[AGSAgoraKitManager shareManager].callBackView showCallBackView];
        }
        
        [currentNavigationController pushViewController:nextViewController animated:YES];
    }];
}

@end
