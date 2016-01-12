//
//  AGSChatCell.m
//  AgoraDemo
//
//  Created by Shilong on 9/10/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import "AGSChatCell.h"

@interface AGSChatCell ()
@property (weak, nonatomic) UIView *audioView;
@property (weak, nonatomic) UIButton *audioMicButton;
@property (weak, nonatomic) UIButton *videoMicButton;
@property (weak, nonatomic) UIImageView *qualityImageView;

@property (assign, nonatomic) BOOL audioMute;
@end

@implementation AGSChatCell

- (id)init
{
    self = [super init];
    if (self) {
        _videoView = [[UIView alloc] init];
        _videoView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        _nameLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 64, 16)];
        _nameLabel.autoresizingMask = UIViewAutoresizingFlexibleWidth;
        [self addSubview:_videoView];
        [self addSubview:_nameLabel];
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
        self.audioView.hidden = NO;
    } else if (type == AGSChatTypeVideo) {
        self.videoView.hidden = NO;
        self.audioView.hidden = YES;
    } else {
        NSLog(@"error: control type not correct");
    }
}

- (void)setAudioMute:(BOOL)audioMute
{
    _audioMute = audioMute;
    
    //
    self.audioMicButton.selected = audioMute;
    self.videoMicButton.selected = audioMute;
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

- (IBAction)didClickAudioMute:(UIButton *)btn
{
    self.audioMute = !self.audioMute;
    if ([self.delegate respondsToSelector:@selector(cell:didMuteAudio:)]) {
        [self.delegate cell:self didMuteAudio:self.audioMute];
    }
}

@end
