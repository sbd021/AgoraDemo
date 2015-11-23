//
//  AGSEnterRoomViewController.m
//  AgoraSample
//
//  Created by apple on 15/9/15.
//  Copyright (c) 2015年 Agora. All rights reserved.
//

#import "AGSSelectMediaViewController.h"
#import "AGSCallBackView.h"
#import "AGSAgoraKitManager.h"
#import "AGSChatViewController.h"
#import "AGSEchoTestView.h"
#import "UIColor+Helper.h"

#define kRecordAudioFile @"textRecord.caf"

@interface AGSSelectMediaViewController ()

@property (weak, nonatomic) IBOutlet UITextField *roomNumberTextField;
@property (weak, nonatomic) IBOutlet UIButton *echoTest;
@property (weak, nonatomic) IBOutlet UILabel *videoLabel;
@property (weak, nonatomic) IBOutlet UILabel *voiceLabel;

@property (nonatomic, strong) AGSAlertView *alertView;
@property (nonatomic, strong) AGSEchoTestView *echoTestView;

@property (nonatomic, strong) AVAudioSession *audioSession;
@property (nonatomic, strong) AVAudioRecorder *audioRecorder;
@property (nonatomic, strong) AVAudioPlayer *audioPlayer;

@property (nonatomic, readwrite) BOOL isTesting;
@property (nonatomic, strong) NSTimer *recorderTimer;
@end

@implementation AGSSelectMediaViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    self.navigationController.navigationBarHidden = NO;
    
    //
    self.title = NSLocalizedString(@"Agora Easy Call", @"");
    [self.echoTest setTitle:NSLocalizedString(@"Test", @"") forState:UIControlStateNormal];
    self.roomNumberTextField.placeholder = NSLocalizedString(@"Enter Room No.", @"");
    self.videoLabel.text = NSLocalizedString(@"Join Video Call", @"");
    self.voiceLabel.text = NSLocalizedString(@"Join Voice Call", @"");
    
#ifdef DEBUG
        self.roomNumberTextField.text = @"1024";
#endif
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
}

#pragma mark - Actions

- (IBAction)didClickShowEchoTestView:(id)sender
{
    [self startTesting];
}

- (IBAction)didClickMenuButton:(UIButton *)sender
{
    [self.frostedViewController presentMenuViewController];
}

- (IBAction)didClickChatButton:(UIButton *)sender
{
    if ([self isValidInput]) {
        [self performSegueWithIdentifier:AGSKeySegueIdentifierChat sender:sender];
    }
}

- (BOOL)isValidInput
{
    [self.view endEditing:YES];
    if (self.roomNumberTextField.text.length && self.roomNumberTextField.text.length) {
        return YES;
    } else {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:nil
                                                            message:NSLocalizedString(@"Room No. can not be empty", @"")
                                                           delegate:nil
                                                  cancelButtonTitle:nil
                                                  otherButtonTitles:NSLocalizedString(@"Done", @""), nil];
        [alertView show];
        return NO;
    }
}

#pragma mark - Start/Stop testing

- (void)startTesting
{
    [self.view endEditing:YES];
    self.isTesting = YES;
    
    // Init and show
    [self setAlertViewStat:0];
    [self.alertView showAlertView];
}

- (void)stopTesting
{
    [self.alertView hideAlertView];
    self.isTesting = NO;
    // Stop recording and playing
    [self.recorderTimer invalidate];
    self.recorderTimer = nil;
    
    [self.audioRecorder stop];
//    [self.audioRecorder deleteRecording];
    [self.audioPlayer stop];
    [self.audioSession setActive:NO error:nil];
}

#pragma mark - Alert View Delegate

- (void)agsAlertView:(AGSAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0) {
        [self stopTesting];
    } else {
        [self startRecording];
    }
}

- (void)startRecording
{
    [self setAlertViewStat:1];

    [self.audioSession setCategory:AVAudioSessionCategoryRecord error:nil];
    [self.audioRecorder record];
    // Volume
    [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(audioRecordPowerChange:) userInfo:nil repeats:YES];
    // Stop recoring
    self.recorderTimer = [NSTimer scheduledTimerWithTimeInterval:5 target:self selector:@selector(stopRecording) userInfo:nil repeats:NO];
    
}

- (void)stopRecording
{
    [self.audioRecorder stop];
}

#pragma mark - Audio Recorder/Player Delegate
// Recorder
- (void)audioRecorderDidFinishRecording:(AVAudioRecorder *)recorder successfully:(BOOL)flag
{
    if (!self.isTesting) {
        return;
    }
    
    [self setAlertViewStat:4];
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(.3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        
        [self.audioSession setCategory:AVAudioSessionCategoryPlayback error:nil];
        [self.audioPlayer play];
        [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(audioPlayerPowerChange:) userInfo:nil repeats:YES];
    });
}

- (void)audioRecorderEncodeErrorDidOccur:(AVAudioRecorder *)recorder error:(NSError *)error
{
    [self setAlertViewStat:3];
}

// Player
- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag
{
    [self setAlertViewStat:2];
}

- (void)audioPlayerDecodeErrorDidOccur:(AVAudioPlayer *)player error:(NSError *)error
{
    [self setAlertViewStat:3];
}

#pragma mark - Others

- (void)audioRecordPowerChange:(NSTimer *)timer
{
    if (self.audioRecorder.isRecording) {
        [self.audioRecorder updateMeters];
        float power = [self.audioRecorder averagePowerForChannel:0];
        CGFloat progress = (power+160)/160.0;
        [self.echoTestView.volumeView setVolumenValue:progress];
    } else {
        [timer invalidate];
        timer = nil;
    }
}

- (void)audioPlayerPowerChange:(NSTimer *)timer
{
    if (self.audioPlayer.isPlaying) {
        [self.audioPlayer updateMeters];
        float power = [self.audioPlayer averagePowerForChannel:0];
        CGFloat progress = (power+160)/160.0;
        [self.echoTestView.volumeView setVolumenValue:progress];
    } else {
        [timer invalidate];
        timer = nil;
    }
}

- (void)setAlertViewStat:(NSInteger)stat
{
    switch (stat) {
        case 0: // Initial
            [self.echoTestView.volumeView setVolumenValue:0];
            [self.alertView setTitle:NSLocalizedString(@"Echo Test", @"")];
            [self.alertView setSubTitle:NSLocalizedString(@"Click Test to Start", @"") color:[UIColor colorWithHexString:@"B7B7B7"]];
            [self.alertView setRightButtonText:NSLocalizedString(@"Echo Test", @"") color:[UIColor colorWithHexString:@"1677CB"]];
            [self.alertView setLeftButtonText:NSLocalizedString(@"Cancel", @"")];
            [self.alertView setButtonEnabled:YES];
            break;
        case 1: // Doing
            [self.alertView setButtonEnabled:NO];
            [self.alertView setSubTitle:NSLocalizedString(@"Please speak to the phone", @"") color:[UIColor colorWithHexString:@"B7B7B7"]];
            [self.alertView setRightButtonText:NSLocalizedString(@"In Testing", @"") color:[UIColor colorWithHexString:@"999999"]];
            [self.alertView setLeftButtonText:NSLocalizedString(@"Cancel", @"")];
            break;
        case 2: // Success
            [self.alertView setButtonEnabled:YES];
            [self.alertView setSubTitle:NSLocalizedString(@"Click Test to Start", @"") color:[UIColor colorWithHexString:@"B7B7B7"]];
            [self.alertView setRightButtonText:NSLocalizedString(@"Test Again", @"") color:[UIColor colorWithHexString:@"1677CB"]];
            [self.alertView setLeftButtonText:NSLocalizedString(@"Done", @"")];
            break;
        case 3: // Error
            [self.alertView setButtonEnabled:YES];
            [self.alertView setSubTitle:NSLocalizedString(@"Click Test to Start", @"") color:[UIColor colorWithHexString:@"DCB059"]];
            [self.alertView setRightButtonText:NSLocalizedString(@"Test Again", @"") color:[UIColor colorWithHexString:@"1677CB"]];
            break;
        case 4: // Playing
            [self.alertView setSubTitle:NSLocalizedString(@"Detecting", @"")];
            break;
        default:
            break;
    }
}

#pragma mark -
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if (![segue.identifier isEqualToString:AGSKeySegueIdentifierChat]) {return;}
    
    AGSChatViewController *chatViewController = segue.destinationViewController;
    chatViewController.dictionary = @{AGSKeyChannel: self.roomNumberTextField.text};
    
    UIButton *button = (UIButton *)sender;
    if (button.tag == 0) {
        chatViewController.chatType = AGSChatTypeVideo;
    } else {
        chatViewController.chatType = AGSChatTypeAudio;
    }
}

#pragma mark - Testing Config

- (AGSAlertView *)alertView
{
    if (!_alertView) {
        _alertView = [[AGSAlertView alloc] init];
        _alertView.delegate = self;
        [_alertView addStatusView:self.echoTestView];
    }
    return _alertView;
}

- (AGSEchoTestView *)echoTestView
{
    if (!_echoTestView) {
        _echoTestView = [[[NSBundle mainBundle] loadNibNamed:@"AGSEchoTestView" owner:self options:nil] lastObject];
        [_echoTestView.volumeView setNumberOfBars:21];
        [_echoTestView.volumeView setBarsColorMin:[UIColor greenColor]];
        [_echoTestView.volumeView setBarsColorMax:[UIColor grayColor]];
        [_echoTestView.volumeView setVolumenValue:0];
    }
    return _echoTestView;
}

- (AVAudioSession *)audioSession
{
    if (!_audioSession) {
        _audioSession = [AVAudioSession sharedInstance];
        [_audioSession setCategory:AVAudioSessionCategoryPlayAndRecord error:nil];
        [_audioSession setActive:YES error:nil];
    }
    return _audioSession;
}

- (AVAudioRecorder *)audioRecorder
{
    if (!_audioRecorder) {
        NSDictionary *settings = @{AVFormatIDKey: @(kAudioFormatLinearPCM),
                                     AVSampleRateKey: @(8000),
                                     AVNumberOfChannelsKey: @(1),
                                     AVLinearPCMBitDepthKey: @(8),
                                     AVLinearPCMIsFloatKey: @(YES),
                                     AVLinearPCMIsBigEndianKey: @(NO)};
        NSError *error = nil;
        _audioRecorder = [[AVAudioRecorder alloc] initWithURL:[self filePath] settings:settings error:&error];
        _audioRecorder.delegate = self;
        _audioRecorder.meteringEnabled = YES;
    }
    
    return _audioRecorder;
}

- (AVAudioPlayer *)audioPlayer
{
    if (!_audioPlayer) {
        NSError *error = nil;
        _audioPlayer = [[AVAudioPlayer alloc]initWithContentsOfURL:[self filePath] error:&error];
        _audioPlayer.delegate = self;
        _audioPlayer.numberOfLoops = 0;
        _audioPlayer.meteringEnabled = YES;
        [_audioPlayer prepareToPlay];
    }
    return _audioPlayer;
}

- (NSURL *)filePath
{
    NSString *urlStr = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
    NSURL *url = [NSURL fileURLWithPath:[urlStr stringByAppendingPathComponent:kRecordAudioFile]];
    return url;
}

@end
