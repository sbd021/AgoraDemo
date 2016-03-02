//
//  AGHostingView.m
//  AgoraMacFullset
//
//  Created by Jesse on 17/01/16.
//  Copyright © 2016 Agora. All rights reserved.
//

#import "AGHostingView.h"
#import "NSColor+Hex.h"

@implementation AGHostingView

- (instancetype)initWithFrame:(NSRect)frameRect {
    self = [super initWithFrame:frameRect];
    if (self) {
        self.wantsLayer = YES;
        self.layer.backgroundColor = [NSColor colorWithHex:0x3A3F4D].CGColor;
        
        self.avatarImageView = [[NSImageView alloc] initWithFrame:NSMakeRect(35, 0, 30, 32)];
        self.avatarImageView.image = [NSImage imageNamed:@"avatar"];
        self.avatarImageView.translatesAutoresizingMaskIntoConstraints = NO;
        [self addSubview:self.avatarImageView];
        [self addConstraint:[NSLayoutConstraint constraintWithItem:self.avatarImageView
                                                         attribute:NSLayoutAttributeCenterX
                                                         relatedBy:NSLayoutRelationEqual
                                                            toItem:self
                                                         attribute:NSLayoutAttributeCenterX
                                                        multiplier:1.0f
                                                          constant:0.0f]];
        [self addConstraint:[NSLayoutConstraint constraintWithItem:self.avatarImageView
                                                         attribute:NSLayoutAttributeCenterY
                                                         relatedBy:NSLayoutRelationEqual
                                                            toItem:self
                                                         attribute:NSLayoutAttributeCenterY
                                                        multiplier:1.0f
                                                          constant:-10.0f]];
        
        
        self.nameLabel = [[NSTextField alloc] initWithFrame:NSZeroRect];
        self.nameLabel.editable = NO;
        self.nameLabel.selectable = NO;
        self.nameLabel.drawsBackground = NO;
        self.nameLabel.bordered = NO;
        self.nameLabel.textColor = [NSColor colorWithHex:0xA8A8A8];
        self.nameLabel.font = [NSFont fontWithName:@"STHeitiSC-Light" size:14];
        self.nameLabel.translatesAutoresizingMaskIntoConstraints = NO;
        [self addSubview:self.nameLabel];
        [self addConstraint:[NSLayoutConstraint constraintWithItem:self.nameLabel
                                                         attribute:NSLayoutAttributeCenterX
                                                         relatedBy:NSLayoutRelationEqual
                                                            toItem:self
                                                         attribute:NSLayoutAttributeCenterX
                                                        multiplier:1.0f
                                                          constant:0.0f]];
        [self addConstraint:[NSLayoutConstraint constraintWithItem:self.nameLabel
                                                         attribute:NSLayoutAttributeCenterY
                                                         relatedBy:NSLayoutRelationEqual
                                                            toItem:self
                                                         attribute:NSLayoutAttributeCenterY
                                                        multiplier:1.0f
                                                          constant:25.0f]];
        
        self.videoView = [[NSView alloc] initWithFrame:frameRect];
        self.videoView.translatesAutoresizingMaskIntoConstraints = NO;
        [self addSubview:self.videoView];
        [self addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|-0-[video]-0-|"
                                                                     options:0
                                                                     metrics:nil
                                                                       views:@{@"video": self.videoView}]];
        [self addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|-0-[video]-0-|"
                                                                     options:0
                                                                     metrics:nil
                                                                       views:@{@"video": self.videoView}]];

    }
    return self;
}

- (void)setIsLocalVideo:(BOOL)isLocalVideo {
    _isLocalVideo = isLocalVideo;
    if (isLocalVideo) {
        self.avatarImageView.hidden = YES;
        self.nameLabel.hidden = YES;
        self.layer.backgroundColor = [NSColor clearColor].CGColor;
    }
}

@end
