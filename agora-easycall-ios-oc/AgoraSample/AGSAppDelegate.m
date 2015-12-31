//
//  AppDelegate.m
//  AgoraSample
//
//  Created by Shilong on 9/7/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import "AGSAppDelegate.h"
#import "AGSVoiceTestViewController.h"
#import "AGSCoreDataManager.h"
#import "AGSChatViewController.h"
#import "AGSCallBackView.h"
#import "Crasheye.h"

@interface AGSAppDelegate ()

@end

@implementation AGSAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    [Crasheye initWithAppKey:@"faf12510"];
    
    //
    [AGSAgoraKitManager shareManager].delegate = self;
    
    return YES;
}

- (void)navigationController:(UINavigationController *)navigationController willShowViewController:(UIViewController *)viewController animated:(BOOL)animated
{
    if ([viewController isKindOfClass:[AGSChatViewController class]]) {
        [[AGSAgoraKitManager shareManager].callBackView hideCallBackView];
    }
}

- (void)didBackChatViewAndHideCallBackView:(AGSCallBackView *)view
{
    for (UIViewController *viewControllView in self.navigationController.viewControllers) {
        if ([viewControllView isKindOfClass:[AGSChatViewController class]]) {
            [self.navigationController popToViewController:viewControllView animated:YES];
        }
    }
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
