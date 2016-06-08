//
//  AGSChatEncryptObserver.h
//  AgoraSample
//
//  Created by junhao wang on 6/7/16.
//  Copyright © 2016 Agora. All rights reserved.
//

#ifndef AGSChatEncryptObserver_h
#define AGSChatEncryptObserver_h

#import <AgoraRtcEngineKit/AgoraRtcEngineKit.h>

@interface AGSChatEncryptObserver : NSObject

+ (int) registerEncryptObserver:(AgoraRtcEngineKit*) kit;

@end


#endif /* AGSChatEncryptObserver_h */
