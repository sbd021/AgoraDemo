//
//  AGSVoiceTestViewController.m
//  AgoraSample
//
//  Created by Shilong on 9/7/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import "AGSVoiceTestViewController.h"
#import <AgoraRtcEngineKit/AgoraRtcEngineKit.h>
#import <AVFoundation/AVFoundation.h>

@interface AGSVoiceTestViewController ()

@property (weak, nonatomic) IBOutlet UILabel *alertTitleLabel;
@property (weak, nonatomic) IBOutlet UILabel *alertSubtitleLabel;
@property (weak, nonatomic) IBOutlet UILabel *alertStatusLabel;
@property (weak, nonatomic) IBOutlet UIButton *alertTestButton;

@property (strong, nonatomic) AgoraRtcEngineKit *agoraKit;

@property (assign, nonatomic) int recordingCount;
@property (assign, nonatomic) int playbackCount;
@end

@implementation AGSVoiceTestViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    self.agoraKit = [AgoraRtcEngineKit sharedEngineWithVendorKey:@"6D7A26A1D3554A54A9F43BE6797FE3E2" error:^(AgoraRtcErrorCode errorCode) {
        if (errorCode != AgoraRtc_Error_NoError) {
            NSLog(@"kit initial error: %ld. please check the detail", errorCode);
        } else {
            [self.agoraKit enableAudioVolumeIndication:1000 smooth:0];
            [self.agoraKit setEnableSpeakerphone:YES];
            [self.agoraKit audioVolumeIndicationBlock:^(NSArray *speakers, NSInteger totalVolume) {
                AgoraRtcAudioVolumeInfo *s = speakers.lastObject;
                NSLog(@"uid: %ld, volume: %ld", s.uid, s.volume);
                
            }];
        }
    }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/
- (IBAction)didClickAlertCancelButton:(id)sender {
    [self.agoraKit stopEchoTest];
}

- (IBAction)didClickAlertTestButton:(id)sender {
    // 点击后需要持续至少20秒，20秒内不能重复操作
    
    // alert状态改变 开始测试
    self.alertSubtitleLabel.text = @"请稍后...";
    self.alertTestButton.enabled = NO;
    
    
    [self.agoraKit startEchoTest:^(NSString *channel, NSUInteger uid, NSInteger elapsed) {
        NSLog(@"channel: %@, uid: %ld, elapsed: %ld", channel, uid, elapsed);
        // 语音测试开始
        // 倒计时10秒，10秒后静音本地，
        self.recordingCount = 10;
        self.alertSubtitleLabel.text = [NSString stringWithFormat:@"请开始说话 %d", self.recordingCount--];
        [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(countDownRecording:) userInfo:nil repeats:YES];
        
        
    }];
}

- (void)countDownRecording:(NSTimer *)timer
{
    
    if (self.recordingCount < 0) {
        [timer invalidate];
        timer = nil;
        //// 继续倒计时10秒，10秒后关闭测试stopEchoTest
        
        [self.agoraKit muteLocalAudioStream:YES];
        self.playbackCount = 10;
        self.playbackCount--;
        self.alertSubtitleLabel.text = [NSString stringWithFormat:@"回放中"];
        [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(countDownPlayback:) userInfo:nil repeats:YES];
        
    } else {
        self.alertSubtitleLabel.text = [NSString stringWithFormat:@"请开始说话 %d", self.recordingCount--];
    }
    
}

- (void)countDownPlayback:(NSTimer *)timer
{
    if (self.playbackCount < 0) {
       
        [timer invalidate];
        timer = nil;
        
        [self.agoraKit stopEchoTest];
        
        self.alertSubtitleLabel.text = @"成功";
        [self.alertTestButton setTitle:@"重新测试" forState:UIControlStateNormal];
        self.alertTestButton.enabled = YES;
        
    } else {
        self.playbackCount--;
        self.alertSubtitleLabel.text = [NSString stringWithFormat:@"回放中"];
    }
}
@end
