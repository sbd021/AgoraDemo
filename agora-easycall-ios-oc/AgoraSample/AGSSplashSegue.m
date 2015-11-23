//
//  AGSSplashSegue.m
//  AgoraSample
//
//  Created by let on 10/21/15.
//  Copyright © 2015 Agora. All rights reserved.
//

#import "AGSSplashSegue.h"

@implementation AGSSplashSegue

- (void)perform
{
    [[[UIApplication sharedApplication] keyWindow] setRootViewController:self.destinationViewController];
}

@end
