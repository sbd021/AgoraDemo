//
//  AGGlobalSessionConfiguration.h
//  AgoraMacFullset
//
//  Created by Jesse on 12/01/16.
//  Copyright © 2016 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AgoraRtcEngineKit/AgoraRtcEngineKit.h"

@interface AGGlobalSessionConfiguration : NSObject

@property (strong, nonatomic) NSString *vendorKey;
@property (strong, nonatomic) NSString *roomIdentifier;
@property (nonatomic) AgoraRtcChannelProfile channelProfile;
@property (nonatomic) AgoraRtcVideoProfile videoProfile;
@property (nonatomic) BOOL videoEnabled;

+ (instancetype)configuration;

+ (NSString *)displayNameForVideoProfile:(AgoraRtcVideoProfile)profile;
+ (NSString *)displayNameForChannelProfile:(AgoraRtcChannelProfile)profile;

@end
