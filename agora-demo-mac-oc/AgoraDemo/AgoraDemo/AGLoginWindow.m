//
//  NSLoginWindow.m
//  AgoraMacFullset
//
//  Created by Jesse on 22/01/16.
//  Copyright © 2016 Agora. All rights reserved.
//

#import "AGLoginWindow.h"
#import "AppDelegate.h"

static AGLoginWindow *_loginWindow;

@implementation AGLoginWindow

+ (void)setLoginWindow:(AGLoginWindow *)window {
    _loginWindow = window;
}

+ (AGLoginWindow *)window {
    return _loginWindow;
}

- (void)awakeFromNib {
    [super awakeFromNib];
    [AGLoginWindow setLoginWindow:self];
}

- (void)setFrame:(NSRect)frameRect display:(BOOL)flag {
    if (frameRect.size.height > 556) {
        frameRect.size.width = 305;
        frameRect.size.height = 534;
    }
    [super setFrame:frameRect display:flag];
}

@end
