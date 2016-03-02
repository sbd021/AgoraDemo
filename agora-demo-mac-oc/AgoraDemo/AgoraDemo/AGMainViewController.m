//
//  MainViewController.m
//  AgoraMacFullset
//
//  Created by Jesse on 16/01/16.
//  Copyright © 2016 Agora. All rights reserved.
//

#import "AGMainViewController.h"
#import "AGChatViewController.h"
#import "NSColor+Hex.h"

@interface AGMainViewController ()

@property (weak) IBOutlet NSView *titleBarBackgroundView;
@property (weak) IBOutlet NSView *containerView;
@property (weak) IBOutlet NSView *containerBackgroundView;

@property (strong, nonatomic) AGChatViewController *chatViewController;

@end

@implementation AGMainViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.titleBarBackgroundView.wantsLayer = YES;
    self.titleBarBackgroundView.layer.backgroundColor = [NSColor colorWithHex:0x1677CB].CGColor;
    
    self.containerBackgroundView.wantsLayer = YES;
    self.containerBackgroundView.layer.contents = [NSImage imageNamed:@"main_background"];
    self.containerBackgroundView.layer.contentsGravity = kCAGravityResizeAspectFill;
    
    self.chatViewController = [self.storyboard instantiateControllerWithIdentifier:@"ChatViewController"];
    [self addChildViewController:self.chatViewController];
    [self.containerView addSubview:self.chatViewController.view];
    self.chatViewController.view.translatesAutoresizingMaskIntoConstraints = NO;
    
    NSArray *v = [NSLayoutConstraint constraintsWithVisualFormat:@"V:|-0-[chatView]-0-|"
                                                         options:0
                                                         metrics:nil
                                                           views:@{@"chatView": self.chatViewController.view}];
    [self.containerView addConstraints:v];
    NSArray *h = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|-0-[chatView]-0-|"
                                                         options:0
                                                         metrics:nil
                                                           views:@{@"chatView": self.chatViewController.view}];
    [self.containerView addConstraints:h];
}

@end
