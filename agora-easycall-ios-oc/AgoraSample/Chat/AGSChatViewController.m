//
//  AGSChatViewController.m
//  AgoraDemo
//
//  Created by apple on 15/9/9.
//  Copyright (c) 2015年 Agora. All rights reserved.
//

#import "AGSChatViewController.h"
#import <AgoraMediaKit/AgoraRTCEngineKit.h>
#import "AGSCoreDataManager.h"
#import "AGSProfileViewController.h"

@interface AGSChatViewController ()
{
    __block AgoraRtcSessionStat *lastStat_;
    BOOL isErrorKey_;
    NSUInteger fullscreenUid_;
    AgoraRtcVideoCanvas *localVideoCanvas_;
}

@property (weak,nonatomic) IBOutlet UILabel *controlTitleMuteLabel;
@property (weak,nonatomic) IBOutlet UILabel *controlTitleMuteAudioLabel;
@property (weak,nonatomic) IBOutlet UILabel *controlTitleSpeakerLabel;
@property (weak,nonatomic) IBOutlet UILabel *controlTitleSpeakerAudioLabel;
@property (weak,nonatomic) IBOutlet UILabel *controlTitleSwitchLabel;
@property (weak,nonatomic) IBOutlet UILabel *controlTitleCloseLabel;

@property (weak, nonatomic) IBOutlet UIView *audioControlView;
@property (weak, nonatomic) IBOutlet UIView *videoControlView;
@property (strong, nonatomic) IBOutletCollection(UIButton) NSArray *speakerControlButtons;
@property (strong, nonatomic) IBOutletCollection(UIButton) NSArray *audioMuteControlButtons;
@property (weak, nonatomic) IBOutlet UIButton *cameraControlButton;

@property (weak, nonatomic) IBOutlet UIView *videoMainView;

@property (weak, nonatomic) IBOutlet UICollectionView *collectionView;

@property (weak, nonatomic) IBOutlet UIView *statContrainerView;
@property (weak, nonatomic) IBOutlet UILabel *talkTimeLabel;
@property (weak, nonatomic) IBOutlet UILabel *dataTrafficLabel;
@property (weak, nonatomic) IBOutlet UILabel *alertLabel;
@property (weak, nonatomic) IBOutlet UIImageView *networkImageView;

@property (weak, nonatomic) IBOutlet UIButton *videoButton;
@property (weak, nonatomic) IBOutlet UIButton *audioButton;

@property (strong, nonatomic) AgoraRtcEngineKit *agoraKit;

@property (strong, nonatomic) NSMutableArray *uids;
@property (strong, nonatomic) NSMutableDictionary *videoMuteForUids;

//
@property (assign, nonatomic) AGSChatType type;
@property (strong, nonatomic) NSString *channel;
@property (strong, nonatomic) NSString *key;
@property (assign, nonatomic) BOOL agoraVideoEnabled;
@property (strong, nonatomic) NSTimer *durationTimer;

// Agora
@property (strong, nonatomic) NSString *callId;
@property (nonatomic) NSInteger rating;
@property (nonatomic) NSDate *startDate;
@property (nonatomic) NSUInteger myUid;
@property (nonatomic) NSUInteger firstJoinedUid;

// Activity
@property (strong, nonatomic) NSMutableArray *activityStrings;
@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (weak, nonatomic) IBOutlet UIView *activityContrainerView;

@property (strong, nonatomic) UIAlertView *errorKeyAlert;

@end

@implementation AGSChatViewController

#pragma mark - View

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //
    self.uids = [NSMutableArray array];
    self.videoMuteForUids = [NSMutableDictionary dictionary];
    self.activityStrings = [NSMutableArray array];
    
    self.key = [[NSUserDefaults standardUserDefaults] stringForKey:AGSKeyVendorKey];
    self.channel = [self.dictionary objectForKey:AGSKeyChannel];
    self.type = self.chatType;
    
    
    [self prepareAgoraKit];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    NSString *key = [[NSUserDefaults standardUserDefaults] stringForKey:AGSKeyVendorKey];
    if (isErrorKey_ || ![self.key isEqualToString:key]) {
        self.key = key;
        [self clearData];
        [self prepareAgoraKit];
    }
    
    //
    self.title = [NSString stringWithFormat:@"%@ %@",NSLocalizedString(@"Room", @""), self.channel];
    
    self.controlTitleCloseLabel.text = NSLocalizedString(@"Camera Off", @"");
    self.controlTitleMuteAudioLabel.text = NSLocalizedString(@"Mute", @"");
    self.controlTitleMuteLabel.text = NSLocalizedString(@"Mute", @"");
    self.controlTitleSpeakerAudioLabel.text = NSLocalizedString(@"Speaker", @"");
    self.controlTitleSpeakerLabel.text = NSLocalizedString(@"Speaker", @"");
    self.controlTitleSwitchLabel.text = NSLocalizedString(@"Switch Camera", @"");
    
    [self.videoButton setTitle:NSLocalizedString(@"Video Call", @"") forState:UIControlStateNormal];
    [self.audioButton setTitle:NSLocalizedString(@"Voice Call", @"") forState:UIControlStateNormal];
    
    self.talkTimeLabel.text = NSLocalizedString(@"Total Time", @"");
    self.dataTrafficLabel.text = NSLocalizedString(@"Total Trafic", @"");
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Delegate

// Table view
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.activityStrings.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    AGSChatActivityCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ChatActivityCell" forIndexPath:indexPath];
    cell.titleLabel.text = [self.activityStrings objectAtIndex:indexPath.row];
    if (indexPath.row == [tableView numberOfRowsInSection:0]-1) {
        cell.titleLabel.textColor = [UIColor whiteColor];
    } else {
        cell.titleLabel.textColor = [UIColor colorWithWhite:1 alpha:.6];
    }
    return cell;
}

// Collection view
- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section
{
    return self.uids.count;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    
    AGSChatCell *cell = [self.collectionView dequeueReusableCellWithReuseIdentifier:@"CollectionViewCell" forIndexPath:indexPath];
    cell.delegate = self;
    
    // Get info
    NSNumber *uid = [self.uids objectAtIndex:indexPath.row];
    NSNumber *videoMute = [self.videoMuteForUids objectForKey:uid];
    
    if (self.type == AGSChatTypeVideo) {
        if (videoMute.boolValue) {
            cell.type = AGSChatTypeAudio;
        } else {
            cell.type = AGSChatTypeVideo;
            cell.uid = uid.unsignedIntegerValue;
            [self.agoraKit setupRemoteVideo:cell.canvas];
        }
    } else {
        cell.type = AGSChatTypeAudio;
    }
    
    // Name
    cell.nameLabel.text = uid.stringValue;
    
    return cell;
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath
{
    AGSChatCell *cell = (AGSChatCell *)[collectionView cellForItemAtIndexPath:indexPath];
    [self.agoraKit switchView:fullscreenUid_ andAnother:cell.uid];
    
    // Switch two Uid
    NSUInteger temp = cell.uid;
    cell.uid = fullscreenUid_;
    fullscreenUid_ = temp;
}

// Cell
- (void)cell:(AGSChatCell *)cell didMuteAudio:(BOOL)muted
{
    NSLog(@"make user: %td %@", cell.uid, muted?@"muted":@"unmuted");
    [self.agoraKit muteAllRemoteAudioStreams:muted];
}

// Rating
- (void)ratingChanged:(float)newRating
{
    NSLog(@"rating changed: %f", newRating);
    self.rating = (NSInteger)newRating;
}

// App Alert
- (void)agsAlertView:(AGSAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 1) {
        [self.agoraKit rate:self.callId rating:self.rating description:nil];
    }
    
    [alertView hideAlertView];
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self.navigationController popViewControllerAnimated:YES];
    });
}

// Default Alert
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if ([alertView isEqual:self.errorKeyAlert]) {
        AGSProfileViewController *controller = [self.frostedViewController.menuViewController.storyboard instantiateViewControllerWithIdentifier:@"Profile"];
        [self.navigationController pushViewController:controller animated:YES];
    }
}

#pragma mark - Tool

- (void)prepareAgoraKit
{
    [self initAgoraKit];
    [self joinChannel];
}

- (void)clearData
{
    [self.uids removeAllObjects];
    [self.videoMuteForUids removeAllObjects];
    [self.activityStrings removeAllObjects];
    
    [self.tableView reloadData];
    [self.collectionView reloadData];
    
    // update UI
    [self.durationTimer invalidate];
    self.duration = 0;
    self.durationTimer = nil;
}

- (void)initAgoraKit
{
    if (self.agoraKit) {
        self.agoraKit = nil;
    }
    self.agoraKit = [[AgoraRtcEngineKit alloc] initWithVendorKey:self.key error:^(AgoraRtcErrorCode errorCode) {
        if (errorCode == AgoraRtc_Error_NoError) {
            NSLog(@"agora kit init successfully");
        } else {
            if (errorCode == AgoraRtc_Error_InvalidVendorKey) {
                isErrorKey_ = YES;
                [self.agoraKit leaveChannel];
                [self.errorKeyAlert show];
            }
        }
    }];

    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *docDir = [paths objectAtIndex:0];
    [self.agoraKit setLogFile:[NSString stringWithFormat:@"%@/agora.log", docDir]];
    [self.agoraKit setSpeakerphoneVolume:200];
    [self.agoraKit enableNetworkTest];
    
    [self setUpVideo];
    [self setUpBlocks];
    [self setupMenuSettingBlocks];
}

- (void)joinChannel
{
    [self.agoraKit joinChannelByKey:self.key channelName:self.channel info:nil uid:0 joinSuccess:^(NSString *channel, NSUInteger uid, NSInteger elapsed) {
        [self showAlertLabelWithString:NSLocalizedString(@"Waiting for attendees", @"")];
        isErrorKey_ = NO;
        
        if (self.type == AGSChatTypeAudio) {
            [self.agoraKit disableVideo];
            [self.agoraKit setEnableSpeakerphone:YES];
            [self selectSpeakerButtons:NO];
        } else {
            [self.agoraKit setEnableSpeakerphone:YES];
            [self selectSpeakerButtons:NO];
        }
        
        // Get call id
        self.callId = [self.agoraKit getCallId];
        self.startDate = [NSDate date];
        self.myUid = uid;
        
        [UIApplication sharedApplication].idleTimerDisabled = YES;
    }];
}

- (void)setUpVideo
{
    [self.agoraKit enableVideo];
    localVideoCanvas_ = [[AgoraRtcVideoCanvas alloc] init];
    localVideoCanvas_.uid = 0;
    localVideoCanvas_.view = self.videoMainView;
    localVideoCanvas_.renderMode = AgoraRtc_Render_Hidden;
    [self.agoraKit setupLocalVideo:localVideoCanvas_];
    
    fullscreenUid_ = 0;
}

- (void)updateActivityTableView
{
    NSIndexPath *lastIndexPath = [NSIndexPath indexPathForRow:self.activityStrings.count-1 inSection:0];
    [self.tableView insertRowsAtIndexPaths:@[lastIndexPath] withRowAnimation:UITableViewRowAnimationNone];
    [self.tableView reloadRowsAtIndexPaths:@[[NSIndexPath indexPathForRow:lastIndexPath.row-1 inSection:lastIndexPath.section]] withRowAnimation:UITableViewRowAnimationFade];
    [self.tableView scrollToRowAtIndexPath:lastIndexPath atScrollPosition:UITableViewScrollPositionBottom animated:YES];
}

- (void)setUpBlocks
{
    //
    // Network
    //
    [self.agoraKit networkQualityBlock:^(AgoraRtcQuality quality) {
            NSString *imageName = @"";
            switch (quality) {
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
            self.networkImageView.image = [UIImage imageNamed:imageName];
    }];
    
    //
    // Session
    //
    [self.agoraKit updateSessionStatBlock:^(AgoraRtcSessionStat *stat) {
        // Update talk time
        if (self.duration == 0 && !self.durationTimer) {
            self.talkTimeLabel.text = @"00:00";
            self.durationTimer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(updateTalkTimeLabel) userInfo:nil repeats:YES];
        }
        
        NSUInteger traffic = (stat.txBytes + stat.rxBytes - lastStat_.txBytes - lastStat_.rxBytes) / 1024;
        NSUInteger speed = traffic / (stat.duration - lastStat_.duration);
        NSString *trafficString = [NSString stringWithFormat:@"%tdKB/s", speed];
        self.dataTrafficLabel.text = trafficString;
        
        lastStat_ = stat;
    }];
    
    //
    // User joined
    //
    [self.agoraKit userJoinedBlock:^(NSUInteger uid, NSInteger elapsed) {
        NSLog(@"user joined: %td", uid);
        //
        if (self.firstJoinedUid == 0) {
            self.firstJoinedUid = uid;
        }
        
        //
        [self hideAlertLabel];
        [self.uids addObject:@(uid)];
        
        [self.collectionView insertItemsAtIndexPaths:@[[NSIndexPath indexPathForRow:self.uids.count-1 inSection:0]]];
        
        //
        [self.activityStrings addObject:[NSString stringWithFormat:@"%td %@", uid, NSLocalizedString(@"joined room", @"")]];

        [self updateActivityTableView];
        
    }];
    
    //
    // User offline
    //
    [self.agoraKit userOfflineBlock:^(NSUInteger uid) {
        NSLog(@"user offine: %td", uid);
        NSInteger index = [self.uids indexOfObject:@(uid)];
        
        if (index != NSNotFound) {
            NSIndexPath *indexPath = [NSIndexPath indexPathForRow:index inSection:0];
            if (fullscreenUid_ == uid) {
                
                [self.agoraKit setupLocalVideo:localVideoCanvas_];
                
                [self.agoraKit disableVideo];
                dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(.3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                    [self.agoraKit enableVideo];
                });
                
            }
        
            [self.uids removeObjectAtIndex:index];
            [self.collectionView deleteItemsAtIndexPaths:@[indexPath]];
        }
        
        [self.activityStrings addObject:[NSString stringWithFormat:@"%td %@", uid, NSLocalizedString(@"left room", @"")]];
        [self updateActivityTableView];
    }];
    
    //
    // Leave channel
    //
    [self.agoraKit leaveChannelBlock:^(AgoraRtcSessionStat *stat) {
        if (isErrorKey_) return ;
        // Myself leave status
        [self.durationTimer invalidate];
        
        // Rating view
        AGSRatingView *view = [[NSBundle mainBundle] loadNibNamed:@"AGSRatingView" owner:nil options:nil].lastObject;
        view.frame = CGRectMake(50, 200, 170, 61);
        view.delegate = self;
        //
        if (lastStat_) {
            double traffic = (lastStat_.rxBytes+lastStat_.txBytes)/(1024.0*1024.0);
            view.dataTrafficLabel.text = [NSString stringWithFormat:@"%.2fMB", traffic];
        }
        if (self.duration > 0) {
            view.talkTimeLabel.text = self.talkTimeLabel.text;
        }
        
        // Alert
        AGSAlertView *alert = [[AGSAlertView alloc] init];
        alert.delegate = self;
        [alert addStatusView:view];
        alert.titleLabel.text = NSLocalizedString(@"Please rate the call", @"");
        alert.subTitleLabel.text = NSLocalizedString(@"Let's do better", @"");
        alert.subTitleLabel.textColor = [UIColor colorWithRed:220/255.0 green:186/255.0 blue:117/255.0 alpha:1];
        [alert.leftButton setTitle:NSLocalizedString(@"Close", @"") forState:UIControlStateNormal];
        [alert.rightButton setTitle:NSLocalizedString(@"Rate", @"") forState:UIControlStateNormal];
        
        [alert showAlertView];
        
        // Save record
        if (self.firstJoinedUid != 0) {
            NSString *url = [self.agoraKit makeQualityReportUrl:self.callId listenerUid:self.firstJoinedUid speakerrUid:self.myUid reportFormat:AgoraRtc_QualityReportFormat_Html];
            [[AGSCoreDataManager shareManager] saveRecordWithCallId:self.callId date:self.startDate duration:self.duration url:url];
        }
        
        [UIApplication sharedApplication].idleTimerDisabled = YES;
    }];
    
    //
    [self.agoraKit userMuteVideoBlock:^(NSUInteger uid, bool muted) {
        NSLog(@"user %td video: %@", uid, muted ? @"muted" : @"unmuted");
        
        [self.videoMuteForUids setObject:@(muted) forKey:@(uid)];
        
        [self.collectionView reloadItemsAtIndexPaths:@[[NSIndexPath indexPathForRow:[self.uids indexOfObject:@(uid)] inSection:0]]];
        if (muted) {
            [self.activityStrings addObject:[NSString stringWithFormat:@"%td %@", uid, NSLocalizedString(@"disabled camera", @"")]];
        } else {
            [self.activityStrings addObject:[NSString stringWithFormat:@"%td %@", uid, NSLocalizedString(@"enabled camera", @"")]];
        }
        [self updateActivityTableView];
        
    }];
    
    [self.agoraKit userMuteAudioBlock:^(NSUInteger uid, bool muted) {
        NSLog(@"user %td audio: %@", uid, muted ? @"muted" : @"unmuted");
        
        if (muted) {
            [self.activityStrings addObject:[NSString stringWithFormat:@"%td %@", uid, NSLocalizedString(@"disabled microphone", @"")]];
        } else {
            [self.activityStrings addObject:[NSString stringWithFormat:@"%td %@", uid, NSLocalizedString(@"enabled microphone", @"")]];
        }
        [self updateActivityTableView];
    }];
    
    [self.agoraKit connectionLostBlock:^{
        [self showAlertLabelWithString:NSLocalizedString(@"No network connection, please check your network", @"")];
        self.dataTrafficLabel.text = @"0KB/s";
    }];
    
    [self.agoraKit audioQualityBlock:^(NSUInteger uid, AgoraRtcQuality quality, NSUInteger delay, NSUInteger lost) {
        
//        NSLog(@"audio quality %td %td: quality-%td, delay-%td, lost-%td", [self.uids indexOfObject:@(uid)], uid, quality, delay, lost);
        
        AGSChatCell *cell = (AGSChatCell *)[self.collectionView cellForItemAtIndexPath:[NSIndexPath indexPathForRow:[self.uids indexOfObject:@(uid)] inSection:0]];
        cell.networkQulity = quality;
    }];
    
    [self.agoraKit audioRecorderExceptionBlock:^(NSInteger elapsed) {
        NSLog(@"audio recorder exception, elapsed: %zd", elapsed);
    }];
    
    [self.agoraKit firstLocalVideoFrameBlock:^(NSInteger width, NSInteger height, NSInteger elapsed) {
        NSLog(@"local video display");
        self.videoMainView.frame = self.videoMainView.superview.bounds; // video view's autolayout cause crash
    }];
}

- (void)setupMenuSettingBlocks
{
    AGSMenuViewController *menu = (AGSMenuViewController *)self.frostedViewController.menuViewController;
    
    [menu setResolutionBlock:^(AGSResolution *resolution) {
        [self.agoraKit setVideoResolution:resolution.width.intValue andHeight:resolution.height.intValue];
    }];
    
    [menu setFloatWindowBlock:^(BOOL floatWindow) {
        self.activityContrainerView.hidden = !floatWindow;
        self.statContrainerView.backgroundColor = floatWindow ? [UIColor clearColor] : [UIColor colorWithWhite:0 alpha:.4];
    }];
    
    [menu setRecordingBlock:^(BOOL recording) {
        if (recording) {
            NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
            NSString *dir = [[paths objectAtIndex:0] stringByAppendingPathComponent:@"recording"];
            if (![[NSFileManager defaultManager] fileExistsAtPath:dir]) {
                NSError *error = nil;
                [[NSFileManager defaultManager] createDirectoryAtPath:dir withIntermediateDirectories:NO attributes:nil error:&error];
            }
            NSString *file = [NSString stringWithFormat:@"%f.wav", [NSDate date].timeIntervalSince1970];
            [self.agoraKit startAudioRecording:[dir stringByAppendingPathComponent:file]];
        } else {
            [self.agoraKit stopAudioRecording];
        }
    }];
    
    [menu setRateBlock:^(int rate) {
        [self.agoraKit setVideoMaxBitrate:rate];
    }];
    
    [menu setFrameBlock:^(int frame) {
        [self.agoraKit setVideoMaxFrameRate:frame];
    }];
    
    [menu setVolumeBlock:^(int volume) {
        NSLog(@"%d", volume);
        [self.agoraKit setSpeakerphoneVolume:volume];
    }];
}

- (void)showAlertLabelWithString:(NSString *)text;
{
    self.alertLabel.hidden = NO;
    self.alertLabel.text = text;
}

- (void)hideAlertLabel
{
    self.alertLabel.hidden = YES;
}

- (void)updateTalkTimeLabel
{
    self.duration++;
    NSUInteger seconds = self.duration % 60;
    NSUInteger minutes = (self.duration - seconds) / 60;
    self.talkTimeLabel.text = [NSString stringWithFormat:@"%02ld:%02ld", minutes, seconds];
}

- (void)selectSpeakerButtons:(BOOL)selected
{
    for (UIButton *btn in self.speakerControlButtons) {
        btn.selected = selected;
    }
}

- (void)selectAudioMuteButtons:(BOOL)selected
{
    for (UIButton *btn in self.audioMuteControlButtons) {
        btn.selected = selected;
    }
}

#pragma mark - IB Actions

- (IBAction)didClickBcakView:(id)sender
{
    [self showAlertLabelWithString:NSLocalizedString(@"Exiting", @"")];
    if (isErrorKey_) {
        [self.navigationController popViewControllerAnimated:YES];
    } else {
        [self.agoraKit leaveChannel];
    }
}

- (IBAction)didClickAudioMuteButton:(UIButton *)btn
{
    [self selectAudioMuteButtons:!btn.selected];
    [self.agoraKit muteLocalAudioStream:btn.selected];
}

- (IBAction)didClickSpeakerButton:(UIButton *)btn
{
    [self.agoraKit setEnableSpeakerphone:!self.agoraKit.isSpeakerphoneEnabled];
    [self selectSpeakerButtons:!self.agoraKit.isSpeakerphoneEnabled];
}

- (IBAction)didClickVideoMuteButton:(UIButton *)btn
{
    btn.selected = !btn.selected;
    [self.agoraKit muteLocalVideoStream:btn.selected];
    self.videoMainView.hidden = btn.selected;
}

- (IBAction)didClickSwitchButton:(UIButton *)btn
{
    btn.selected = !btn.selected;
    [self.agoraKit switchCamera];
}

- (IBAction)didClickHungUpButton:(UIButton *)btn
{
    [self showAlertLabelWithString:NSLocalizedString(@"Exiting", @"")];
    [self.agoraKit leaveChannel];
}

- (IBAction)didClickAudioButton:(UIButton *)btn
{
    // Start audio chat
    self.type = AGSChatTypeAudio;
    [self.agoraKit disableVideo];
}

- (IBAction)didClickVideoButton:(UIButton *)btn
{
    // Start video chat
    self.type = AGSChatTypeVideo;
    [self.agoraKit enableVideo];
    if (self.cameraControlButton.selected) {
        self.cameraControlButton.selected = NO;
    }
}

- (IBAction)didClickMenuButton:(id)sender
{
    [self.frostedViewController presentMenuViewController];
}

#pragma mark - Setter and Getter

- (void)setType:(AGSChatType)type
{
    _type = type;
    if (type == AGSChatTypeVideo) {
        // Control buttons
        self.videoControlView.hidden = NO;
        self.audioControlView.hidden = YES;
        
        // Video/Audio switch button
        self.videoButton.selected = YES;
        self.audioButton.selected = NO;
        
        //
        self.videoMainView.hidden = NO;
    } else {
        // Control buttons
        self.videoControlView.hidden = YES;
        self.audioControlView.hidden = NO;
        
        // Video/Audio switch button
        self.videoButton.selected = NO;
        self.audioButton.selected = YES;
        
        //
        self.videoMainView.hidden = YES;
    }
    [self.collectionView reloadData];
}

- (UIAlertView *)errorKeyAlert
{
    if (!_errorKeyAlert) {
        _errorKeyAlert = [[UIAlertView alloc] initWithTitle:@""
                                                    message:NSLocalizedString(@"Vendor key incorrect, please update user information", @"")
                                                   delegate:self
                                          cancelButtonTitle:NSLocalizedString(@"Done", @"")
                                          otherButtonTitles:nil];
        _errorKeyAlert.delegate = self;
    }
    return _errorKeyAlert;
}

@end

@implementation AGSChatActivityCell

@end