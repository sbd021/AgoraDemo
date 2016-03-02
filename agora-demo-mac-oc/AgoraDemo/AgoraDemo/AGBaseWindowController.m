//
//  AGBaseWindowController.m
//  AgoraMacFullset
//
//  Created by Jesse on 12/01/16.
//  Copyright © 2016 Agora. All rights reserved.
//

#import "AGBaseWindowController.h"

@interface AGBaseWindowController ()<NSWindowDelegate>

@end

@implementation AGBaseWindowController

- (void)windowDidLoad {
    [super windowDidLoad];
    
    self.window.styleMask |= NSFullSizeContentViewWindowMask;
    self.window.titlebarAppearsTransparent = YES;
    self.window.movableByWindowBackground = YES;
    self.window.delegate = self;
    [self adjustTrafficLights];
}

- (void)adjustTrafficLights {
    for (NSView *view in self.window.contentView.superview.subviews) {
        if ([NSStringFromClass(view.class) isEqualToString:@"NSTitlebarContainerView"] &&
            NSHeight(view.frame) == 22) {
            NSRect frame = view.frame;
            frame.origin.y -= 8;
            frame.size.height = 38;
            view.frame = frame;
        }
    }
}


#pragma mark - NSWindowDelegate

- (void)windowDidResize:(NSNotification *)notification {
    [self adjustTrafficLights];
}


@end
