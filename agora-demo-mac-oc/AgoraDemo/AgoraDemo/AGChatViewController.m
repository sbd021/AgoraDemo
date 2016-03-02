//
//  AGChatViewController.m
//  AgoraMacFullset
//
//  Created by Jesse on 16/01/16.
//  Copyright © 2016 Agora. All rights reserved.
//

#import "AGChatViewController.h"
#import "AGHostingView.h"
#import "AGGlobalSessionConfiguration.h"
#import "NSColor+Hex.h"
#import "AGLoginViewController.h"
#import "AGLoginWindow.h"
#import <AgoraRtcEngineKit/AgoraRtcEngineKit.h>


@interface AGVideoSession : NSObject

@property (nonatomic) NSUInteger uid;
@property (strong, nonatomic) AGHostingView *hostingView;
@property (strong, nonatomic) AgoraRtcVideoCanvas *canvas;

@end

@implementation AGVideoSession

+ (instancetype)localSession {
    return [[AGVideoSession alloc] initWithUid:0];
}

- (instancetype)initWithUid:(NSUInteger)uid {
    self = [super init];
    if (self) {
        self.uid = uid;
        self.hostingView = [[AGHostingView alloc] initWithFrame:NSMakeRect(0, 0, 100, 100)];
        self.canvas = [AgoraRtcVideoCanvas new];
        self.canvas.uid = uid;
        self.canvas.view = self.hostingView.videoView;
        self.canvas.renderMode = AgoraRtc_Render_Fit;
    }
    return self;
}

@end



typedef NS_ENUM(NSInteger, AGLayoutMode) {
    AGLayoutModeLocalPrimary,
    AGLayoutModeLocalSecondary,
};


@interface AGChatViewController () <AgoraRtcEngineDelegate>

@property (weak) IBOutlet NSView *sessionContainerView;
@property (weak) IBOutlet NSView *chatMenuView;
@property (weak) IBOutlet NSLayoutConstraint *chatMenuWidthConstraint;
@property (weak) IBOutlet NSButton *muteVideoButton;
@property (weak) IBOutlet NSTextField *muteVideoLabel;
@property (weak) IBOutlet NSTextField *muteAudioLabel;
@property (weak) IBOutlet NSButton *changeViewsButton;
@property (weak) IBOutlet NSTextField *changeViewsLabel;

@property (weak) IBOutlet NSTextField *timeLabel;
@property (weak) IBOutlet NSTextField *instructionLabel;
@property (weak) IBOutlet NSTextField *waitingLabel;
@property (strong, nonatomic) AgoraRtcEngineKit *agoraKit;
@property (strong, nonatomic) NSMutableArray<AGVideoSession *> *videoSessions;
@property (nonatomic) AGLayoutMode layoutMode;
@property (nonatomic) BOOL muteAudio;
@property (nonatomic) BOOL muteVideo;
@property (nonatomic) NSInteger duration;
@property (strong, nonatomic) NSTimer *durationTimer;

@end

@implementation AGChatViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.view.wantsLayer = YES;
    self.view.layer.backgroundColor = [NSColor clearColor].CGColor;
    
    self.sessionContainerView.wantsLayer = YES;
    self.sessionContainerView.layer.backgroundColor = [AGGlobalSessionConfiguration configuration].videoEnabled ? [NSColor blackColor].CGColor : [NSColor clearColor].CGColor;
    
    self.muteAudioLabel.stringValue = NSLocalizedString(@"Mute Audio", comment: @"");
    self.muteVideoLabel.stringValue = NSLocalizedString(@"Mute Video", comment: @"");
    self.changeViewsLabel.stringValue = NSLocalizedString(@"Switch", comment: "");
    
    self.chatMenuView.wantsLayer = YES;
    self.chatMenuView.layer.backgroundColor = [NSColor colorWithHex:0x3A3F4D alpha:0.8].CGColor;
    self.chatMenuView.layer.cornerRadius = 8;
    
    if (![AGGlobalSessionConfiguration configuration].videoEnabled) {
        self.chatMenuWidthConstraint.constant = 162;
        [self.muteVideoButton removeFromSuperview];
        [self.muteVideoLabel removeFromSuperview];
        [self.changeViewsButton removeFromSuperview];
        [self.changeViewsLabel removeFromSuperview];
    }
    
    self.instructionLabel.stringValue = @"";
    self.waitingLabel.stringValue = NSLocalizedString(@"waiting for friends to join", comment: @"");
   
    [self.sessionContainerView addTrackingArea:[[NSTrackingArea alloc] initWithRect:self.sessionContainerView.bounds
                                                                            options:NSTrackingMouseMoved | NSTrackingActiveInActiveApp | NSTrackingInVisibleRect
                                                                              owner:self
                                                                           userInfo:nil]];
    
    [self.chatMenuView addTrackingArea:[[NSTrackingArea alloc] initWithRect:self.chatMenuView.bounds
                                                                            options:NSTrackingMouseEnteredAndExited | NSTrackingActiveInActiveApp | NSTrackingInVisibleRect
                                                                              owner:self
                                                                           userInfo:nil]];
    [self initAgoraKit];
}

- (void)hideChatMenu {
    self.chatMenuView.hidden = YES;
}

- (void)updateTalkTimeLabel {
    self.duration += 1;
    
    NSUInteger s = self.duration % 60;
    NSUInteger m = self.duration / 60;
    self.timeLabel.stringValue = [NSString stringWithFormat:@"%02lu:%02lu", m, s];
}


- (void)mouseMoved:(NSEvent *)theEvent {
    if (self.chatMenuView.hidden) {
        self.chatMenuView.hidden = NO;
        [self performSelector:@selector(hideChatMenu) withObject:nil afterDelay:3];
    }
}

- (void)mouseEntered:(NSEvent *)theEvent {
    [AGChatViewController cancelPreviousPerformRequestsWithTarget:self];
}

- (void)mouseExited:(NSEvent *)theEvent {
    [self performSelector:@selector(hideChatMenu) withObject:nil afterDelay:3];
}


- (IBAction)muteAudioButtonAction:(NSButton *)button {
    self.muteAudio = !self.muteAudio;
    [self.agoraKit muteLocalAudioStream:self.muteAudio];
    
    if (self.muteAudio) {
        [button setImage:[NSImage imageNamed:@"chat_disable_audio_button_on"]];
    } else {
        [button setImage:[NSImage imageNamed:@"chat_disable_audio_button"]];
    }
}

- (IBAction)muteVideoButtonAction:(NSButton *)button {
    self.muteVideo = !self.muteVideo;
    [self.agoraKit muteLocalVideoStream:self.muteVideo];
    
    if (self.muteVideo) {
        [button setImage:[NSImage imageNamed:@"chat_disable_video_button_on"]];
    } else {
        [button setImage:[NSImage imageNamed:@"chat_disable_video_button"]];
    }
    
    self.instructionLabel.stringValue = self.muteVideo ? @"Turn off camera" : @"Turn on camera";
}

- (IBAction)switchViewsButtonAction:(id)sender {
    if (self.layoutMode == AGLayoutModeLocalPrimary) {
        self.layoutMode = AGLayoutModeLocalSecondary;
    } else {
        self.layoutMode = AGLayoutModeLocalPrimary;
    }
    [self layoutVideoSessionsIfNeeded];
}

- (IBAction)hangUpButtonAction:(id)sender {
    [self leaveChannel];
}


#pragma mark - Layout

- (void)viewDidLayout {
    [super viewDidLayout];
    [self layoutVideoSessionsIfNeeded];
}

- (NSRect)primarySessionFrameAtIndex:(NSInteger)index containerSize: (NSSize)containerSize {
    CGFloat width = containerSize.width / 2;
    CGFloat height = containerSize.height / 2;
    CGFloat x = (index % 2) * width;
    CGFloat y = containerSize.height - (index / 2 + 1) * height;
    return NSMakeRect(x, y, width, height);
}

- (NSRect)secondarySessionFrameAtIndex:(NSInteger)index containerSize: (NSSize)containerSize {
    CGFloat x = containerSize.width - 116;
    CGFloat y = containerSize.height - (index + 1) * 116;
    return NSMakeRect(x, y, 100, 100);
}

- (void)layoutVideoSessionsIfNeeded {
    if (self.videoSessions.count == 0) {
        return;
    }

    NSMutableArray *sessions = [self.videoSessions mutableCopy];
    AGVideoSession *localSession = sessions[0];
    [sessions removeObjectAtIndex:0];
    
    if (self.layoutMode == AGLayoutModeLocalPrimary) {
        localSession.hostingView.frame = self.sessionContainerView.bounds;
        for (NSInteger i = 0; i < sessions.count; i ++) {
            AGVideoSession *session = sessions[i];
            session.hostingView.frame = [self secondarySessionFrameAtIndex:i
                                                           containerSize:self.sessionContainerView.bounds.size];
            [self.sessionContainerView addSubview:session.hostingView
                                       positioned:NSWindowAbove
                                       relativeTo:nil];
        }
    } else {
        if (sessions.count == 1) {
            [sessions[0] hostingView].frame = self.sessionContainerView.bounds;
        } else {
            for (NSInteger i = 0; i < sessions.count; i ++) {
                AGVideoSession *session = sessions[i];
                session.hostingView.frame = [self primarySessionFrameAtIndex:i
                                                               containerSize:self.sessionContainerView.bounds.size];
            }
        }
        
        localSession.hostingView.frame = [self secondarySessionFrameAtIndex:0
                                                              containerSize:self.sessionContainerView.bounds.size];
        [self.sessionContainerView addSubview:localSession.hostingView
                                   positioned:NSWindowAbove
                                   relativeTo:nil];
    }
}

#pragma mark - Agora Kit

- (void)initAgoraKit {
    AGGlobalSessionConfiguration *config = [AGGlobalSessionConfiguration configuration];
    
    self.agoraKit = [AgoraRtcEngineKit sharedEngineWithVendorKey:config.vendorKey delegate:self];
    [self.agoraKit setChannelProfile:config.channelProfile];
    
    if (config.videoEnabled) {
        [self.agoraKit enableVideo];
        [self.agoraKit setVideoProfile:config.videoProfile];
    } else {
        [self.agoraKit disableVideo];
    }
    
    // add local session
    self.videoSessions = [NSMutableArray array];
    AGVideoSession *localSession = [AGVideoSession localSession];
    localSession.hostingView.isLocalVideo = YES;
    [self.videoSessions addObject:localSession];
    [self.sessionContainerView addSubview:localSession.hostingView];
    [self layoutVideoSessionsIfNeeded];
    [self.agoraKit setupLocalVideo:localSession.canvas];
    
    // join channel
    [self.agoraKit joinChannelByKey:config.vendorKey
                        channelName:config.roomIdentifier
                               info:nil
                                uid:0
                        joinSuccess:nil];
    
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    [userDefaults setObject:config.vendorKey forKey:AGDKeyVendorKey];
}

- (void)leaveChannel {
    [self.durationTimer invalidate];
    self.durationTimer = nil;
    
    [self.agoraKit leaveChannel:nil];
    [self.agoraKit setupLocalVideo:nil];
    for (AGVideoSession *session in self.videoSessions) {
        [session.hostingView removeFromSuperview];
    }
    [self.videoSessions removeAllObjects];
    
    self.agoraKit = nil;
    
    [self.view.window close];
    
    AGLoginViewController *loginViewController = [self.storyboard instantiateControllerWithIdentifier:@"AGLoginViewController"];
    [[AGLoginWindow window] setContentViewController:loginViewController];
    [[AGLoginWindow window] makeKeyAndOrderFront:nil];
    
//    // restart app
//    int identifier = [NSProcessInfo processInfo].processIdentifier;
//    NSURL *pathUrl = [NSBundle mainBundle].executableURL;
//    NSString *path = [NSString stringWithCString:[pathUrl fileSystemRepresentation]
//                                        encoding:NSUTF8StringEncoding];
//    [NSTask launchedTaskWithLaunchPath:path arguments:@[[NSString stringWithFormat:@"%@", @(identifier)]]];
//    [NSApp terminate:self];
}


- (void)rtcEngine:(AgoraRtcEngineKit *)engine reportRtcStats:(AgoraRtcStats *)stats {
    if (self.duration == 0) {
        self.timeLabel.hidden = NO;
        self.durationTimer = [NSTimer scheduledTimerWithTimeInterval:1.0f
                                                              target:self
                                                            selector:@selector(updateTalkTimeLabel)
                                                            userInfo:nil
                                                             repeats:YES];
    }
}

- (void)rtcEngine:(AgoraRtcEngineKit *)engine didJoinedOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed {
    AGVideoSession *newSession = [[AGVideoSession alloc] initWithUid:uid];
    newSession.hostingView.nameLabel.stringValue = [NSString stringWithFormat:@"%@", @(uid)];
    [self.videoSessions addObject:newSession];
    [self.sessionContainerView addSubview:newSession.hostingView];
    [self layoutVideoSessionsIfNeeded];
    [self.agoraKit setupRemoteVideo:newSession.canvas];
    
    self.waitingLabel.hidden = YES;
}

- (void)rtcEngine:(AgoraRtcEngineKit *)engine didOfflineOfUid:(NSUInteger)uid reason:(AgoraRtcUserOfflineReason)reason {
    for (AGVideoSession *session in self.videoSessions) {
        if (session.uid == uid) {
            [session.hostingView removeFromSuperview];
            [self.videoSessions removeObject:session];
            [self layoutVideoSessionsIfNeeded];
            break;
        }
    }
}


@end
