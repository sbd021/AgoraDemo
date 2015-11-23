//
//  AGSEnterRoomViewController.h
//  AgoraSample
//
//  Created by apple on 15/9/15.
//  Copyright (c) 2015年 Agora. All rights reserved.
//

#import "AGSBaseViewController.h"
#import "AGSAlertView.h"
#import <AVFoundation/AVFoundation.h>

@interface AGSSelectMediaViewController : AGSBaseViewController <AGSAlertViewDelegate, AVAudioRecorderDelegate, AVAudioPlayerDelegate>

@end

static NSString * const AGSKeyChannel = @"Channel";
static NSString * const AGSKeyVendorKey = @"VendorKey";
static NSString * const AGSKeySegueIdentifierSelect = @"Select";
static NSString * const AGSKeyUsername = @"Username";
static NSString * const AGSKeySegueIdentifierChat = @"Chat";