//
//  ViewController.m
//  sample
//
//  Created by kele on 14-6-8.
//  Copyright (c) 2014年 kele. All rights reserved.
//

#import "ViewController.h"
#include <AgoraAudioKit/AgoraRtcEngineKit.h>

@interface ViewController () <UITextFieldDelegate>
@property (weak, nonatomic) IBOutlet UITextField *nameTextField;
@property (weak, nonatomic) IBOutlet UITextField *vendorKeyTextField;

@property (weak, nonatomic) IBOutlet UIButton *joinButton;
@property (weak, nonatomic) IBOutlet UIButton *leaveButton;
@property (weak, nonatomic) IBOutlet UIButton *muteSwitchButton;
@property (weak, nonatomic) IBOutlet UIButton *speakerSwitchButton;
@property (weak, nonatomic) IBOutlet UITextView *logMessageTextView;

@property (strong, nonatomic) NSMutableString *logString;

@property (strong ,nonatomic) AgoraRtcEngineKit *agoraRtcEngine;

@property (assign, nonatomic) BOOL hasJoinedChannel;
@property (assign, nonatomic) BOOL hasMuted;
@property (assign, nonatomic) BOOL enabledSpeaker;
@end

static NSString * const KeyVendorKey = @"VendorKey";


@implementation ViewController
- (NSMutableString *)logString
{
    if (!_logString) {
        _logString = [[NSMutableString alloc] init];
    }
    return _logString;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSString *vendorKey = [userDefaults objectForKey:KeyVendorKey];
    if (vendorKey) {
        self.vendorKeyTextField.text = vendorKey;
    } else {
        NSURL *innerKeyUrl = [NSURL URLWithString:@"http://192.168.99.253:8970/agora.inner.test.key.txt"];
        NSString *innerVendorKey = [NSString stringWithContentsOfURL:innerKeyUrl
                                                            encoding:NSASCIIStringEncoding
                                                               error:nil];
        
        self.vendorKeyTextField.text = [innerVendorKey
                                  stringByReplacingOccurrencesOfString:@"\n" withString:@""];; // Please use your own key. The inner test key is just invalid in public.
    }
    
    
    __weak typeof(self) weakSelf = self;
    self.agoraRtcEngine = [[AgoraRtcEngineKit alloc] initWithVendorKey:self.vendorKeyTextField.text error:^(AgoraRtcErrorCode errorCode) {
        __strong typeof(weakSelf) strongSelf = weakSelf;
        [strongSelf appendLogString:[NSString stringWithFormat:@"error code: %lu", (long)errorCode]];
    }];
    
    NSURL *docURL = [[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask] lastObject];
    NSString *logDir = [docURL path];
//    NSString *logDir = NSSearchPathForDirectoriesInDomains(NSCachesDirectory,NSUserDomainMask, YES).firstObject;
    
    NSString *logTextPath = [logDir stringByAppendingPathComponent:@"com.agora.CacheLogs/agorasdk.log"];
    [self.agoraRtcEngine setLogFile:logTextPath];
    
    [self.agoraRtcEngine audioQualityBlock:^(NSUInteger uid, AgoraRtcQuality quality, NSUInteger delay, NSUInteger lost) {
        __strong typeof(weakSelf) strongSelf = weakSelf;
        [strongSelf appendLogString:[NSString stringWithFormat:@"user %u delay %u lost %u", (unsigned int)uid, (unsigned int)delay, (unsigned int)lost]];
    }];
    
    [self.agoraRtcEngine leaveChannelBlock:^(AgoraRtcStats *stat) {
        //NSLog(@"duration %d tx %d rx %d", stat.duration, stat.txBytes, stat.rxBytes);
    }];
    
    [self.agoraRtcEngine rtcStatsBlock:^(AgoraRtcStats *stat) {
        //NSLog(@"duration %d tx %d rx %d", stat.duration, stat.txBytes, stat.rxBytes);
    }];
    
    [self.agoraRtcEngine networkQualityBlock:^(AgoraRtcQuality quality) {
        __strong typeof(weakSelf) strongSelf = weakSelf;
        [strongSelf appendLogString:[NSString stringWithFormat:@"network quality: %d", (int)quality]];
    }];
    
    [self.agoraRtcEngine enableNetworkTest];
}

- (void)setHasJoinedChannel:(BOOL)hasJoinedChannel
{
    _hasJoinedChannel = hasJoinedChannel;
    
    self.joinButton.hidden = hasJoinedChannel;
    self.leaveButton.hidden = ! hasJoinedChannel;
    self.muteSwitchButton.hidden = ! hasJoinedChannel;
    self.speakerSwitchButton.hidden = ! hasJoinedChannel;
    
    [[UIDevice currentDevice] setProximityMonitoringEnabled:hasJoinedChannel];
}

- (void)appendLogString:(NSString *)logString
{
    [self.logString appendFormat:@"%@\n", logString];
    
    self.logMessageTextView.text = self.logString;
    [self.logMessageTextView scrollRangeToVisible:NSMakeRange(self.logString.length, 0)];
}

- (void)clearLogTextView
{
    self.logMessageTextView.text = nil;
    self.logString = nil;
}

- (void)joinChannel:(NSString *)channelName
{
    if (! channelName.length) {
        [self appendLogString:@"no channel name!"];
        return;
    }
    
    if(self.hasJoinedChannel) {
        [self appendLogString:@"join channel already,  leave first!"];
        return;
    }
    
    [self clearLogTextView];
    self.joinButton.enabled = NO;
    self.joinButton.alpha = 0.1f;
    [self appendLogString:@"join Channel begin"];
    
    __weak typeof(self) weakSelf = self;
    
    [self.agoraRtcEngine userJoinedBlock:^(NSUInteger uid, NSInteger elapsed) {
        __strong typeof(weakSelf) strongSelf = weakSelf;
        [strongSelf appendLogString:[NSString stringWithFormat:@"user %u joined in %d ms", (uint32_t)uid, (int)elapsed]];
    }];
    
    [self.agoraRtcEngine userOfflineBlock:^(NSUInteger uid) {
        __strong typeof(weakSelf) strongSelf = weakSelf;
        [strongSelf appendLogString:[NSString stringWithFormat:@"user %u offline", (uint32_t)uid]];
    }];

    [self.agoraRtcEngine userMuteAudioBlock:^(NSUInteger uid, BOOL muted) {
        __strong typeof(weakSelf) strongSelf = weakSelf;
        [strongSelf appendLogString:[NSString stringWithFormat:@"user %u audio %@", (uint32_t)uid, muted ? @"muted" : @"unmuted"]];
    }];

    [self.agoraRtcEngine userMuteVideoBlock:^(NSUInteger uid, BOOL muted) {
        __strong typeof(weakSelf) strongSelf = weakSelf;
        [strongSelf appendLogString:[NSString stringWithFormat:@"user %u video %@", (uint32_t)uid, muted ? @"muted" : @"unmuted"]];
    }];

    [self.agoraRtcEngine joinChannelByKey:nil channelName:channelName info:nil uid:0 joinSuccess:^(NSString* channel, NSUInteger uid, NSInteger elapsed){
        weakSelf.hasJoinedChannel = YES;
        weakSelf.joinButton.enabled = YES;
        weakSelf.joinButton.alpha = 1.0f;
        __strong typeof(weakSelf) strongSelf = weakSelf;
        [strongSelf appendLogString:[NSString stringWithFormat:@"joined channel: %@ uid %u elapsed %d ms", channel, (unsigned int)uid, (int)elapsed]];
        
        
        NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
        [userDefaults setObject:self.vendorKeyTextField.text forKey:KeyVendorKey];
    }];
}

- (IBAction)joinPressed:(id)sender
{
    [self joinChannel:self.nameTextField.text];
}

- (IBAction)leavePressed:(id)sender
{
    if(! self.hasJoinedChannel) {
        [self appendLogString:@"not in channel!"];
        return;
    }
    
    [self.agoraRtcEngine leaveChannel:nil];
    self.hasJoinedChannel = NO;
    
    [self clearLogTextView];
}

- (IBAction)mutePressed:(UIButton *)sender
{
    if(! self.hasJoinedChannel) {
        [self appendLogString:@"not in channel!"];
        return;
    }
    
    [self.agoraRtcEngine muteLocalAudioStream:!self.hasMuted];
    self.hasMuted = !self.hasMuted;
    
    [self.muteSwitchButton setTitle:(self.hasMuted ? @"unMute" : @"mute") forState:UIControlStateNormal];
}

- (IBAction)speakerPressed:(UIButton *)sender
{
    if(! self.hasJoinedChannel) {
        [self appendLogString:@"not in channel!"];
        return;
    }
    
    [self.agoraRtcEngine setEnableSpeakerphone:!self.enabledSpeaker];
    self.enabledSpeaker = !self.enabledSpeaker;
    
    [self.speakerSwitchButton setTitle:(self.enabledSpeaker ? @"disable speaker" : @"enable speaker") forState:UIControlStateNormal];
}

#pragma mark - textField delegate
- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField
{
    return (! self.hasJoinedChannel);
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    [self joinChannel:textField.text];
    
    return YES;
}
@end
