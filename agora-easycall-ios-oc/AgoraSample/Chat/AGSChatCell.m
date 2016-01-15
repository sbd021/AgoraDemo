//
//  AGSChatCell.m
//  AgoraDemo
//
//  Created by Shilong on 9/10/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import "AGSChatCell.h"

@interface AGSChatCell ()

@property (nonatomic) UILabel *nameLabel;
@property (nonatomic) UIButton *audioMicButton;
@property (nonatomic) UIImageView *qualityImageView;

@property (assign, nonatomic) BOOL audioMute;
@end

@implementation AGSChatCell

- (id)init
{
    self = [super init];
    if (self) {
        _videoView = [[UIView alloc] init];
        _videoView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        [self addSubview:_videoView];

        _nameLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 64, 16)];
        _nameLabel.textColor = [UIColor colorWithRed:0.7 green:0.2 blue:0.2 alpha:1.0];
        _nameLabel.font = [UIFont systemFontOfSize:12];
        [self addSubview:_nameLabel];
        
        _qualityImageView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 16, 16)];
        [self addSubview:_qualityImageView];
        
        _audioMicButton = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 24, 24)];
        [_audioMicButton setBackgroundImage:[UIImage imageNamed:@"ic_room_cell_microphone"] forState:UIControlStateNormal];
        [_audioMicButton setBackgroundImage:[UIImage imageNamed:@"ic_room_mute_pressed"] forState:UIControlStateSelected];
        [_audioMicButton addTarget:self action:@selector(didClickAudioMute:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:_audioMicButton];

        _type = AGSChatTypeVideo;
        _audioMute = NO;
    }
    return self;
}


- (void)setType:(AGSChatType)type
{
    _type = type;
    
    if (type == AGSChatTypeAudio) {
        self.videoView.hidden = YES;
    } else if (type == AGSChatTypeVideo) {
        self.videoView.hidden = NO;
    } else {
        NSLog(@"error: control type not correct");
    }
}

- (void)setAudioMute:(BOOL)audioMute
{
    _audioMute = audioMute;
    
    //
    self.audioMicButton.selected = audioMute;
}

- (void)setNetworkQulity:(AgoraRtcQuality)networkQulity
{
    _networkQulity = networkQulity;
    
    NSString *imageName = @"";
    switch (networkQulity) {
        case AgoraRtc_Quality_Down:
            imageName = @"ic_room_signal_none";
            break;
        case AgoraRtc_Quality_Bad:
        case AgoraRtc_Quality_VBad:
            imageName = @"ic_room_signal_one";
            break;
        case AgoraRtc_Quality_Poor:
        case AgoraRtc_Quality_Good:
            imageName = @"ic_room_signal_two";
            break;
        case AgoraRtc_Quality_Excellent:
            imageName = @"ic_room_signal_three";
            break;
        default:
            imageName = @"ic_room_signal_none";
            break;
    }
    
    self.qualityImageView.image = [UIImage imageNamed:imageName];
}

- (void) didClickAudioMute:(UIButton *)btn
{
    self.audioMute = !self.audioMute;
    if ([self.delegate respondsToSelector:@selector(cell:didMuteAudio:)]) {
        [self.delegate cell:self didMuteAudio:self.audioMute];
    }
}

- (void) reLayout
{
    CGRect rcBounds = self.bounds;
    self.videoView.frame = rcBounds;

    CGRect rc = rcBounds;
    rc.size.height = 16;
    self.nameLabel.frame = rc;

    rc.origin.y += rc.size.height;
    rc.size.width = 32;
    rc.size.height = 32;
    rc.origin.x = rcBounds.size.width - rc.size.width;
    self.audioMicButton.frame = rc;
    
    rc.origin.x = 0;
    rc.size.width = 16;
    rc.size.height = 16;
    rc.origin.y = rcBounds.size.height - rc.size.height;
    self.qualityImageView.frame = rc;
}

- (void)setTitle:(NSString *)title
{
    self.nameLabel.text = title;
}

@end
