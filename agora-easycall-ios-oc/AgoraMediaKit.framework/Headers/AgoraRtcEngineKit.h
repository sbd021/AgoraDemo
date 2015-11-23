//
//  AgoraRtcEngineKit.h
//  AgoraRtcEngineKit
//
//  Created by Sting Feng on 2014-8-11.
//  Copyright (c) 2015 Agora. All rights reserved.
//
//  v1.0

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
typedef UIView VIEW_CLASS;

#elif TARGET_OS_MAC
#import <AppKit/AppKit.h>
typedef NSView VIEW_CLASS;

#endif


typedef NS_ENUM(NSInteger, AgoraRtcErrorCode) {
    AgoraRtc_Error_NoError = 0,
    AgoraRtc_Error_Failed = 1,
    AgoraRtc_Error_InvalidArgument = 2,
    AgoraRtc_Error_NotReady = 3,
    AgoraRtc_Error_NotSupported = 4,
    AgoraRtc_Error_Refused = 5,
    AgoraRtc_Error_BufferTooSmall = 6,
	AgoraRtc_Error_NotInitialized = 7,
	AgoraRtc_Error_InvalidView = 8,
	AgoraRtc_Error_NoPermission = 9,
    AgoraRtc_Error_TimedOut = 10,
    AgoraRtc_Error_Canceled = 11,
    AgoraRtc_Error_TooOften = 12,
    AgoraRtc_Error_BindSocket = 13,
    AgoraRtc_Error_NetDown = 14,
    AgoraRtc_Error_NoBufs = 15,

    AgoraRtc_Error_InvalidVendorKey = 101,
    AgoraRtc_Error_InvalidChannelName = 102,
    AgoraRtc_Error_NoAvailableChannel = 103,
    AgoraRtc_Error_LookupChannelTimeout = 104,
    AgoraRtc_Error_LookupChannelRejected = 105,
    AgoraRtc_Error_OpenChannelTimeout = 106,
    AgoraRtc_Error_OpenChannelRejected = 107,
    
    AgoraRtc_Error_LoadMediaEngine = 1001,
    AgoraRtc_Error_StartCall = 1002,
    AgoraRtc_Error_StartCamera = 1003,
	AgoraRtc_Error_StartVideoRender = 1004,
	AgoraRtc_Error_Adm_GeneralError = 1005,
	AgoraRtc_Error_Adm_JavaResource = 1006,
	AgoraRtc_Error_Adm_SampleRate = 1007,
	AgoraRtc_Error_Adm_InitPlayout = 1008,
	AgoraRtc_Error_Adm_StartPlayout = 1009,
	AgoraRtc_Error_Adm_StopPlayout = 1010,
	AgoraRtc_Error_Adm_InitRecording = 1011,
	AgoraRtc_Error_Adm_StartRecording = 1012,
	AgoraRtc_Error_Adm_StopRecording = 1013,
    AgoraRtc_Error_Adm_RuntimePlayoutWarning = 1014,
    AgoraRtc_Error_Adm_RuntimePlayoutError = 1015,
    AgoraRtc_Error_Adm_RuntimeRecordingWarning = 1016,
    AgoraRtc_Error_Adm_RuntimeRecordingError = 1017,
    AgoraRtc_Error_Adm_RecordAudioFailed = 1018,
    AgoraRtc_Error_Adm_RecordAudioSilence = 1019,
    AgoraRtc_Error_Adm_PlaybackAbnormalFrequency = 1020,
    AgoraRtc_Error_Adm_RecordAbnormalFrequency = 1021,
};

typedef NS_ENUM(NSUInteger, AgoraRtcQuality) {
    AgoraRtc_Quality_Unknown = 0,
    AgoraRtc_Quality_Excellent = 1,
    AgoraRtc_Quality_Good = 2,
    AgoraRtc_Quality_Poor = 3,
    AgoraRtc_Quality_Bad = 4,
    AgoraRtc_Quality_VBad = 5,
    AgoraRtc_Quality_Down = 6,
};

typedef NS_ENUM(NSUInteger, AgoraRtcLogFilter) {
    AgoraRtc_LogFilter_Debug = 0x0800,
    AgoraRtc_LogFilter_Info = 0x0001,
    AgoraRtc_LogFilter_Warn = 0x0002,
    AgoraRtc_LogFilter_Error = 0x0004,
    AgoraRtc_LogFilter_Critical = 0x0008,
};

typedef NS_ENUM(NSUInteger, AgoraRtcRenderMode) {
    AgoraRtc_Render_Hidden = 1,
    AgoraRtc_Render_Fit = 2,
    AgoraRtc_Render_Adaptive = 3,
};

typedef NS_ENUM(NSUInteger, AgoraRtcQualityReportFormat) {
    AgoraRtc_QualityReportFormat_Json = 0,
    AgoraRtc_QualityReportFormat_Html = 1,
};

__attribute__((visibility("default"))) @interface AgoraRtcVideoCanvas : NSObject
@property (strong, nonatomic) VIEW_CLASS* view;
@property (assign, nonatomic) AgoraRtcRenderMode renderMode;
@property (assign, nonatomic) NSUInteger uid;
@end


__attribute__((visibility("default"))) @interface AgoraRtcSessionStat : NSObject
@property (assign, nonatomic) NSUInteger duration;
@property (assign, nonatomic) NSUInteger txBytes;
@property (assign, nonatomic) NSUInteger rxBytes;
@end

__attribute__((visibility("default"))) @interface AgoraRtcAudioVolumeInfo : NSObject
@property (assign, nonatomic) NSUInteger uid;
@property (assign, nonatomic) NSUInteger volume;
@end


__attribute__((visibility("default"))) @interface AgoraRtcEngineKit : NSObject

/**
 *  Returns Agora Voice SDK version.
 *
 *  @return SDK version
 */
+ (NSString *)getSdkVersion;
+ (NSString *)getMediaEngineVersion;

/**
 *  The constructor for AgoraRtcEngineKit Class. The method accept three callback blocks as arguments, thy are to be executed on main queue.
 *
 *  @param qualityBlock  executed every 3 seconds for each user.
 *  @param logEventBlock executed on receive log messages.
 *  @param errorBlock    executed on receive error messages.
 *
 *  @return an object of AgoraRtcEngineKit class
 */
- (id)initWithVendorKey:(NSString*)key
                  error:(void(^)(AgoraRtcErrorCode errorCode))errorBlock;
/**
 * blocks
 */
- (void)recapBlock:(void(^)(const char *recapData, NSInteger length))recapBlock;
- (void)audioVolumeIndicationBlock:(void(^)(NSArray *speakers, NSInteger totalVolume))audioVolumeIndicationBlock;

- (void)firstLocalVideoFrameBlock:(void(^)(NSInteger width, NSInteger height, NSInteger elapsed))firstLocalVideoFrameBlock;
- (void)firstRemoteVideoDecodedBlock:(void(^)(NSUInteger uid, NSInteger width, NSInteger height, NSInteger elapsed))firstRemoteVideoDecodedBlock;
- (void)firstRemoteVideoFrameBlock:(void(^)(NSUInteger uid, NSInteger width, NSInteger height, NSInteger elapsed))firstRemoteVideoFrameBlock;
- (void)userJoinedBlock:(void(^)(NSUInteger uid, NSInteger elapsed))userJoinedBlock;
- (void)userOfflineBlock:(void(^)(NSUInteger uid))userOfflineBlock;
- (void)audioRecorderExceptionBlock:(void(^)(NSInteger elapsed))audioRecorderExceptionBlock;
- (void)userMuteAudioBlock:(void(^)(NSUInteger uid, bool muted))userMuteAudioBlock;
- (void)userMuteVideoBlock:(void(^)(NSUInteger uid, bool muted))userMuteVideoBlock;
- (void)localVideoStatBlock:(void(^)(NSInteger sentBytes, NSInteger sentFrames))localVideoStatBlock;
- (void)remoteVideoStatBlock:(void(^)(NSUInteger uid, NSInteger frameCount, NSInteger delay, NSInteger receivedBytes))remoteVideoStatBlock;
- (void)cameraReadyBlock:(void(^)())cameraReadyBlock;
- (void)connectionLostBlock:(void(^)())connectionLostBlock;
- (void)rejoinChannelSuccessBlock:(void(^)(NSString* channel, NSUInteger uid, NSInteger elapsed))rejoinChannelSuccessBlock;
- (void)updateSessionStatBlock:(void(^)(AgoraRtcSessionStat* stat))updateSessionBlock;
- (void)leaveChannelBlock:(void(^)(AgoraRtcSessionStat* stat))leaveChannelBlock;
- (void)audioQualityBlock:(void(^)(NSUInteger uid, AgoraRtcQuality quality, NSUInteger delay, NSUInteger lost))audioQualityBlock;
- (void)audioTransportQualityBlock:(void(^)(NSUInteger uid, NSUInteger delay, NSUInteger lost))audioTransportQualityBlock;
- (void)videoTransportQualityBlock:(void(^)(NSUInteger uid, NSUInteger delay, NSUInteger lost))videoTransportQualityBlock;
- (void)networkQualityBlock:(void(^)(AgoraRtcQuality quality))networkQualityBlock;
- (void)mediaEngineEventBlock:(void(^)(NSInteger code))mediaEngineEventBlock;
- (void)vendorMessageBlock:(void(^)(NSUInteger uid, NSData* data))vendorMessageBlock;

/** BEGIN OF COMMON METHODS */

/**
 *  Create an open UDP socket to the AgoraRtcEngineKit cloud service to join a channel.
 *
 *  @param key    Account level credentials issued by AgoraLab company to each vendor.
 *  @param channelName  Joining in the same channel indicates those clients have entered in one room.
 *  @param info         Optional argument can be whatever the programmer likes personally.
 *  @param uid          Optional argument is the unique ID for each member in one channel. Uid management will be taken over if it is 0 by default.
 *  @param successBlock executed on main queue after join the channel successfully.
 */
- (int)joinChannelByKey:(NSString *)key
             channelName:(NSString *)channelName
                    info:(NSString *)info
                     uid:(NSUInteger)uid
                 joinSuccess:(void(^)(NSString* channel, NSUInteger uid, NSInteger elapsed))joinSuccessBlock;

/**
 *  Leave channel positively.
 */
- (int)leaveChannel;

/**
 *  Enable network test.
 */
- (int)enableNetworkTest;

/**
 *  Disable network test.
 */
- (int)disableNetworkTest;

- (int)enableVideo;
- (int)disableVideo;
- (int)startPreview;
- (int)stopPreview;

- (int)enableVendorMessage;
- (int)disableVendorMessage;
- (int)sendVendorMessage:(NSData*)data;

/**
 *  Specify sdk profile
 *
 *  @param profile, sdk profile in json format.
 *  @param merge, specify merge or replace old profile
 */
- (int)setProfile:(NSString *)profile
            merge:(BOOL)merge;

/**
 *  Specify sdk parameters
 *
 *  @param options, sdk options in json format.
 */
- (int)setParameters:(NSString *)options;

- (NSString*) makeQualityReportUrl:(NSString*) channel
                       listenerUid:(NSUInteger) listenerUid
                       speakerrUid:(NSUInteger) speakerUid
                      reportFormat:(AgoraRtcQualityReportFormat) reportFormat;

- (NSString*) getCallId;

- (int) rate:(NSString*) callId
      rating:(NSInteger) rating
 description:(NSString*) description;

- (int) complain:(NSString*) callId
     description:(NSString*) description;

/** END OF COMMON METHODS */

/** BEGIN OF AUDIO METHODS */


/**
 *  Enable / Disable speaker
 *
 *  @param enableSpeaker set YES to enable, NO to disable.
 */
- (int)setEnableSpeakerphone:(BOOL)enableSpeaker;

- (BOOL)isSpeakerphoneEnabled;

/**
 *  Set speaker volume.
 *
 *  @param volume set between 0 and 255.
 */
- (int)setSpeakerphoneVolume:(NSUInteger)volume;

/**
 *  Enable speakers' volume report
 *
 *  @param interval, <=0 - disabled, >0 interval in ms.
 */
- (int)enableAudioVolumeIndication:(NSInteger)interval
               smooth:(NSInteger)smooth;

/**
 *  Enable recap
 *
 *  @param interval, <=0 - disabled, >0 interval in ms.
 */
- (int)enableRecap:(NSInteger)interval;

/**
 *  Start playing recap conversation
 *
 */
- (int)playRecap;

- (int)enableAudioQualityIndication:(BOOL)enabled;
- (int)enableTransportQualityIndication:(BOOL)enabled;


/**
 *  Start recording conversation to file specified by the file path
 *
 *  @param filePath, file path to save recorded conversation.
 */
- (int)startAudioRecording:(NSString*)filePath;

/**
 *  Stop conversation recording
 *
 */
- (int)stopAudioRecording;

/**
 *  Start echo test.
 */
- (int)startEchoTest:(void(^)(NSString* channel, NSUInteger uid, NSInteger elapsed))successBlock;


/**
 *  Stop echo test.
 */
- (int)stopEchoTest;

/**
 *  Mute / Unmute the client.
 *
 *  @param shouldMute set YES to mute, NO to unmute.
 */
- (int)muteLocalAudioStream:(BOOL)mute;


/**
 *  Mute / Unmute peers.
 *
 *  @param shouldMute set YES to mute, NO to unmute.
 */
- (int)muteAllRemoteAudioStreams:(BOOL)mute;

/** END OF AUDIO METHODS */

/** BEGIN OF VIDIO METHODS */

- (int)setupLocalVideo:(AgoraRtcVideoCanvas*)local;

- (int)setupRemoteVideo:(AgoraRtcVideoCanvas*)remote;

- (int)setLocalRenderMode:(AgoraRtcRenderMode) mode;
- (int)setRemoteRenderMode: (NSUInteger)uid
                      mode:(AgoraRtcRenderMode) mode;

- (int)switchView:(NSUInteger)uid1
       andAnother:(NSUInteger)uid2;

- (int)switchCamera;

- (int)setVideoResolution: (int)width andHeight: (int)height;

- (int)muteLocalVideoStream:(BOOL)mute;
- (int)muteAllRemoteVideoStreams:(BOOL)mute;

- (int)setVideoMaxBitrate: (int)bitrate;
- (int)setVideoMaxFrameRate: (int)frameRate;

/** END OF VIDIO METHODS */

- (int)setLogFile:(NSString*)filePath;
@end
