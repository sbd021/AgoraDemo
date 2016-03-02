//
//  AGHostingView.h
//  AgoraMacFullset
//
//  Created by Jesse on 17/01/16.
//  Copyright © 2016 Agora. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AGHostingView : NSView

@property (strong, nonatomic) NSImageView *avatarImageView;
@property (strong, nonatomic) NSTextField *nameLabel;
@property (strong, nonatomic) NSView *videoView;
@property (nonatomic) BOOL isLocalVideo;

@end
