//
//  AGSAgoraKitManager.h
//  AgoraSample
//
//  Created by apple on 15/9/17.
//  Copyright (c) 2015年 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AgoraRtcEngineKit/AgoraRtcEngineKit.h>
#import "AGSCallBackView.h"

@protocol AGSAgoraKitManagerDelegate;

@interface AGSAgoraKitManager : NSObject <AGSCallBackViewDelegate>

@property (nonatomic, strong) AgoraRtcEngineKit *agoraKit;
@property (nonatomic, copy) NSString *vendorKey;
@property (nonatomic, readonly) AgoraRtcErrorCode errorCode;
@property (nonatomic, strong) AGSCallBackView *callBackView;
@property (nonatomic, weak) id<AGSAgoraKitManagerDelegate> delegate;

+ (AGSAgoraKitManager *)shareManager;

@end

@protocol AGSAgoraKitManagerDelegate <NSObject>

- (void)didBackChatViewAndHideCallBackView:(AGSCallBackView *)view;

@end;