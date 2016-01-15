//
//  AGSAgoraKitManager.m
//  AgoraSample
//
//  Created by apple on 15/9/17.
//  Copyright (c) 2015年 Agora. All rights reserved.
//

#import "AGSAgoraKitManager.h"

static AGSAgoraKitManager *obj = nil;

@implementation AGSAgoraKitManager

+ (AGSAgoraKitManager *)shareManager
{
    static dispatch_once_t once_token;
    dispatch_once(&once_token, ^{
        if (!obj) {
            obj = [[AGSAgoraKitManager alloc] init];
        }
    });
    return obj;
}

- (id)init
{
    self = [super init];
    if (self) {
        self.callBackView = [[AGSCallBackView alloc]init];
        self.callBackView.delegate = self;
    }
    
    return self;
}

- (void)setVendorKey:(NSString *)vendorKey
{
    _vendorKey = vendorKey;
    if (!self.agoraKit) {
        self.agoraKit = [AgoraRtcEngineKit sharedEngineWithVendorKey:vendorKey error:^(AgoraRtcErrorCode errorCode) {
            _errorCode = errorCode;
        }];
    }
}

- (void)didHideCallBackView:(AGSCallBackView *)view
{
    if ([self.delegate respondsToSelector:@selector(didBackChatViewAndHideCallBackView:)]) {
        [self.delegate didBackChatViewAndHideCallBackView:view];
    }
}

@end
