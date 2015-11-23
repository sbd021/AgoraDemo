//
//  AGSChatCell.m
//  AgoraDemo
//
//  Created by Shilong on 9/10/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import "AGSChatCell.h"

@interface AGSChatCell ()
@property (weak, nonatomic) IBOutlet UIView *audioView;
@property (weak, nonatomic) IBOutlet UIButton *audioMicButton;
@property (weak, nonatomic) IBOutlet UIButton *videoMicButton;
@property (weak, nonatomic) IBOutlet UIImageView *qualityImageView;

@property (assign, nonatomic) BOOL audioMute;
@end

@implementation AGSChatCell

- (void)setType:(AGSChatType)type
{
    _type = type;
    
    if (type == AGSChatTypeAudio) {
        self.videoView.hidden = YES;
        self.audioView.hidden = NO;
        self.uid = 0;
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

- (void)setUid:(NSUInteger)uid
{
    _uid = uid;
    if (!self.canvas) {
        _canvas = [[AgoraRtcVideoCanvas alloc] init];
        _canvas.renderMode = AgoraRtc_Render_Hidden;
        _canvas.view = self.videoView;
    }
    self.canvas.uid = uid;
}

- (IBAction)didClickAudioMute:(UIButton *)btn
{
    self.audioMute = !self.audioMute;
    if ([self.delegate respondsToSelector:@selector(cell:didMuteAudio:)]) {
        [self.delegate cell:self didMuteAudio:self.audioMute];
    }
}

@end
