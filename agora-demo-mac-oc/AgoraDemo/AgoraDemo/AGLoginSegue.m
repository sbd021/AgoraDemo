//
//  LoginSegue.m
//  AgoraMacFullset
//
//  Created by Jesse on 15/01/16.
//  Copyright © 2016 Agora. All rights reserved.
//

#import "AGLoginSegue.h"

@implementation AGLoginSegue

- (void)perform {
    [[self.sourceController view] window].contentViewController = self.destinationController;
}

@end
