//
//  AGGlobalSessionConfiguration.m
//  AgoraMacFullset
//
//  Created by Jesse on 12/01/16.
//  Copyright © 2016 Agora. All rights reserved.
//

#import "AGGlobalSessionConfiguration.h"

@implementation AGGlobalSessionConfiguration

+ (instancetype)configuration {
    static dispatch_once_t onceToken;
    static AGGlobalSessionConfiguration *config;
    dispatch_once(&onceToken, ^{
        config = [AGGlobalSessionConfiguration new];
        config.vendorKey = @"";
        config.roomIdentifier = @"";
        config.channelProfile = AgoraRtc_ChannelProfile_Free;
        config.videoEnabled = YES;
        config.videoProfile = AgoraRtc_VideoProfile_360P;
    });
    
    return config;
}

+ (NSString *)displayNameForVideoProfile:(AgoraRtcVideoProfile)profile {
    switch (profile) {
        case AgoraRtc_VideoProfile_DEFAULT:
            return @"360P640*360_15FPS400";
        case AgoraRtc_VideoProfile_120P:
            return @"120P160*120_15FPS80";
        case AgoraRtc_VideoProfile_240P:
            return @"240P320*240_15FPS200";
        case AgoraRtc_VideoProfile_360P_4:
            return @"360P640*360_30FPS680";
        case AgoraRtc_VideoProfile_360P_6:
            return @"360P360*360_30FPS500";
        case AgoraRtc_VideoProfile_480P:
            return @"480P640*480_15FPS500";
        case AgoraRtc_VideoProfile_480P_4:
            return @"480P640*480_30FPS750";
        case AgoraRtc_VideoProfile_480P_6:
            return @"480P480*480_30FPS680";
        case AgoraRtc_VideoProfile_720P:
            return @"720P1280*720_15FPS1000";
        case AgoraRtc_VideoProfile_720P_3:
            return @"720P1280*720_30FPS1700";
        case AgoraRtc_VideoProfile_1080P:
            return @"1080P1920*1080_15FPS1500";
        case AgoraRtc_VideoProfile_1080P_3:
            return @"1080P1920*1080_30FPS2550";
        case AgoraRtc_VideoProfile_1080P_5:
            return @"1080P1920*1080_60FPS4300";
        default:
            return @"";
    }
}

+ (NSString *)displayNameForChannelProfile:(AgoraRtcChannelProfile)profile {
    switch (profile) {
        case AgoraRtc_ChannelProfile_Free:
            return NSLocalizedString(@"Free", comment: @"");
        case AgoraRtc_ChannelProfile_Broadcaster:
            return NSLocalizedString(@"Host", comment: @"");
        case AgoraRtc_ChannelProfile_Audience:
            return NSLocalizedString(@"Audience", comment: @"");
        default:
            return @"";
    }
}

@end
